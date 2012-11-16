#ifndef CLIENTNETWORKENGINE_H
#define CLIENTNETWORKENGINE_H

#include "Engine/NetworkEngine/NetworkEngine.h"

class ClientNetworkEngine : public NetworkEngine
{
    public:
        ClientNetworkEngine();
        virtual ~ClientNetworkEngine();

        virtual void work();
        virtual void handleMessage(const EngineMessage &e);

        virtual void sendToAllTcp(const EngineMessage &e);
        virtual void sendToAllUdp(const EngineMessage &e) = 0;
    protected:
    private:
};

#endif // CLIENTNETWORKENGINE_H
