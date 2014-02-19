#include "ClientLogin.h"
#include "Engine/NetworkEngine/NetworkIpAdressFinder.h"
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

bool ClientLogin::isLogin()
{
    return m_login;
}

 ClientLogin::~ClientLogin()
{
    m_work.reset();
    m_service->stop();
    m_service_thread.join();
    delete m_player;
}

 ClientLogin::ClientLogin(unsigned short port, std::string pseudo, std::string passwd) :
m_service(new boost::asio::io_service),
m_work(new boost::asio::io_service::work(*m_service)),
m_login(false)
{
    m_connection = SslConnection::create(m_service, SslConnection::Type::CLIENT);
    m_connection->connect(boost::asio::ip::tcp::endpoint(getAddress(*m_service, "127.0.0.1"), port));
    m_service_thread = boost::thread(&ClientLogin::m_run, this);

    Player player;
    ServerGlobalMessage* message = new ServerGlobalMessage();

    while(1)
    {
        if(m_connection->isConnected())
            break;
        if(m_connection->hasError())
        {
            std::cout << std::endl << m_connection->getError().message() << std::endl;
            return;
        }
        boost::this_thread::sleep(boost::posix_time::milliseconds(150));
    }
    player.pseudo=pseudo;
    player.passwd=passwd;

    message->player = player;
    message->type = ServerGlobalMessageType::LOGIN;

    m_connection->send(m_serialize(message));

    while(1)
    {
        if(m_connection->hasError())
        {
            std::cout<<m_connection->getError().message()<<std::endl;
        }
        if(m_connection->hasData())
        {
            message = m_deserialize(m_connection->getData());
            switch (message->type)
            {
                case ServerGlobalMessageType::LOGIN:
                {
                    if (message->player.pseudo == pseudo && message->player.passwd == passwd)
                    {
                        m_player = &message->player;
                        m_login = true;
                        delete message;
                        return;
                    }
                    delete message;
                    return;
                }
                break;
            }
        }
    }
    delete message;
}

Player* ClientLogin::getPlayer()
{
    return m_player;
}

