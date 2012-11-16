#include "clientnetworkengine.h"
#include "Engine/NetworkEngine/NetworkIpAdressFinder.h"

ClientNetworkEngine::ClientNetworkEngine()
{
    m_tcp = TcpConnection::create(m_service);
    m_udp = UdpConnection::create(m_service);
}

ClientNetworkEngine::~ClientNetworkEngine()
{
    //dtor
}
void ClientNetworkEngine::work()
{
    if(m_tcp->isConnected()){
        std::cout << "connected" << std::endl;
    }
    while(m_tcp->hasError()){
        std::cout << m_tcp->getError().message()<<std::endl;
    }
}

void ClientNetworkEngine::handleMessage(const EngineMessage& e)
{

}
void ClientNetworkEngine::sendToAllTcp(const EngineMessage& e)
{

}
void ClientNetworkEngine::connect(std::string address, unsigned short port)
{
    std::cout << "Connecting to " << address << "..." << std::endl;
    m_port = port;
    bool ok=true;
    m_serverAddress = getAddress(*m_service, address, &ok);
    if(ok){
        std::cout << "Failed" << std::endl;
        return;
    }
    m_tcp->connect(boost::asio::ip::tcp::endpoint(m_serverAddress, m_port));
    /*m_udp->connect(boost::asio::ip::udp::endpoint(m_serverAddress, m_port));
    m_udp->bind(boost::asio::ip::udp::endpoint(boost::asio::ip::address(), m_port));*/
}
void ClientNetworkEngine::send(std::string data)
{
    m_tcp->send(data);
}
