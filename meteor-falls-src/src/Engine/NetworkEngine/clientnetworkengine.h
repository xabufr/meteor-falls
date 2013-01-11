#ifndef CLIENTNETWORKENGINE_H
#define CLIENTNETWORKENGINE_H

#include "NetworkEngine.h"
#include "TcpConnection.h"
#include "UdpConnection.h"

class Joueur;
class ClientNetworkEngine : public NetworkEngine
{
    public:
        ClientNetworkEngine(EngineManager*, const std::string& address, unsigned short port, Joueur*, const std::string& password);
        virtual ~ClientNetworkEngine();

        virtual void work();
        virtual void handleMessage(EngineMessage &);

        virtual void sendToAllTcp(const EngineMessage &e);
        virtual void sendToAllUdp(const EngineMessage &e){};

        void connect(std::string, unsigned short);
        int getState() const;
		virtual void logingIn();

		void sendChatMessage(std::string message, int porte);

		void trySelectTeam(char);
		void trySelectGameplay(int);

		bool isRtsDispo() const;

    protected:
        TcpConnection::pointer m_tcp;
        UdpConnection::pointer m_udp;

        boost::asio::ip::address m_serverAddress;
        unsigned short m_port;
		std::string m_password, m_salt, m_session;
		unsigned int m_playerNumber;
		Joueur *m_joueur;
		char m_teamId;
		bool m_rtsDispo;
	public:
        enum ClientNetworkEngineState{
            CONNECTING,
            CONNECTED,
            AUTHENTIFICATING,
            NONE
        } m_state;
};

#endif // CLIENTNETWORKENGINE_H
