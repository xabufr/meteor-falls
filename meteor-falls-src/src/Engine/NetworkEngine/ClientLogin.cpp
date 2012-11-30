#include "ClientLogin.h"
#include "../../../GlobalServer/src/Player.h"
#include <boost/bind.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

ServerGlobalMessage* ClientLogin::m_deserialize(const std::string &data)
{
    ServerGlobalMessage *message = new ServerGlobalMessage;
    std::istringstream iss(data);
    boost::archive::text_iarchive archive(iss);
    archive >> *message;
    return message;
}

std::string ClientLogin::m_serialize(const ServerGlobalMessage *message)
{
    std::ostringstream os;
    boost::archive::text_oarchive archive(os);
    archive << *message;
    return os.str();
}

void ClientLogin::m_run()
{
    m_service->run();
}

void ClientLogin::m_handleAccept_ssl(SslConnection::pointer conn, const boost::system::error_code& e)
{
    if (!e){
        {
            boost::mutex::scoped_lock l(m_mutex_server);
            conn->startListen();
        }
        m_startAccept();
    }
}

void ClientLogin::m_startAccept()
{
    SslConnection::pointer connection_ssl = SslConnection::create(m_service, SslConnection::CLIENT);
    m_acceptor_ssl.async_accept(connection_ssl->socket(),
                                boost::bind(&ClientLogin::m_handleAccept_ssl, this,
                                            connection_ssl, boost::asio::placeholders::error));
}

bool ClientLogin::get_start()
{
    return m_start;
}

bool ClientLogin::send_log(std::string pseudo, std::string passwd)
{
    Player player;
    ServerGlobalMessage* message = new ServerGlobalMessage;
    bool rep = true;

    player.set_pseudo(pseudo);
    player.set_passwd(passwd);

    message->player = player;
    message->type = ServerGlobalMessageType::LOGIN;

    m_server->send(m_serialize(message));

    while (m_start)
    {
       rep = work();
    }

    return rep;
}



bool ClientLogin::work()
{
    if (!m_server->isConnected() || !m_server->isListening())
             return false;

    ServerGlobalMessage *message;
    while (m_server->hasData())
    {
        switch (message->type)
        {
            case ServerGlobalMessageType::LOGIN:
            {
                m_start = false;
                return message->make;
            }
            break;
            case ServerGlobalMessageType::LOGOUT:
            {
                m_start = false;
                return message->make;
            }
            break;
        }
    }
    return false;
}

 ClientLogin::~ClientLogin()
{
    m_work.reset();
    m_service->stop();
    m_thread_service.join();
}

 ClientLogin::ClientLogin(unsigned short port) :
m_service(new boost::asio::io_service),
m_work(new boost::asio::io_service::work(*m_service)),
m_acceptor_ssl(*m_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::address(), port)),
m_start(true)
{
    m_server = SslConnection::create(m_service, SslConnection::CLIENT);
    m_server->connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::address(), port));
    m_thread_service = boost::thread(&ClientLogin::m_run, this);
    m_startAccept();
}


