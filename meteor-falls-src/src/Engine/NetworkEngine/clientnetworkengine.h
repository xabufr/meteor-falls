#ifndef CLIENTNETWORKENGINE_H
#define CLIENTNETWORKENGINE_H

#include "../../Engine/NetworkEngine/NetworkEngine.h"
#include "../../Engine/NetworkEngine/TcpConnection.h"
#include "../../Engine/NetworkEngine/UdpConnection.h"

class ClientNetworkEngine : public NetworkEngine
{
    public:
        ClientNetworkEngine(EngineManager*, const std::string& address, unsigned short port, const std::string& password);
        virtual ~ClientNetworkEngine();

        virtual void work();
        virtual void handleMessage(const EngineMessage &e);

        virtual void sendToAllTcp(const EngineMessage &e);
        virtual void sendToAllUdp(const EngineMessage &e){};

        void connect(std::string, unsigned short);
        int getState() const;
		virtual void logingIn();
    protected:
        TcpConnection::pointer m_tcp;
        UdpConnection::pointer m_udp;

        boost::asio::ip::address m_serverAddress;
        unsigned short m_port;
		std::string m_password, m_salt, m_session;
		unsigned int m_playerNumber;

	public:
        enum ClientNetworkEngineState{
            CONNECTING,
            CONNECTED,
            AUTHENTIFICATING,
            NONE
        } m_state;
};

#endif // CLIENTNETWORKENGINE_H
