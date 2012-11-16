#ifndef CLIENTNETWORKENGINE_H
#define CLIENTNETWORKENGINE_H

#include "Engine/NetworkEngine/NetworkEngine.h"
#include "Engine/NetworkEngine/TcpConnection.h"
#include "Engine/NetworkEngine/UdpConnection.h"

class ClientNetworkEngine : public NetworkEngine
{
    public:
        ClientNetworkEngine();
        virtual ~ClientNetworkEngine();

        virtual void work();
        virtual void handleMessage(const EngineMessage &e);

        virtual void sendToAllTcp(const EngineMessage &e);
        void send(std::string data);
        virtual void sendToAllUdp(const EngineMessage &e){};

        void connect(std::string, unsigned short);
    protected:
    private:
        TcpConnection::pointer m_tcp;
        UdpConnection::pointer m_udp;

        boost::asio::ip::address m_serverAddress;
        unsigned short m_port;
};

#endif // CLIENTNETWORKENGINE_H
