#include "ServerNetworkEngine.h"
#include <iostream>

ServerNetworkEngine::ServerNetworkEngine(unsigned short port) : NetworkEngine(),
m_acceptor(*m_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::address(), port)),
m_lastClient(0)
{
    m_startAccept();
}

ServerNetworkEngine::~ServerNetworkEngine()
{
    //dtor
}
void ServerNetworkEngine::handleMessage(const EngineMessage&)
{

}

void ServerNetworkEngine::work()
{
    std::vector<ServerClient> clients;
    {
        boost::mutex::scoped_lock(l);
        clients =  m_clients;
    }
    for(ServerClient client : clients){
        while(client.tcp()->hasData()){
            std::cout << client.tcp()->getData() << std::endl;
        }
        while(client.tcp()->hasError()){
            std::cout << client.tcp()->getError().message() << std::endl;
        }
    }

}
void ServerNetworkEngine::m_startAccept()
{
    TcpConnection::pointer connection = TcpConnection::create(m_service);
    m_acceptor.async_accept(connection->socket(),
                            boost::bind(&ServerNetworkEngine::m_handleAccept, this,
                                        connection, boost::asio::placeholders::error));
}

void ServerNetworkEngine::m_handleAccept(TcpConnection::pointer conn, const boost::system::error_code& e)
{
    if(!e)
    {
        {
            boost::mutex::scoped_lock(l);
            m_clients.push_back(ServerClient(conn, m_lastClient++));
            conn->setConnected(true);
            conn->startListen();
        }
        m_startAccept();
    }
}
