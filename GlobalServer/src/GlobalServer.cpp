#include <boost/bind.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>
#include "GlobalServer.h"

GlobalServer::GlobalServer(EngineManager *mng, unsigned short port) : NetworkEngine(mng),
m_acceptor_ssl(*m_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::address(), port))
{
    m_sql = new Creator("rack.gheberg.eu", "theshark", "fabrice", "test");
    m_sql->connect_mysql();
    m_startAccept();
}

GlobalServer::~GlobalServer()
{
    delete m_sql;
}


void GlobalServer::work()
{
    std::vector<SslConnection::pointer> clients;
    {
        boost::mutex::scoped_lock l(m_mutex_clients);
        clients = m_clients;
    }
    std::vector<ServerGlobalMessage*> messages;
    ServerGlobalMessage *message;
    for (SslConnection::pointer client : clients){
        if (!client->isConnected() || !client->isListening())
            removeClient(client);
        else{
            while (client->hasData()){
                message = m_deserialize(client->getData());
                messages.push_back(message);

                switch (message->type)
                {
                    case ServerGlobalMessage::Type::LOGIN:
                    {
                        Player joueur = m_sql->select_player(message->player.get_pseudo());
                        if (joueur.get_passwd() == message->player.get_passwd())
                            client->send(joueur.get_session());
                        else
                            client->send("0");
                        break;
                    }
                    case ServerGlobalMessage::Type::LOGOUT:
                        removeClient(client);
                        break;
                    /*case ServerGlobalMessage::Type::SERVER_LIST:
                        break;*/
                    case ServerGlobalMessage::Type::SERVER_UP:
                    {
                        /*Server srv = message->servers[0];
                        m_sql->update(srv.get_id_server(), srv.get_ip_server(), srv.get_id());*/
                        break;
                    }
                    case ServerGlobalMessage::Type::SERVER_DEL:
                    {
                        m_sql->delete_server(message->servers[0].get_ip_server())
                        break;
                    }
                }

                std::cout << message->type << std::endl;
            }
            while (client->hasError())
                std::cout<<client->getError().message()<<std::endl;
        }
    }
}

void GlobalServer::m_startAccept()
{
    SslConnection::pointer connection_ssl = SslConnection::create(m_service, SslConnection::SERVER);
    m_acceptor_ssl.async_accept(connection_ssl->socket(),
                                boost::bind(&GlobalServer::m_handleAccept_ssl, this,
                                            connection_ssl, boost::asio::placeholders::error));
}

void GlobalServer::m_handleAccept_ssl(SslConnection::pointer conn, const boost::system::error_code& e)
{
    if (!e){
        {
            boost::mutex::scoped_lock l(m_mutex_clients);
            m_clients.push_back(conn);
            conn->setConnected(true);
            conn->startListen();
        }
        m_startAccept();
    }
}

void GlobalServer::removeClient(SslConnection::pointer c)
{
    boost::mutex::scoped_lock l(m_mutex_clients);
    for(auto it=m_clients.begin(); it!=m_clients.end(); ++it)
    {
        if(*it==c)
        {
            m_clients.erase(it);
            return;
        }
    }
}

std::string GlobalServer::m_serialize(const ServerGlobalMessage *message)
{
    std::ostringstream os;
    boost::archive::text_oarchive archive(os);
    archive << *message;
    return os.str();
}

ServerGlobalMessage* GlobalServer::m_deserialize(const std::string &data)
{
    ServerGlobalMessage *message;
    std::istringstream iss(data);
    boost::archive::text_iarchive archive(iss);
    archive >> *message;
    return message;
}


