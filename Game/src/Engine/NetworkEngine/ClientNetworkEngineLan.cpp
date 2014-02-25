#include "ClientNetworkEngineLan.h"
#include "../EngineMessage/EngineMessage.h"
#include "../GameEngine/Joueur/Joueur.h"

ClientNetworkEngineLan::ClientNetworkEngineLan(EngineManager* mng, const std::string& address, unsigned short port, Joueur* j, const std::string& password):
    ClientNetworkEngine(mng, address, port, j,  password)
{
    m_udp->connect(boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string("225.125.145.155"), port));
}
ClientNetworkEngineLan::~ClientNetworkEngineLan()
{
    //dtor
}
void ClientNetworkEngineLan::sendToAllUdp(const EngineMessage& e)
{
    m_udp->sendPacket(e.toPacket());
}
void ClientNetworkEngineLan::logingIn()
{
    EngineMessage mess(m_manager);
    mess.message = EngineMessageType::NEW_PLAYER;
    mess.strings[mf::EngineMessageKey::PSEUDO] = m_joueur->getNom();
    mess.strings[mf::EngineMessageKey::PASSWORD] = SHA1(m_password+m_salt);
    m_tcp->sendPacket(mess.toPacket());
}
