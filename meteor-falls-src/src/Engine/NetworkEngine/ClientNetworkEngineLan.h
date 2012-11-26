#ifndef CLIENTNETWORKENGINELAN_H
#define CLIENTNETWORKENGINELAN_H
#include "../../Engine/NetworkEngine/clientnetworkengine.h"

class ClientNetworkEngineLan : public ClientNetworkEngine
{
    public:
        ClientNetworkEngineLan(EngineManager*);
        virtual ~ClientNetworkEngineLan();

        virtual void sendToAllUdp(const EngineMessage &e);
    protected:
    private:
};

#endif // CLIENTNETWORKENGINELAN_H
