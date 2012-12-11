#include <boost/bind.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>
#include "GlobalServer.h"

GlobalServer::GlobalServer(unsigned short port) :
m_service(new boost::asio::io_service),
m_work(new boost::asio::io_service::work(*m_service)),
m_acceptor_ssl(*m_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::address(), port)),
m_start(true)
{
    m_sql = new Creator("rack.gheberg.eu", "theshark", "fabrice", "test");
    m_sql->connect_mysql();
    m_thread_service = boost::thread(&GlobalServer::m_run, this);
    m_startAccept();
}

GlobalServer::~GlobalServer()
{
    delete m_sql;
    m_work.reset();
    m_service->stop();
    m_thread_service.join();
}

bool GlobalServer::get_start()
{
    return m_start;
}

void GlobalServer::m_run()
{
    m_service->run();
}

void GlobalServer::work()
{
    std::vector<SslConnection::pointer> clients;
    {
        boost::mutex::scoped_lock l(m_mutex_clients);
        clients = m_clients;
    }

    ServerGlobalMessage *message;
    for (SslConnection::pointer client : clients){
        if (!client->isConnected())
            removeClient(client);
        else{
            while (client->hasData()){
                std::string data = client->getData();
                message = m_deserialize(data);
                ServerGlobalMessage *msg = new ServerGlobalMessage;
                msg->type = message->type;

                switch (message->type)
                {
                    case ServerGlobalMessageType::LOGIN:
                    {
                        msg->player = m_sql->select_player(message->player.pseudo);
                        msg->make = (msg->player.passwd == message->player.passwd)?true:false;
                    }
                    break;
                    case ServerGlobalMessageType::ADMIN_LOGIN:
                    {
                        msg->admin = m_sql->select_admin(message->admin.pseudo);
                        msg->make = (msg->admin.passwd == message->admin.passwd)?true:false;
                    }
                    break;
                    case ServerGlobalMessageType::ADMIN_CMD:
                    {
                        msg->admin = m_sql->select_admin(message->admin.pseudo);
                        if (msg->admin.passwd == message->admin.passwd)
                        {
                            if (message->admin.cmd == "server_stop")
                            {
                                m_start = false;
                                msg->make = true;
                            }
                            else
                                msg->make = false;
                        }
                    }
                    break;
                    case ServerGlobalMessageType::LOGOUT:
                    {
                        removeClient(client);
                        msg->make = true;
                    }
                    break;
                    case ServerGlobalMessageType::SERVER_LIST:
                    {
                        msg->servers = m_sql->select_all_server();
                        msg->type = ServerGlobalMessageType::SERVER_LIST;
                    }
                    break;
                    case ServerGlobalMessageType::SERVER_UP:
                    {
                        Server srv = message->servers[0];
                        m_sql->update(srv);
                        msg->make = true;
                    }
                    break;
                    case ServerGlobalMessageType::SERVER_DEL:
                    {
                        m_sql->delete_server(message->servers[0].ip);
                        msg->make = true;
                    }
                    break;
                }
                client->send(m_serialize(msg));
                delete msg;
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
            conn->connectionAccepted();
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
    ServerGlobalMessage *message = new ServerGlobalMessage();
    std::istringstream iss(data);
    boost::archive::text_iarchive archive(iss);
    archive >> *message;
    return message;
}
