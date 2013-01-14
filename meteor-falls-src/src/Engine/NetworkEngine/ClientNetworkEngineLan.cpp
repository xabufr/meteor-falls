#include "ClientNetworkEngineLan.h"
#include "../EngineMessage/EngineMessage.h"
#include "../GameEngine/Joueur/Joueur.h"

ClientNetworkEngineLan::ClientNetworkEngineLan(EngineManager* mng, const std::string& address, unsigned short port, Joueur* j, const std::string& password):
    ClientNetworkEngine(mng, address, port, j,  password)
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
	mess.message = EngineMessageType::NEW_PLAYER;
	mess.strings[EngineMessageKey::PSEUDO] = m_joueur->getNom();
	mess.strings[EngineMessageKey::PASSWORD] = SHA1(m_password+m_salt);
	m_tcp->send(serialize(&mess));
}
