#include "ServerNetworkEngineLan.h"
#include "../EngineMessage/EngineMessage.h"
ServerNetworkEngineLan::ServerNetworkEngineLan(EngineManager* mng, unsigned short port):
ServerNetworkEngine(mng,port)
{
	announceServer();
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
	std::cout << "Sending infos" << std::endl;
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
