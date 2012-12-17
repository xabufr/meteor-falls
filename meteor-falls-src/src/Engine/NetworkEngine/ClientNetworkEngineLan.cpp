#include "ClientNetworkEngineLan.h"
#include "../EngineMessage/EngineMessage.h"

ClientNetworkEngineLan::ClientNetworkEngineLan(EngineManager* mng, const std::string& address, unsigned short port, const std::string& password):
    ClientNetworkEngine(mng, address, port, password)
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
void ClientNetworkEngineLan::logingIn()
{
	EngineMessage mess(m_manager);
	mess.strings[EngineMessageKey::PSEUDO] = "TEST";
	mess.strings[EngineMessageKey::PASSWORD] = SHA1(m_password+m_salt);
	m_tcp->send(serialize(&mess));
}
