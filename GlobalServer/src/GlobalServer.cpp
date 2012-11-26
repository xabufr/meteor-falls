#include <boost/bind.hpp>
#include "GlobalServer.h"
#include "../../meteor-falls-src/src/Engine/EngineMessage/EngineMessage.h"

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
    std::vector<EngineMessage*> messages;
    EngineMessage *message;
    for (SslConnection::pointer client : clients){
        if (!client->isConnected() || !client->isListening())
            removeClient(client);
        else{
            while (client->hasData()){
                message = NetworkEngine::deserialize(client->getData());
                messages.push_back(message);

                std::cout << message->strings[FILE_NAME] << std::endl;
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
