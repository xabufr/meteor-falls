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
    m_startAccept();
}

GlobalServer::~GlobalServer()
{

}


void GlobalServer::work()
{
    std::vector<SslConnection::pointer> clients;
    {
        boost::mutex::scoped_lock l(m_mutex_clients);
        clients = m_clients;
    }
    std::vector<ServerGlobalMessage> messages;
    ServerGlobalMessage message;
    for (SslConnection::pointer client : clients){
        if (!client->isConnected() || !client->isListening())
            removeClient(client);
        else{
            while (client->hasData()){
                message = m_deserialize(client->getData());
                messages.push_back(message);

                /*si il demande la liste des serveur
                switch (message->type)
                {
                    case ServerGlobalMessage::Type::LOGIN:
                        break;
                    case ServerGlobalMessage::Type::LOGOUT:
                        break;
                    case ServerGlobalMessage::Type::SERVER_LIST:
                        break;
                    case ServerGlobalMessage::Type::SERVER_UP:
                        break;
                    case ServerGlobalMessage::Type::SERVER_DEL:
                        break;
                }
                client->send(serialize());*/

                std::cout << message.type << std::endl;
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
            /*on lui envoie son num de session
            ServerGlobalMessage *message;
            conn->send(serialize(message));*/
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

std::string GlobalServer::m_serialize(ServerGlobalMessage message)
{
    std::ostringstream os;
    boost::archive::text_oarchive archive(os);
    archive << message;
    return os.str();
}

ServerGlobalMessage GlobalServer::m_deserialize(std::string data)
{
    ServerGlobalMessage message;
    std::istringstream iss(data);
    boost::archive::text_iarchive archive(iss);
    archive >> message;
    return message;
}


