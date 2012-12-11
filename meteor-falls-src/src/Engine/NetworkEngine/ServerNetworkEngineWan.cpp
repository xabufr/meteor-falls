#include "ServerNetworkEngineWan.h"
#include "../../../../GlobalServer/src/Server.h"
#include "../../../../GlobalServer/src/ServerGlobalMessage.h"
#include <boost/archive/text_oarchive.hpp>
#include "NetworkIpAdressFinder.h"
#include "../../Utils/Exception/BasicException.h"

ServerNetworkEngineWan::ServerNetworkEngineWan(EngineManager* mng, unsigned short port):
ServerNetworkEngine(mng, port)
{
	m_connexionServerG = SslConnection::create(m_service, SslConnection::CLIENT);
	m_udpConnexion = UdpConnection::create(m_service);
	bool error;
	boost::asio::ip::address adr = getAddress(*m_service, "127.0.0.1", &error);
	if(error)
	{
		THROW_BASIC_EXCEPTION("Adresse non résolvable");
	}
	m_connexionServerG->connect(boost::asio::ip::tcp::endpoint(adr, 80));
}
void ServerNetworkEngineWan::sendAllUdp(const std::string& data)
{
}

void ServerNetworkEngineWan::announceServer()
{
	m_timer_seed->expires_from_now(boost::posix_time::seconds(5));
	m_timer_seed->async_wait(boost::bind(&ServerNetworkEngineWan::m_handleSendWanInfo, this, _1));
}

void ServerNetworkEngineWan::m_handleSendWanInfo(const boost::system::error_code&)
{
	m_timer_seed->expires_from_now(boost::posix_time::seconds(5));
	m_timer_seed->async_wait(boost::bind(&ServerNetworkEngineWan::m_handleSendWanInfo, this, _1));

	ServerGlobalMessage message;
	message.type = ServerGlobalMessageType::SERVER_UP;
	Server server;
	server.set_passwd(false);
	server.set_nom(m_server_name);
	server.set_nombre_joueurs_connectes(m_clients.size());
	server.set_nombre_joueurs_max(m_max_clients);
	server.set_carte_jouee(m_map_name);
	message.servers.push_back(server);

	std::ostringstream os;
	boost::archive::text_oarchive ar(os);
	ar << message;
	m_connexionServerG->send(os.str());
}
void ServerNetworkEngineWan::work()
{
	if(!m_hasSendtoG&&m_connexionServerG->isConnected())
	{
		announceServer();
		m_hasSendtoG=true;
	}
	if(m_connexionServerG->hasError())
	{
		THROW_BASIC_EXCEPTION(m_connexionServerG->getError().message());	
	}
	ServerNetworkEngine::work();
}
