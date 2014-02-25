#include "clientnetworkengine.h"
#include "NetworkIpAdressFinder.h"
#include "../../Utils/Exception/BasicException.h"
#include "../EngineMessage/EngineMessage.h"
#include "../EngineManager/EngineManager.h"
#include "../../precompiled/serialization.h"
#include "../GameEngine/GameEngine.h"
#include "../GameEngine/Joueur/Joueur.h"
#include "../GameEngine/Joueur/JoueurRPG.h"
#include "../GameEngine/Factions/Equipe.h"
#include "../GameEngine/Factions/FactionManager.h"
#include "../GameEngine/Heros/ClasseHero.h"
#include "../GameEngine/Heros/Hero.h"
#include "../GameEngine/Heros/Avatar.h"
#include "../GameEngine/Unites/Unite.h"
#include "../GameEngine/ClientGameEngine.h"
#include <SFML/System/Clock.hpp>

ClientNetworkEngine::ClientNetworkEngine(EngineManager* mng, const std::string& address, unsigned short port, Joueur* j, const std::string& password):
    NetworkEngine(mng),
    m_port(port),
    m_password(password),
    m_joueur(j)
{
    m_tcp = TcpConnection::create(m_service);
    m_udp = UdpConnection::create(m_service);
    m_teamId = -1;
    m_state = WAITING;
    connect(address, port);
    m_waitingSpawn      = false;
    m_waitingSelectTeam = false;
}
ClientNetworkEngine::~ClientNetworkEngine()
{
    m_tcp->stop();
    m_tcp.reset();
}
void ClientNetworkEngine::handleReceivedNetworkMessage(Packet packet)
{
    EngineMessage message(m_manager, packet);
    switch(message.message)
    {
    case EngineMessageType::SETSALT:
    {
        m_salt  = message.strings[mf::EngineMessageKey::SEL];
        m_state = AUTHENTIFICATING;
        logingIn();
    }
        break;
    case EngineMessageType::LOGIN_RESULT:
    {
        m_playerNumber = message.ints[mf::EngineMessageKey::PLAYER_NUMBER];
        if(m_playerNumber!=-1)
        {
            m_state = CONNECTED;
            m_joueur->setId(m_playerNumber);
            EngineMessage messageTeam(m_manager);
            messageTeam.message = EngineMessageType::GETTEAMLIST;
            m_tcp->sendPacket(messageTeam.toPacket());
            messageTeam.message = EngineMessageType::GETOBJECTSLIST;
            m_tcp->sendPacket(messageTeam.toPacket());
        }
        else
            m_state=NONE;
    }
        break;
    case EngineMessageType::LOAD_MAP:
        m_manager->getGame()->loadMap(message.strings[mf::EngineMessageKey::MAP_NAME]);
        sendSyncReq();
        break;
    case EngineMessageType::ADDTEAM:
    {
        Equipe* equipe = new Equipe(m_manager->getGame(), message.ints[mf::EngineMessageKey::TEAM_ID]);
        equipe->setFaction(FactionManager::get()->getFaction(message.ints[mf::EngineMessageKey::FACTION_ID]));
        m_manager->getGame()->addTeam(equipe);
    }
        break;
    case EngineMessageType::NEW_PLAYER:
    {
        Equipe* e = m_manager->getGame()->getEquipe(message.ints[mf::EngineMessageKey::TEAM_ID]);
        Joueur *j = new Joueur;
        j->setNom(message.strings[mf::EngineMessageKey::PSEUDO]);
        j->setId(message.ints[mf::EngineMessageKey::PLAYER_NUMBER]);
        j->changeTeam(e);
        m_manager->getGame()->addPlayer(j);
        j->setTypeGamplay(Joueur::TypeGameplay::NONE_GAMEPLAY);
        if(message.ints[mf::EngineMessageKey::GAMEPLAY_TYPE] != (int) mf::EngineMessageKey::NONE_GAMEPLAY)
        {
            if(message.ints[mf::EngineMessageKey::GAMEPLAY_TYPE] == (int) mf::EngineMessageKey::RPG_GAMEPLAY)
            {
                j->setTypeGamplay(Joueur::TypeGameplay::RPG);
            }
            else
            {
                j->setTypeGamplay(Joueur::TypeGameplay::RTS);
            }
        }
    }
        break;
    case EngineMessageType::SELECT_TEAM:
    {
        message.setFrom(this);
        EngineMessage *messageGame = EngineMessage::clone(&message);
        messageGame->addToType(EngineType::GameEngineType);
        m_manager->addMessage(messageGame);
        m_waitingSelectTeam = message.ints[mf::EngineMessageKey::PLAYER_NUMBER] != m_joueur->id();
    }
        break;
    case EngineMessageType::SELECT_GAMEPLAY:
    {
        EngineMessage *messageGameplay = EngineMessage::clone(&message);
        messageGameplay->clearTo();
        messageGameplay->addToType(EngineType::GameEngineType);
        m_manager->addMessage(messageGameplay);
    }
        break;
    case EngineMessageType::CHAT_MESSAGE:
    {
        message.setFrom(this);
        EngineMessage *messageGame = EngineMessage::clone(&message);
        messageGame->clearTo();
        messageGame->addToType(EngineType::GameEngineType);
        m_manager->addMessage(messageGame);
    }
        break;
    case EngineMessageType::DEL_PLAYER:
    {
        EngineMessage *clone = EngineMessage::clone(&message);
        m_manager->addMessage(clone);
    }
        break;
    case EngineMessageType::SYNC_TIME:
    {
        boost::posix_time::time_duration tm = boost::posix_time::milliseconds(message.time);
        tm += m_timeSinceLastSyncReq.getDuration()/2;
        m_clock.setTime(tm.total_milliseconds());
        m_timeSinceLastSync.reset();
    }
        break;
    case EngineMessageType::PING:
    {
        EngineMessage mess(m_manager);
        mess.message = EngineMessageType::PING;
        m_tcp->sendPacket(mess.toPacket());
    }
        break;
    case EngineMessageType::SET_PING:
    {
        long ping = message.ints[mf::EngineMessageKey::TIME];
        Joueur* j = m_manager->getGame()->findJoueur(message.ints[mf::EngineMessageKey::PLAYER_NUMBER]);
        if(j!=nullptr)
        {
            j->ping = ping;
        }
    }
        break;
    case EngineMessageType::ADDOBJECT:
    {
        EngineMessage *messageObject = EngineMessage::clone(&message);
        messageObject->clearTo();
        messageObject->addToType(EngineType::GameEngineType);
        m_manager->addMessage(messageObject);
    }
        break;
    case EngineMessageType::SPAWN:
    {
        EngineMessage *messageSpawn = EngineMessage::clone(&message);
        messageSpawn->clearTo();
        messageSpawn->addToType(EngineType::GameEngineType);
        m_manager->addMessage(messageSpawn);
    }
        break;
    case EngineMessageType::PLAYER_POSITION:
    {
        Joueur *j = m_manager->getGame()->findJoueur(message.ints[mf::EngineMessageKey::PLAYER_NUMBER]);
        if(j && j->getTypeGameplay() == Joueur::TypeGameplay::RPG && j->getRPG()->hero())
        {
            j->getRPG()->hero()->deserializeComportement(&message);
        }
    }
        break;
    default:
    {
        EngineMessage *tmpMess = EngineMessage::clone(&message);
        tmpMess->clearTo();
        tmpMess->addToType(EngineType::GameEngineType);
        m_manager->addMessage(tmpMess);
    }
        break;
    }
}

void ClientNetworkEngine::handleRtsSelection(Packet &packet)
{
    std::vector<std::uint32_t> ids;
    packet >> ids;
    ((ClientGameEngine*)m_manager->getGame())->setSelectedUnits(ids);
}

void ClientNetworkEngine::handleReceivedRawMessage(Packet &packet)
{
    std::uint8_t message;
    packet >> message;
    if(message == RTS_SELECTION)
    {
        handleRtsSelection(packet);
    }
}

void ClientNetworkEngine::work(const TimeDuration &elapsed)
{
    if(m_state==CONNECTED && !m_tcp->isConnected())
    {
        m_state = NONE;
    }
    while(m_tcp->hasError())
    {
        std::cout << m_tcp->getError().message()<<std::endl;
        m_state = ClientNetworkEngineState::NONE;
    }
    Packet packet;
    while(m_tcp->hasData())
    {
        m_tcp->fillPacket(packet);
        std::uint8_t messageType;
        packet >> messageType;
        if(messageType == mf::MESSAGE)
        {
            handleReceivedNetworkMessage(packet);
        }
        else if(messageType == mf::RAW_DATA)
        {
            handleReceivedRawMessage(packet);
        }
    }
    while(m_udp->hasData())
    {
        m_udp->fillPacket(packet);
        std::uint8_t messageType;
        packet >> messageType;
        if(messageType == mf::MESSAGE)
        {
            EngineMessage mess(m_manager, packet);
            switch (mess.message)
            {
            case EngineMessageType::PLAYER_POSITION:
            {
                Equipe *e = m_manager->getGame()->getEquipe(mess.ints[mf::EngineMessageKey::TEAM_ID]);
                if(e)
                {
                    Hero *h = dynamic_cast<Hero*>(e->getUnite(mess.ints[mf::EngineMessageKey::OBJECT_ID]));
                    if(h)
                        h->deserializeComportement(&mess);
                }
            }
                break;
            }
        }
    }
    if(m_timeSinceLastSync.getTime() >= 1000)
        sendSyncReq();
}
void ClientNetworkEngine::handleMessage(EngineMessage& e)
{
    sendToAllTcp(e);
}
void ClientNetworkEngine::sendToAllTcp(const EngineMessage& e)
{
    if(m_state==CONNECTED)
        m_tcp->sendPacket(e.toPacket());
}

void ClientNetworkEngine::sendToServerTcp(const EngineMessage &e)
{
    sendToAllTcp(e);
}
void ClientNetworkEngine::connect(std::string address, unsigned short port)
{
    m_port = port;
    bool error=false;
    m_serverAddress = getAddress(*m_service, address, &error);
    if(error){
        THROW_BASIC_EXCEPTION("Can't resolve host address");
    }
    m_state = CONNECTING;
    m_tcp->connect(boost::asio::ip::tcp::endpoint(m_serverAddress, m_port));
    m_udp->socket()->set_option(boost::asio::socket_base::reuse_address(true));
    m_udp->connect(boost::asio::ip::udp::endpoint(m_serverAddress, m_port));
    m_udp->socket()->set_option(boost::asio::ip::multicast::join_group(boost::asio::ip::address::from_string("225.125.145.155")));
    m_udp->bind(boost::asio::ip::udp::endpoint(boost::asio::ip::address(), m_port));
    m_udp->startListen();
}
int ClientNetworkEngine::getState() const
{
    return m_state;
}
void ClientNetworkEngine::logingIn()
{
    EngineMessage mess(m_manager);
    mess.message = EngineMessageType::NEW_PLAYER;
    mess.strings[mf::EngineMessageKey::PASSWORD] = SHA1(m_password+m_salt);
    mess.strings[mf::EngineMessageKey::SESSION] = m_session;
    m_tcp->sendPacket(mess.toPacket());
}
void ClientNetworkEngine::sendChatMessage(std::string mes, mf::EngineMessageKey porte)
{
    EngineMessage message(m_manager);
    message.ints[mf::EngineMessageKey::PLAYER_NUMBER] = m_joueur->id();
    message.message = EngineMessageType::CHAT_MESSAGE;
    message.strings[mf::EngineMessageKey::MESSAGE] = mes;
    message.ints[mf::EngineMessageKey::RANGE] = (int) porte;
    m_tcp->sendPacket(message.toPacket());
}
void ClientNetworkEngine::trySelectTeam(char id)
{
    EngineMessage message(m_manager);
    message.message = EngineMessageType::SELECT_TEAM;
    message.ints[mf::EngineMessageKey::PLAYER_NUMBER] = m_joueur->id();
    message.ints[mf::EngineMessageKey::TEAM_ID] = id;
    m_tcp->sendPacket(message.toPacket());
    m_waitingSelectTeam = true;
}
void ClientNetworkEngine::trySelectGameplay(mf::EngineMessageKey gameplay)
{
    EngineMessage message(m_manager);
    message.message = EngineMessageType::SELECT_GAMEPLAY;
    message.ints[mf::EngineMessageKey::GAMEPLAY_TYPE] = (int) gameplay;
    message.ints[mf::EngineMessageKey::PLAYER_NUMBER] = m_joueur->id();
    m_tcp->sendPacket(message.toPacket());
}
char ClientNetworkEngine::teamId() const
{
    return m_teamId;
}
void ClientNetworkEngine::sendSyncReq()
{
    m_timeSinceLastSyncReq.reset();
    m_timeSinceLastSync.reset();
    EngineMessage message(m_manager);
    message.message = EngineMessageType::SYNC_TIME;
    m_tcp->sendPacket(message.toPacket());
}
void ClientNetworkEngine::trySpawn(Unite* unit, Avatar* av)
{
    EngineMessage message(m_manager);
    message.message = EngineMessageType::SPAWN;
    message.ints[mf::EngineMessageKey::PLAYER_NUMBER] = m_joueur->id();
    message.ints[mf::EngineMessageKey::CLASS_ID] = av->classe()->id();
    message.ints[mf::EngineMessageKey::OBJECT_ID] = unit->id();
    av->serialize(&message);
    message.addToType(EngineType::GameEngineType);
    m_tcp->sendPacket(message.toPacket());
}
void ClientNetworkEngine::sendRpgPosition()
{
    static sf::Clock timerUdpPosition;
    if(m_joueur->getTypeGameplay()!=Joueur::TypeGameplay::RPG||!m_joueur->getRPG()->hero() || timerUdpPosition.getElapsedTime().asMilliseconds() < 1000/30)
        return;
    timerUdpPosition.restart();
    Hero *hero = m_joueur->getRPG()->hero();
    EngineMessage mess(m_manager);
    mess.message = EngineMessageType::PLAYER_POSITION;
    mess.ints[mf::EngineMessageKey::PLAYER_NUMBER] = m_joueur->id();
    hero->serializeComportement(&mess);
    sendToAllUdp(mess);
}
void ClientNetworkEngine::sendRpgModification()
{
    if((m_joueur->getTypeGameplay() != Joueur::TypeGameplay::RPG || !m_joueur->getRPG()->hero()))
        return;
    EngineMessage mess(m_manager);
    mess.message = EngineMessageType::PLAYER_POSITION;
    mess.ints[mf::EngineMessageKey::PLAYER_NUMBER] = m_joueur->id();
    m_joueur->getRPG()->hero()->serializeComportement(&mess);

    m_tcp->sendPacket(mess.toPacket());
}
bool ClientNetworkEngine::isWaitingSpawn() const
{
    return m_waitingSpawn;
}
bool ClientNetworkEngine::isWaitingSelectTeam() const
{
    return m_waitingSelectTeam;
}


void ClientNetworkEngine::sendTCP(const Packet &packet)
{
    m_tcp->sendPacket(packet);
}

void ClientNetworkEngine::sendUDP(const Packet &packet)
{
    m_udp->sendPacket(packet);
}
