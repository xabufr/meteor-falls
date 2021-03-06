#ifndef CLIENTNETWORKENGINE_H
#define CLIENTNETWORKENGINE_H

#include "NetworkEngine.h"
#include "TcpConnection.h"
#include "UdpConnection.h"
#include "../EngineMessage/EngineMessageKey.h"

class Unite;
class Avatar;
class Joueur;
class Packet;
class ClientNetworkEngine : public NetworkEngine
{
    public:
        enum ClientNetworkEngineState{
                    CONNECTING,
                    CONNECTED,
                    AUTHENTIFICATING,
                    WAITING,
                    NONE
                } ;
        ClientNetworkEngine(EngineManager*, const std::string& address, unsigned short port, Joueur*, const std::string& password);
        virtual ~ClientNetworkEngine();

        virtual void work(const TimeDuration &elapsed);
        virtual void handleMessage(EngineMessage &);

        virtual void sendToAllTcp(const EngineMessage &e);
        void sendToServerTcp(const EngineMessage &e);
        virtual void sendToAllUdp(const EngineMessage &e){};

        void sendTCP(const Packet &packet);
        void sendUDP(const Packet &packet);

        void connect(std::string, unsigned short);
        int getState() const;
        virtual void logingIn();

        void sendChatMessage(std::string message, mf::EngineMessageKey porte);

        void trySelectTeam(char);
        void trySelectGameplay(mf::EngineMessageKey);
        void trySpawn(Unite*, Avatar*);

        char teamId() const;

        void sendRpgPosition();
        void sendRpgModification();

        bool isWaitingSpawn() const;
        bool isWaitingSelectTeam() const;

        void handleReceivedNetworkMessage(Packet packet);
        void handleReceivedRawMessage(Packet &packet);
        void handleRtsSelection(Packet &packet);
protected:
        TcpConnection::pointer m_tcp;
        UdpConnection::pointer m_udp;

        void sendSyncReq();

        boost::asio::ip::address m_serverAddress;
        unsigned short m_port;
        std::string m_password, m_salt, m_session;
        unsigned int m_playerNumber;
        Joueur *m_joueur;
        char m_teamId;
        Clock m_timeSinceLastSync, m_timeSinceLastSyncReq;
        ClientNetworkEngineState m_state;
    private:
        bool m_waitingSpawn;
        bool m_waitingSelectTeam;
};

#endif // CLIENTNETWORKENGINE_H
