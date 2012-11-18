#include "clientnetworkengine.h"
#include "Engine/NetworkEngine/NetworkIpAdressFinder.h"
#include "Utils/Exception/BasicException.h"
#include "Engine/EngineMessage/EngineMessage.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

ClientNetworkEngine::ClientNetworkEngine(EngineManager* mng):
    NetworkEngine(mng)
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
    if(m_state==CONNECTING && m_tcp->isConnected()){
        m_state = CONNECTED;
    }
    if(m_state==CONNECTED && !m_tcp->isConnected()){
        m_state = NONE;
    }
    while(m_tcp->hasError()){
        std::cout << m_tcp->getError().message()<<std::endl;
    }
    while(m_tcp->hasData()){
        std::string data = m_tcp->getData();
    }
}

void ClientNetworkEngine::handleMessage(const EngineMessage& e)
{
    sendToAllTcp(e);
}
void ClientNetworkEngine::sendToAllTcp(const EngineMessage& e)
{
    if(m_state==CONNECTED)
        m_tcp->send(serialize(&e));
}
void ClientNetworkEngine::connect(std::string address, unsigned short port)
{
    m_port = port;
    bool error=false;
    m_serverAddress = getAddress(*m_service, address, &error);
    if(error){
        THROW_BASIC_EXCEPTION("Can't resolve host address");
        return;
    }
    m_state = CONNECTING;
    m_tcp->connect(boost::asio::ip::tcp::endpoint(m_serverAddress, m_port));
    /*m_udp->connect(boost::asio::ip::udp::endpoint(m_serverAddress, m_port));
    m_udp->bind(boost::asio::ip::udp::endpoint(boost::asio::ip::address(), m_port));*/
}

int ClientNetworkEngine::getState() const
{
    return m_state;
}
