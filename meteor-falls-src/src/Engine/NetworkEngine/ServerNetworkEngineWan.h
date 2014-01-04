#ifndef _HOME_THOMAS_METEOR_FALLS_METEOR_FALLS_SRC_SRC_ENGINE_SERVERNETWORKENGINEWAN_H__
#define _HOME_THOMAS_METEOR_FALLS_METEOR_FALLS_SRC_SRC_ENGINE_SERVERNETWORKENGINEWAN_H__
#include "ServerNetworkEngine.h"
#include "SslConnection.h"

class ServerNetworkEngineWan : public ServerNetworkEngine
{
    public:
        ServerNetworkEngineWan(EngineManager*, unsigned short port);
        ~ServerNetworkEngineWan();
        virtual void sendAllUdp(const std::string&);
        virtual void announceServer();
        virtual void work(const TimeDuration &elapsed);
    private:
        void m_handleSendWanInfo(const boost::system::error_code&);
        SslConnection::pointer m_connexionServerG;
        bool m_hasSendtoG;
        virtual void m_addNewPlayer(client_id, EngineMessage*);
        void m_recupererSession(ServerClient*);
};
#endif // _HOME_THOMAS_METEOR_FALLS_METEOR_FALLS_SRC_SRC_ENGINE_SERVERNETWORKENGINEWAN_H__
