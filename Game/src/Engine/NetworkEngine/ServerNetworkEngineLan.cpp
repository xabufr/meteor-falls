#include "ServerNetworkEngineLan.h"
#include "../EngineMessage/EngineMessage.h"
#include "../GameEngine/Joueur/Joueur.h"
#include "../GameEngine/GameEngine.h"

ServerNetworkEngineLan::ServerNetworkEngineLan(EngineManager* mng, unsigned short port):
ServerNetworkEngine(mng,port)
{
    announceServer();
    m_udpConnexion->socket()->set_option(boost::asio::ip::udp::socket::broadcast(true));
    m_udpConnexion->socket()->set_option(boost::asio::socket_base::reuse_address(true));
    m_udpConnexion->socket()->set_option(boost::asio::ip::multicast::join_group(boost::asio::ip::address::from_string("225.125.145.155")));
    m_udpConnexion->bind(boost::asio::ip::udp::endpoint(boost::asio::ip::address(), m_port));
    m_udpConnexion->startListen();
}
ServerNetworkEngineLan::~ServerNetworkEngineLan()
{
}
void ServerNetworkEngineLan::m_handleSendLanInfo(const boost::system::error_code&)
{
    m_timer_seed->expires_from_now(boost::posix_time::millisec(500));
    m_timer_seed->async_wait(boost::bind(&ServerNetworkEngineLan::m_handleSendLanInfo, this, _1));

    EngineMessage mess(nullptr);
    mess.message = mf::EngineMessageType::SERVER_INFO;
    mess.strings[mf::EngineMessageKey::SERVER_NAME] = m_server_name;
    mess.strings[mf::EngineMessageKey::MAP_NAME] = m_map_name;
    mess.ints[mf::EngineMessageKey::MAX_PLAYERS] = m_max_clients;
    mess.ints[mf::EngineMessageKey::PLAYER_NUMBER] = m_clients.size();

    m_udpConnexion->send(mess.toPacket(), boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string("225.125.145.155"), m_port));
}
void ServerNetworkEngineLan::announceServer()
{
    m_timer_seed->expires_from_now(boost::posix_time::millisec(500));
    m_timer_seed->async_wait(boost::bind(&ServerNetworkEngineLan::m_handleSendLanInfo, this, _1));
}
void ServerNetworkEngineLan::sendAllUdp(const Packet &packet)
{
    m_udpConnexion->send(packet, boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string("225.125.145.155"), m_port));
}
void ServerNetworkEngineLan::m_addNewPlayer(client_id id, EngineMessage* message)
{
    std::string password = message->strings[mf::EngineMessageKey::PASSWORD];
    std::string pseudo = message->strings[mf::EngineMessageKey::PSEUDO];
    boost::recursive_mutex::scoped_lock(m_mutex_clients);
    ServerClient* client=nullptr;
    for(ServerClient &c : m_clients)
    {
        if(c.id()==id)
        {
            client=&c;
        }
    }
    if(client==nullptr)
        return;
    EngineMessage *messageClient = new EngineMessage(m_manager);
    messageClient->message       = mf::EngineMessageType::LOGIN_RESULT;
    if(password != NetworkEngine::SHA1(m_password+client->data->sel))
    {
        messageClient->ints[mf::EngineMessageKey::PLAYER_NUMBER] = -1;
    }
    else
    {
        client->joueur = new Joueur;
        client->joueur->setNom(pseudo);
        client->joueur->setId(client->id());
        client->data->isConnected=true;
        messageClient->ints[mf::EngineMessageKey::PLAYER_NUMBER] = client->id();
        std::cout << "New player: " << client->id() << std::endl;
        m_manager->getGame()->addPlayer(client->joueur);
    }
    client->tcp()->sendPacket(messageClient->toPacket());
    delete messageClient;
}
