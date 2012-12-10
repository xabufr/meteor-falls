#ifndef SERVERNETWORKENGINE_H
#define SERVERNETWORKENGINE_H

#include "NetworkEngine.h"
#include "ServerClient.h"
#include <vector>
#include <boost/asio.hpp>

class ServerNetworkEngine : public NetworkEngine
{
    public:
        ServerNetworkEngine(EngineManager*, unsigned short port);
        virtual ~ServerNetworkEngine();

        void handleMessage(const EngineMessage&);
        void work();
        void removeClient(ServerClient& c);
        void sendToAllTcp(EngineMessage*);
        void sendToAllExcluding(unsigned int id, EngineMessage*);

		virtual void sendAllUdp(const std::string&)=0;

		virtual void announceServer()=0;

        static void sendToTcp(ServerClient&, EngineMessage*);
        static void sendToTcp(ServerClient&, std::string);

    protected:
        void m_startAccept();
        void m_handleAccept(TcpConnection::pointer, const boost::system::error_code&);

        std::vector<ServerClient> m_clients;
        boost::asio::ip::tcp::acceptor m_acceptor;
        boost::mutex m_mutex_clients;
        client_id m_lastClient;
		std::string m_server_name, m_map_name;
		unsigned short m_max_clients;
		unsigned short m_port;
};

#endif // SERVERNETWORKENGINE_H
