#ifndef CLIENTNETWORKENGINELAN_H
#define CLIENTNETWORKENGINELAN_H
#include "../../Engine/NetworkEngine/clientnetworkengine.h"

class Joueur;
class ClientNetworkEngineLan : public ClientNetworkEngine
{
    public:
		ClientNetworkEngineLan(EngineManager* mng, const std::string& address, unsigned short port, Joueur*, const std::string& password);
        virtual ~ClientNetworkEngineLan();

        virtual void sendToAllUdp(const EngineMessage &e);
		virtual void logingIn();
    protected:
    private:
};

#endif // CLIENTNETWORKENGINELAN_H
