#incldue "ClientLogin.h"

ServerGlobalMessage* ClientLogin::m_deserialize(const std::string &data)
{
    ServerGlobalMessage *message;
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
                                boost::bind(&GlobalServer::m_handleAccept_ssl, this,
                                            connection_ssl, boost::asio::placeholders::error));
}

bool ClientLogin::get_start()
{
    return m_start;
}

void ClientLogin::work()
{
    if (!m_server->isConnected() || !m_server->isListening())
             return;

    ServerGlobalMessage *message;
    while (m_server->hasData())
    {
        switch (message->type)
        {
            case ServerGlobalMessage::Type::LOGIN:
                return message->make;
            break;
            case ServerGlobalMessage::Type::LOGOUT:
                return message->make;
            break;
        }
    }
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
    m_server->connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::address(), port);
    m_server->setConnected(true);
    m_thread_service = boost::thread(&GlobalServer::m_run, this);
    m_startAccept();
}


