#ifndef _HOME_THOMAS_METEOR_FALLS_METEOR_FALLS_SRC_SRC_ENGINE_NETWORKENGINE_SERVERNETWORKENGINELAN_H__
#define _HOME_THOMAS_METEOR_FALLS_METEOR_FALLS_SRC_SRC_ENGINE_NETWORKENGINE_SERVERNETWORKENGINELAN_H__
#include "ServerNetworkEngine.h"

class Packet;
class ServerNetworkEngineLan: public ServerNetworkEngine
{
    public:
        ServerNetworkEngineLan(EngineManager*, unsigned short port);
        virtual void announceServer();
        virtual void sendAllUdp(const Packet &packet);
        virtual ~ServerNetworkEngineLan();

    private:
        void m_handleSendLanInfo(const boost::system::error_code&);
        virtual void m_addNewPlayer(client_id, EngineMessage*);
};
#endif // _HOME_THOMAS_METEOR_FALLS_METEOR_FALLS_SRC_SRC_ENGINE_NETWORKENGINE_SERVERNETWORKENGINELAN_H__
