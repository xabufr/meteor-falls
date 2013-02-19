#ifndef SERVERNETWORKENGINE_H
#define SERVERNETWORKENGINE_H

#include "NetworkEngine.h"
#include "ServerClient.h"
#include <vector>
#include <boost/asio.hpp>
#include <boost/thread/recursive_mutex.hpp>

class Equipe;
class ServerNetworkEngine : public NetworkEngine
{
    public:
        ServerNetworkEngine(EngineManager*, unsigned short port);
        virtual ~ServerNetworkEngine();

        void handleMessage(EngineMessage&);
        virtual void work();
        void removeClient(ServerClient& c);
        void sendToAllTcp(EngineMessage*);
        void sendToAllExcluding(unsigned int id, EngineMessage*);

		virtual void sendAllUdp(const std::string&)=0;

		virtual void announceServer()=0;

        static void sendToTcp(ServerClient&, EngineMessage*);
        static void sendToTcp(ServerClient&, std::string);
		void sendToTcp(Joueur*, EngineMessage*);

		void sendToTeam(Equipe*, EngineMessage*);

		void setServerName(const std::string&);
		void setMaxClients(unsigned short);
		void setMapName(const std::string&);
		void announcePlayerConnectionTeam(ServerClient &c);

		ServerClient* findClient(client_id);
		void pingClients();
		void sendSetPing(ServerClient&);

    protected:
        void m_startAccept();
        void m_handleAccept(TcpConnection::pointer, const boost::system::error_code&);
		virtual void m_addNewPlayer(client_id, EngineMessage*) = 0;
		EngineMessage* m_createMapMessage();

        std::vector<ServerClient> m_clients;
        boost::asio::ip::tcp::acceptor m_acceptor;
        boost::recursive_mutex m_mutex_clients;
        client_id m_lastClient;
		std::string m_server_name, m_map_name, m_password;
		unsigned short m_max_clients;
		unsigned short m_port;
		boost::asio::deadline_timer *m_timer_seed;
};

#endif // SERVERNETWORKENGINE_H
