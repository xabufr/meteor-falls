#include "clientnetworkengine.h"
#include "NetworkIpAdressFinder.h"
#include "../../Utils/Exception/BasicException.h"
#include "../EngineMessage/EngineMessage.h"
#include "../../precompiled/serialization.h"
#include "../GameEngine/GameEngine.h"
#include "../GameEngine/Joueur/Joueur.h"

ClientNetworkEngine::ClientNetworkEngine(EngineManager* mng, const std::string& address, unsigned short port, Joueur* j, const std::string& password):
    NetworkEngine(mng),
	m_port(port),
	m_password(password),
	m_joueur(j)
{
    m_tcp = TcpConnection::create(m_service);
    m_udp = UdpConnection::create(m_service);
	connect(address, port);
}
ClientNetworkEngine::~ClientNetworkEngine()
{
}
void ClientNetworkEngine::work()
{
	if(m_state==CONNECTED && !m_tcp->isConnected()){
        m_state = NONE;
    }
    while(m_tcp->hasError()){
        std::cout << m_tcp->getError().message()<<std::endl;
    }
    while(m_tcp->hasData()){
        std::string data = m_tcp->getData();
		EngineMessage *message = this->deserialize(data);
		switch(message->message)
		{
			case EngineMessageType::SETSALT:
				m_salt  = message->strings[EngineMessageKey::SEL];
				m_state = AUTHENTIFICATING;
				logingIn();
				break;
			case EngineMessageType::LOGIN_RESULT:
				m_playerNumber = message->ints[EngineMessageKey::PLAYER_NUMBER];
				if(m_playerNumber!=-1)
					m_state = CONNECTED;
				else
					m_state=NONE;
				break;
			case EngineMessageType::LOAD_MAP:
				m_manager->getGame()->loadMap(message->strings[EngineMessageKey::MAP_NAME]);
				break;
		}
		delete message;
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
void ClientNetworkEngine::logingIn()
{
	EngineMessage mess(m_manager);
	mess.message = EngineMessageType::NEW_PLAYER;
	mess.strings[EngineMessageKey::PASSWORD] = SHA1(m_password+m_salt);
	mess.strings[EngineMessageKey::SESSION] = m_session;
	m_tcp->send(serialize(&mess));
}
