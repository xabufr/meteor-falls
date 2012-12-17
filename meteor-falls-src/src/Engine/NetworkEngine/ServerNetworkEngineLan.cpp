#include "ServerNetworkEngineLan.h"
#include "../EngineMessage/EngineMessage.h"
#include "../GameEngine/Joueur/Joueur.h"

ServerNetworkEngineLan::ServerNetworkEngineLan(EngineManager* mng, unsigned short port):
ServerNetworkEngine(mng,port)
{
	announceServer();
	m_udpConnexion->socket()->set_option(boost::asio::ip::udp::socket::broadcast(true));
}
ServerNetworkEngineLan::~ServerNetworkEngineLan()
{
}
void ServerNetworkEngineLan::m_handleSendLanInfo(const boost::system::error_code&)
{
	m_timer_seed->expires_from_now(boost::posix_time::millisec(500));
	m_timer_seed->async_wait(boost::bind(&ServerNetworkEngineLan::m_handleSendLanInfo, this, _1));

	EngineMessage mess(nullptr);
	mess.message = EngineMessageType::SERVER_INFO;
	mess.strings[EngineMessageKey::SERVER_NAME] = m_server_name;
	mess.strings[EngineMessageKey::MAP_NAME] = m_map_name; 
	mess.ints[EngineMessageKey::MAX_PLAYERS] = m_max_clients; 
	mess.ints[EngineMessageKey::PLAYER_NUMBER] = m_clients.size();

	std::string data = NetworkEngine::serialize(&mess);
	m_udpConnexion->send(data, boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string("225.125.145.155"), m_port));
}
void ServerNetworkEngineLan::announceServer()
{
	m_timer_seed->expires_from_now(boost::posix_time::millisec(500));
	m_timer_seed->async_wait(boost::bind(&ServerNetworkEngineLan::m_handleSendLanInfo, this, _1));
}
void ServerNetworkEngineLan::sendAllUdp(const std::string& data)
{
	m_udpConnexion->send(data, boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string("225.125.145.155"), m_port));
}
void ServerNetworkEngineLan::m_addNewPlayer(client_id id, EngineMessage* message)
{
	std::string password = message->strings[EngineMessageKey::PASSWORD];
	std::string pseudo = message->strings[EngineMessageKey::PSEUDO];
	boost::mutex::scoped_lock(m_mutex_clients);
	ServerClient* client=nullptr;
	for(ServerClient &c : m_clients)
	{
		if(c.id()==id)
		{
        	client=&c;
		}
	}
	if(client==nullptr)
		return;
	EngineMessage *messageClient = new EngineMessage(m_manager);
	messageClient->message       = EngineMessageType::LOGIN_RESULT;
	if(password != NetworkEngine::SHA1(m_password+client->sel))
	{
		messageClient->ints[EngineMessageKey::PLAYER_NUMBER] = -1;
	}
	else
	{
		client->joueur = new Joueur;
		client->joueur->setNom(pseudo);
		client->isConnected=true;
		messageClient->ints[EngineMessageKey::PLAYER_NUMBER] = client->id();
	}
	client->tcp()->send(serialize(messageClient));
	delete messageClient;
}
