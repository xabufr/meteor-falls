#include "ServerNetworkEngine.h"
#include <iostream>
#include "Engine/EngineMessage/EngineMessage.h"

ServerNetworkEngine::ServerNetworkEngine(EngineManager *mng, unsigned short port) : NetworkEngine(mng),
    m_acceptor(*m_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::address(), port)),
    m_lastClient(0),
	m_port(port)
{
	m_udpConnexion = UdpConnection::create(m_service);
	m_timer_seed = new boost::asio::deadline_timer(*m_service);
    m_startAccept();
}

ServerNetworkEngine::~ServerNetworkEngine()
{
	m_timer_seed->cancel();
	delete m_timer_seed;
}
void ServerNetworkEngine::handleMessage(const EngineMessage&)
{

}

void ServerNetworkEngine::work()
{
    std::vector<ServerClient> clients;
    {
        boost::mutex::scoped_lock l(m_mutex_clients);
        clients =  m_clients;
    }
    std::vector<EngineMessage*> messages;
    EngineMessage *message;
    for(ServerClient client : clients)
    {
        if(!client.tcp()->isConnected()||!client.tcp()->isListening())
        {
            removeClient(client);
        }
        else
        {
            while(client.tcp()->hasData())
            {
                message = NetworkEngine::deserialize(client.tcp()->getData());
                messages.push_back(message);

                std::cout << message->strings[FILE_NAME] << std::endl;
            }
            while(client.tcp()->hasError())
            {
                std::cout << client.tcp()->getError().message() << std::endl;
            }
        }
    }
	while(m_udpConnexion->hasError())
	{
			std::cout << m_udpConnexion->getError().message() << std::endl;
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
            boost::mutex::scoped_lock l(m_mutex_clients);
            m_clients.push_back(ServerClient(conn, m_lastClient++));
            conn->setConnected(true);
            conn->startListen();
        }
        m_startAccept();
    }
}
void ServerNetworkEngine::removeClient(ServerClient& c)
{
    boost::mutex::scoped_lock l(m_mutex_clients);
    for(auto it=m_clients.begin(); it!=m_clients.end(); ++it)
    {
        if(it->tcp()==c.tcp())
        {
            m_clients.erase(it);
            return;
        }
    }
}

void ServerNetworkEngine::sendToAllTcp(EngineMessage* message)
{
    std::string data(NetworkEngine::serialize(message));

    boost::mutex::scoped_lock l(m_mutex_clients);
    for(ServerClient &c : m_clients)
    {
        sendToTcp(c,data);
    }
}
void ServerNetworkEngine::sendToTcp(ServerClient& c, EngineMessage* message)
{
    c.tcp()->send(NetworkEngine::serialize(message));
}
void ServerNetworkEngine::sendToTcp(ServerClient& c, std::string d)
{
    c.tcp()->send(d);
}

void ServerNetworkEngine::sendToAllExcluding(unsigned int id, EngineMessage* message)
{
    std::string data(NetworkEngine::serialize(message));

    boost::mutex::scoped_lock l(m_mutex_clients);
    for(ServerClient &c  :m_clients)
    {
        if(c.id()!=id)
            c.tcp()->send(data);
    }
}
