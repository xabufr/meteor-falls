#include "ServerNetworkEngine.h"
#include "../EngineMessage/EngineMessage.h"
#include "../../precompiled/lexical_cast.h"
#include "../GameEngine/GameEngine.h"
#include "../GameEngine/Factions/Equipe.h"
#include "../GameEngine/Factions/Faction.h"
#include "../GameEngine/Joueur/JoueurRPG.h"
#include "../GameEngine/Joueur/JoueurRTS.h"
#include "../GameEngine/Joueur/Joueur.h"
#include "../GameEngine/Factions/Equipe.h"
#include "../GameEngine/Unites/Unite.h"
#include "../GameEngine/Unites/Batiment.h"
#include "../GameEngine/Heros/Hero.h"
#include "../GameEngine/Heros/Avatar.h"

ServerNetworkEngine::ServerNetworkEngine(EngineManager *mng, unsigned short port) : NetworkEngine(mng),
    m_acceptor(*m_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::address(), port)),
    m_lastClient(0),
    m_port(port)
{
    m_udpConnexion = UdpConnection::create(m_service);
    m_timer_seed = new boost::asio::deadline_timer(*m_service);
    m_startAccept();
}
ServerNetworkEngine::~ServerNetworkEngine()
{
    m_timer_seed->cancel();
    delete m_timer_seed;
}
void ServerNetworkEngine::handleMessage(EngineMessage &)
{

}
void ServerNetworkEngine::handleRtsSelectionChanged(const ServerClient &originalSender, Packet &packet)
{
    std::vector<std::uint32_t> ids;
    packet >> ids;
    this->sendToTeam(originalSender.joueur->equipe(), packet);
}

void ServerNetworkEngine::handleRawPacket(const ServerClient &client, Packet &packet)
{
    std::uint8_t message_encoded;
    packet >> message_encoded;
    mf::EngineMessageType message = (mf::EngineMessageType) message_encoded;
    switch (message)
    {
        case mf::EngineMessageType::RTS_SELECTION:
        {
            handleRtsSelectionChanged(client, packet);
        }
        break;
    }
}

void ServerNetworkEngine::work(const TimeDuration &elapsed)
{
    const long pingTimeout = 10000;
    std::vector<ServerClient> clients;
    {
        boost::recursive_mutex::scoped_lock l(m_mutex_clients);
        for (auto it = m_clients.begin(); it != m_clients.end();)
        {
            if (it->data->toDel)
                it = m_clients.erase(it);
            else
            {
                ++it;
            }
            clients = m_clients;
        }
    }
    EngineMessage *message;
    Packet packet;
    std::uint8_t messageType;
    for (ServerClient & client : clients)
    {
        if (!client.tcp()->isConnected() || !client.tcp()->isListening()
            || (client.data->waitingPing && client.data->timePing.getTime() >= pingTimeout) || client.tcp()->hasError())
        {
            removeClient(client);
        }
        else
        {
            while (client.tcp()->hasData())
            {
                client.tcp()->fillPacket(packet);
                packet >> messageType;
                if (messageType == mf::MESSAGE)
                {
                    message = new EngineMessage(m_manager, packet);
                    switch (message->message)
                    {
                        case mf::EngineMessageType::NEW_PLAYER:
                        {
                            m_addNewPlayer(client.id(), message);
                            EngineMessage *messageMap = m_createMapMessage();
                            client.tcp()->sendPacket(messageMap->toPacket());
                            delete messageMap;
                        }
                        break;
                        case mf::EngineMessageType::GETTEAMLIST:
                        {
                            const std::vector<Equipe *> &equipes = m_manager->getGame()->getTeams();
                            EngineMessage messageTeams(m_manager);
                            messageTeams.message           = mf::EngineMessageType::ADDTEAM;
                            for (Equipe * e : equipes)
                            {
                                messageTeams.ints[mf::EngineMessageKey::FACTION_ID] = e->faction()->id();
                                messageTeams.ints[mf::EngineMessageKey::TEAM_ID] = e->id();
                                client.tcp()->sendPacket(messageTeams.toPacket());
                                for (Joueur * j : e->joueurs())
                                {
                                    EngineMessage *player = new EngineMessage(m_manager);
                                    player->message = mf::EngineMessageType::NEW_PLAYER;
                                    player->ints[mf::EngineMessageKey::TEAM_ID] = e->id();
                                    player->ints[mf::EngineMessageKey::PLAYER_NUMBER] = j->id();
                                    player->strings[mf::EngineMessageKey::PSEUDO] = j->getNom();
                                    player->ints[mf::EngineMessageKey::GAMEPLAY_TYPE] = j->getTypeGameplay();
                                    if (j->getTypeGameplay() == Joueur::RPG)
                                        player->ints[mf::EngineMessageKey::GAMEPLAY_TYPE] = (int)mf::EngineMessageKey::RPG_GAMEPLAY;
                                    else if (j->getTypeGameplay() == Joueur::RTS)
                                        player->ints[mf::EngineMessageKey::GAMEPLAY_TYPE] = (int) mf::EngineMessageKey::RTS_GAMEPLAY;
                                    else
                                        player->ints[mf::EngineMessageKey::GAMEPLAY_TYPE] = (int) mf::EngineMessageKey::NONE_GAMEPLAY;

                                    client.tcp()->sendPacket(player->toPacket());
                                    delete player;
                                }
                            }
                        }
                        break;
                        case mf::EngineMessageType::SYNC_TIME:
                        {
                            EngineMessage messageTime(m_manager);
                            messageTime.message = mf::EngineMessageType::SYNC_TIME;
                            messageTime.time    = m_clock.getTime();
                            sendToTcp(client, &messageTime);
                        }
                        break;
                        case mf::EngineMessageType::PING:
                        {
                            client.data->timeSinceLastPingRep.reset();
                            client.data->waitingPing = false;
                            client.joueur->ping = client.data->timePing.getTime() / 2;
                            sendSetPing(client);
                        }
                        break;
                        case mf::EngineMessageType::GETOBJECTSLIST:
                        {
                            for (Equipe * equipe : m_manager->getGame()->getTeams())
                            {
                                for (Unite * unite : equipe->unites())
                                {
                                    if (dynamic_cast<Hero *>(unite)) continue;
                                    if (!unite->isConstructed()) continue;

                                    EngineMessage messageUnit(m_manager);
                                    messageUnit.message = mf::EngineMessageType::ADDOBJECT;
                                    messageUnit.positions[mf::EngineMessageKey::OBJECT_POSITION] = unite->position();
                                    messageUnit.ints[mf::EngineMessageKey::TEAM_ID] = equipe->id();
                                    messageUnit.ints[mf::EngineMessageKey::OBJECT_ID] = unite->id();
                                    messageUnit.ints[mf::EngineMessageKey::OBJECT_TYPE] = unite->type()->id();
                                    sendToTcp(client, &messageUnit);

                                    Batiment *batiment = dynamic_cast<Batiment *>(unite);
                                    if (batiment)
                                    {
                                        auto buildStack = batiment->buildStack();
                                        while (!buildStack.empty())
                                        {
                                            auto task = buildStack.front();
                                            EngineMessage messageBuild(nullptr);
                                            messageBuild.message = mf::EngineMessageType::BUILD;
                                            messageBuild.ints[mf::EngineMessageKey::BUILDER] = batiment->id();
                                            messageBuild.ints[mf::EngineMessageKey::TEAM_ID] = batiment->equipe()->id();
                                            messageBuild.ints[mf::EngineMessageKey::OBJECT_ID] = task.second->id();
                                            messageBuild.ints[mf::EngineMessageKey::OBJECT_TYPE] = task.second->type()->id();
                                            messageBuild.positions[mf::EngineMessageKey::OBJECT_POSITION] = task.second->position();
                                            messageBuild.ints[mf::EngineMessageKey::TIME] = task.first.milliseconds();
                                            sendToTcp(client, &messageBuild);
                                            buildStack.pop();
                                        }
                                    }
                                }
                                //Synchro des héros
                                for (JoueurRPG * joueur : equipe->getRPG())
                                {
                                    if (!joueur->hero())
                                        continue;
                                    EngineMessage messageHero(m_manager);
                                    messageHero.message = mf::EngineMessageType::SPAWN;
                                    messageHero.ints[mf::EngineMessageKey::PLAYER_NUMBER] = joueur->joueur()->id();
                                    joueur->hero()->avatar()->serialize(&messageHero);
                                    messageHero.ints[mf::EngineMessageKey::OBJECT_ID] = joueur->hero()->id();
                                    messageHero.positions[mf::EngineMessageKey::OBJECT_POSITION] = joueur->hero()->position();
                                    messageHero.addToType(EngineType::GameEngineType);
                                    messageHero.ints[mf::EngineMessageKey::RESULT] = 1;
                                    sendToTcp(client, &messageHero);
                                }
                            }
                        }
                        break;
                        case mf::EngineMessageType::PLAYER_POSITION:
                        {
                            Joueur *j = m_manager->getGame()->findJoueur(message->ints[mf::EngineMessageKey::PLAYER_NUMBER]);
                            if (j && j->getTypeGameplay() == Joueur::TypeGameplay::RPG && j->getRPG()->hero())
                            {
                                j->getRPG()->hero()->teleport(message->positions[mf::EngineMessageKey::OBJECT_POSITION]);
                                Equipe *e = m_manager->getGame()->getEquipe(message->ints[mf::EngineMessageKey::TEAM_ID]);
                                if (e)
                                {
                                    Hero *h = dynamic_cast<Hero *>(e->getUnite(message->ints[mf::EngineMessageKey::OBJECT_ID]));
                                    if (h)
                                    {
                                        h->deserializeComportement(message);
                                    }
                                }
                                sendToAllExcluding(client.id(), message);
                            }
                        }
                        break;
                        default:
                            EngineMessage *messageCopy = EngineMessage::clone(message);
                            messageCopy->clearTo();
                            messageCopy->addToType(EngineType::GameEngineType);
                            m_manager->addMessage(messageCopy);
                            break;
                    }
                    delete message;
                }
                else if (messageType == mf::RAW_DATA)
                {
                    handleRawPacket(client, packet);
                }
            }
            while (client.tcp()->hasError())
            {
                std::cout << client.tcp()->getError().message() << std::endl;
            }
        }
    }
    while (m_udpConnexion->hasError())
    {
        std::cout << m_udpConnexion->getError().message() << std::endl;
    }
    while (m_udpConnexion->hasData())
    {
        m_udpConnexion->fillPacket(packet);
        packet >> messageType;
        if (messageType == mf::MESSAGE)
        {
            if (message)
            {
                boost::recursive_mutex::scoped_lock l(m_mutex_clients);
                bool found = false;
                for (ServerClient client : m_clients)
                {
                    if (client.tcp()->socket().remote_endpoint().address() == packet.sender)
                    {
                        found = true;
                        break;
                    }
                }
                if (!found)
                    continue;
            }
            EngineMessage *message = new EngineMessage(m_manager, packet);
            switch (message->message)
            {
                case mf::EngineMessageType::PLAYER_POSITION:
                {
                    Joueur *j = m_manager->getGame()->findJoueur(message->ints[mf::EngineMessageKey::PLAYER_NUMBER]);
                    if (j && j->getTypeGameplay() == Joueur::TypeGameplay::RPG && j->getRPG()->hero())
                    {
                        j->getRPG()->hero()->teleport(message->positions[mf::EngineMessageKey::OBJECT_POSITION]);
                        Equipe *e = m_manager->getGame()->getEquipe(message->ints[mf::EngineMessageKey::TEAM_ID]);
                        if (e)
                        {
                            Hero *h = dynamic_cast<Hero *>(e->getUnite(message->ints[mf::EngineMessageKey::OBJECT_ID]));
                            if (h)
                            {
                                h->deserializeComportement(message);
                            }
                        }
                    }
                }
                break;
            }
            delete message;
        }
    }
    pingClients();
}
void ServerNetworkEngine::m_startAccept()
{
    TcpConnection::pointer connection = TcpConnection::create(m_service);
    m_acceptor.async_accept(connection->socket(),
                            boost::bind(&ServerNetworkEngine::m_handleAccept, this,
                                        connection, boost::asio::placeholders::error));
}
void ServerNetworkEngine::m_handleAccept(TcpConnection::pointer conn, const boost::system::error_code &e)
{
    if (!e)
    {
        {
            boost::recursive_mutex::scoped_lock l(m_mutex_clients);
            m_clients.push_back(ServerClient(conn, m_lastClient++));
            conn->setConnected(true);
            conn->startListen();
            ServerClient &client(m_clients.back());
            client.data->sel = SHA1(boost::lexical_cast<std::string>(client.id()) +
                                    client.tcp()->socket().remote_endpoint().address().to_string());
            EngineMessage messageSalt(m_manager);
            messageSalt.message = mf::EngineMessageType::SETSALT;
            messageSalt.strings[mf::EngineMessageKey::SEL] = client.data->sel;
            client.tcp()->sendPacket(messageSalt.toPacket());
        }
        m_startAccept();
    }
}
void ServerNetworkEngine::removeClient(ServerClient &c)
{
    EngineMessage message(m_manager);
    message.message = mf::EngineMessageType::DEL_PLAYER;
    message.ints[mf::EngineMessageKey::PLAYER_NUMBER] = c.joueur->id();
    {
        boost::recursive_mutex::scoped_lock l(m_mutex_clients);
        for (auto it = m_clients.begin(); it != m_clients.end(); ++it)
        {
            if (it->tcp() == c.tcp())
            {
                m_clients.erase(it);
                break;
            }
        }
    }
    message.addToType(EngineType::GameEngineType);
    sendToAllTcp(&message);
    EngineMessage *clone = EngineMessage::clone(&message);
    m_manager->addMessage(clone);
}
void ServerNetworkEngine::sendToAllTcp(EngineMessage *message)
{
    Packet data(message->toPacket());

    boost::recursive_mutex::scoped_lock l(m_mutex_clients);
    for (ServerClient & c : m_clients)
    {
        sendToTcp(c, data);
    }
}
void ServerNetworkEngine::sendToTcp(ServerClient &c, EngineMessage *message)
{
    c.tcp()->sendPacket(message->toPacket());
}
void ServerNetworkEngine::sendToTcp(ServerClient &c, const Packet &packet)
{
    c.tcp()->sendPacket(packet);
}
void ServerNetworkEngine::sendToAllExcluding(unsigned int id, EngineMessage *message)
{
    Packet data(message->toPacket());

    boost::recursive_mutex::scoped_lock l(m_mutex_clients);
    for (ServerClient & c  : m_clients)
    {
        if (c.id() != id)
            c.tcp()->sendPacket(data);
    }
}
void ServerNetworkEngine::setServerName(const std::string &name)
{
    m_server_name = name;
}
void ServerNetworkEngine::setMaxClients(unsigned short number)
{
    m_max_clients = number;
}
void ServerNetworkEngine::setMapName(const std::string &name)
{
    m_map_name = name;
    m_manager->getGame()->loadMap(name);
}
EngineMessage *ServerNetworkEngine::m_createMapMessage()
{
    EngineMessage *message = new EngineMessage(m_manager);
    message->message = mf::EngineMessageType::LOAD_MAP;
    message->strings[mf::EngineMessageKey::MAP_NAME] = m_map_name;
    message->addToType(EngineType::GameEngineType);
    return message;
}
void ServerNetworkEngine::sendToTeam(Equipe *e, EngineMessage *message)
{
    sendToTeam(e, message->toPacket());
}

void ServerNetworkEngine::sendToTeam(Equipe *e, const Packet &packet)
{
    boost::recursive_mutex::scoped_lock l(m_mutex_clients);
    for (ServerClient & c : m_clients)
    {
        for (Joueur * j : e->joueurs())
        {
            if (j == c.joueur)
            {
                sendToTcp(c, packet);
                break;
            }
        }
    }
}
ServerClient *ServerNetworkEngine::findClient(client_id id)
{
    boost::recursive_mutex::scoped_lock l(m_mutex_clients);
    for (ServerClient & c : m_clients)
    {
        if (c.id() == id)
            return &c;
    }
    return nullptr;
}
void ServerNetworkEngine::announcePlayerConnectionTeam(Joueur *joueur)
{
    EngineMessage message(m_manager);
    message.message = mf::EngineMessageType::NEW_PLAYER;
    message.ints[mf::EngineMessageKey::PLAYER_NUMBER] = joueur->id();
    message.strings[mf::EngineMessageKey::PSEUDO] = joueur->getNom();
    message.ints[mf::EngineMessageKey::TEAM_ID] = joueur->equipe()->id();
    if (joueur->getTypeGameplay() == Joueur::RPG)
        message.ints[mf::EngineMessageKey::GAMEPLAY_TYPE] = (int) mf::EngineMessageKey::RPG_GAMEPLAY;
    else if (joueur->getTypeGameplay() == Joueur::RTS)
        message.ints[mf::EngineMessageKey::GAMEPLAY_TYPE] = (int) mf::EngineMessageKey::RTS_GAMEPLAY;
    else
        message.ints[mf::EngineMessageKey::GAMEPLAY_TYPE] = (int) mf::EngineMessageKey::NONE_GAMEPLAY;
    sendToAllExcluding(joueur->id(), &message);
}
void ServerNetworkEngine::pingClients()
{
    boost::recursive_mutex::scoped_lock l(m_mutex_clients);
    for (ServerClient & c : m_clients)
    {
        if (!c.data->waitingPing && c.data->timeSinceLastPingRep.getTime() > 2000)
        {
            c.data->waitingPing = true;
            EngineMessage mess(m_manager);
            mess.message = mf::EngineMessageType::PING;
            sendToTcp(c, &mess);
            c.data->timePing.reset();
        }
    }
}
void ServerNetworkEngine::sendSetPing(ServerClient &c)
{
    EngineMessage mess(m_manager);
    mess.message = mf::EngineMessageType::SET_PING;
    mess.ints[mf::EngineMessageKey::TIME] = c.joueur->ping;
    mess.ints[mf::EngineMessageKey::PLAYER_NUMBER] = c.joueur->id();
    sendToAllTcp(&mess);
}
void ServerNetworkEngine::sendToTcp(Joueur *j, EngineMessage *message)
{
    boost::recursive_mutex::scoped_lock(m_mutex_clients);
    for (ServerClient & c : m_clients)
    {
        if (c.joueur == j)
        {
            sendToTcp(c, message);
            return;
        }
    }
}
