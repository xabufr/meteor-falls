#ifndef CLIENTNETWORKENGINE_H
#define CLIENTNETWORKENGINE_H

#include "../../Engine/NetworkEngine/NetworkEngine.h"
#include "../../Engine/NetworkEngine/TcpConnection.h"
#include "../../Engine/NetworkEngine/UdpConnection.h"

class ClientNetworkEngine : public NetworkEngine
{
    public:
        ClientNetworkEngine(EngineManager*);
        virtual ~ClientNetworkEngine();

        virtual void work();
        virtual void handleMessage(const EngineMessage &e);

        virtual void sendToAllTcp(const EngineMessage &e);
        virtual void sendToAllUdp(const EngineMessage &e){};

        void connect(std::string, unsigned short);
        int getState() const;
    protected:
    private:
        TcpConnection::pointer m_tcp;
        UdpConnection::pointer m_udp;

        boost::asio::ip::address m_serverAddress;
        unsigned short m_port;

        enum ClientNetworkEngineState{
            CONNECTING,
            CONNECTED,
            AUTHENTIFICATING,
            NONE
        } m_state;
};

#endif // CLIENTNETWORKENGINE_H
