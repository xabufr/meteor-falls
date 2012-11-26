#include "../../meteor-falls-src/src/Engine/NetworkEngine/ClientNetworkEngineLan.h"

ClientNetworkEngineLan::ClientNetworkEngineLan(EngineManager* mng):
    ClientNetworkEngine(mng)
{
    //ctor
}

ClientNetworkEngineLan::~ClientNetworkEngineLan()
{
    //dtor
}
void ClientNetworkEngineLan::sendToAllUdp(const EngineMessage& e)
{

}
