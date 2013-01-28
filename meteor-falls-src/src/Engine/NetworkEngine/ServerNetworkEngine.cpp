#include "ServerNetworkEngine.h"
#include <iostream>
#include "../EngineMessage/EngineMessage.h"
#include "../../precompiled/lexical_cast.h"
#include "../GameEngine/GameEngine.h"
#include "../GameEngine/Factions/Equipe.h"
#include "../GameEngine/Factions/Faction.h"
#include "../GameEngine/Joueur/JoueurRPG.h"
#include "../GameEngine/Joueur/JoueurRTS.h"
#include "../GameEngine/Joueur/Joueur.h"
#include "../GameEngine/Factions/Equipe.h"

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
void ServerNetworkEngine::handleMessage(EngineMessage&)
{

}
void ServerNetworkEngine::work()
{
    std::vector<ServerClient> clients;
    {
        boost::mutex::scoped_lock l(m_mutex_clients);
		for(auto it=m_clients.begin();it!=m_clients.end();)
		{
			if(it->toDel)
				it = m_clients.erase(it);
			else
				++it;
		}
        clients =  m_clients;
    }
    std::vector<EngineMessage*> messages;
    EngineMessage *message;
    for(ServerClient client : clients)
    {
        if(!client.tcp()->isConnected()||!client.tcp()->isListening())
        {
            removeClient(client);
        }
        else
        {
            while(client.tcp()->hasData())
            {
                message = NetworkEngine::deserialize(client.tcp()->getData());
				switch(message->message)
				{
					case EngineMessageType::NEW_PLAYER:
						{
							m_addNewPlayer(client.id(), message);
							EngineMessage *messageMap = m_createMapMessage();
							client.tcp()->send(serialize(messageMap));
							delete messageMap;
						}
						break;
					case EngineMessageType::GETTEAMLIST:
						{
							const std::vector<Equipe*>& equipes = m_manager->getGame()->getTeams();
							EngineMessage messageTeams(m_manager);
							messageTeams.message           = EngineMessageType::ADDTEAM;
							for(Equipe* e : equipes)
							{
								messageTeams.ints[EngineMessageKey::FACTION_ID] = e->faction()->id();
								messageTeams.ints[EngineMessageKey::TEAM_ID] = e->id();
								client.tcp()->send(serialize(&messageTeams));
								for(Joueur *j : e->joueurs())
								{
									EngineMessage *player = new EngineMessage(m_manager);
									player->message = EngineMessageType::NEW_PLAYER;
									player->ints[EngineMessageKey::TEAM_ID] = e->id();
									player->ints[EngineMessageKey::PLAYER_NUMBER] = j->id;
									player->strings[EngineMessageKey::PSEUDO] = j->getNom();
									player->ints[EngineMessageKey::GAMEPLAY_TYPE] = j->getTypeGameplay();
									if(j->getTypeGameplay() == Joueur::RPG)
										player->ints[EngineMessageKey::GAMEPLAY_TYPE] = EngineMessageKey::RPG_GAMEPLAY;
									else if(j->getTypeGameplay() == Joueur::RTS)
										player->ints[EngineMessageKey::GAMEPLAY_TYPE] = EngineMessageKey::RTS_GAMEPLAY;
									else
										player->ints[EngineMessageKey::GAMEPLAY_TYPE] = EngineMessageKey::NONE_GAMEPLAY;
	
									client.tcp()->send(serialize(player));
									delete player;
								}
							}
						}
						break;
					case EngineMessageType::CHAT_MESSAGE:
						{
							message->setFrom(this);
							EngineMessage *messageGameEngine = EngineMessage::clone(message);
							messageGameEngine->clearTo();
							messageGameEngine->addToType(EngineType::GameEngineType);
							m_manager->addMessage(messageGameEngine);
						}
						break;
					case EngineMessageType::SELECT_TEAM:
						{
							char teamId  = message->ints[EngineMessageKey::TEAM_ID];
							ServerClient *client = findClient(message->ints[EngineMessageKey::PLAYER_NUMBER]);
							if(client==nullptr)
									break;
							bool canJoin = m_manager->getGame()->tryJoinTeam(teamId, client->joueur);
							EngineMessage messageTeam(m_manager);
							messageTeam.message = EngineMessageType::SELECT_TEAM;
							messageTeam.ints[EngineMessageKey::PLAYER_NUMBER] = client->id();
							if(canJoin)
							{
								messageTeam.ints[EngineMessageKey::TEAM_ID] = teamId;
								sendToAllTcp(&messageTeam);
								Equipe *equ         = m_manager->getGame()->getEquipe(teamId);
								int rtsDisp         = equ->getRTS() == nullptr ? 1 : 0;
								messageTeam.message = EngineMessageType::SET_RTS_DISP;
								messageTeam.ints.clear();
								messageTeam.ints[EngineMessageKey::RESULT] = rtsDisp;
								sendToTcp(*client, &messageTeam);
								announcePlayerConnectionTeam(*client);
							}
							else
							{
								messageTeam.ints[EngineMessageKey::TEAM_ID] = -1;
								sendToTcp(*client, &messageTeam);
							}

						}
						break;
					case EngineMessageType::SELECT_GAMEPLAY:
						{
							ServerClient *client = findClient(message->ints[EngineMessageKey::PLAYER_NUMBER]);
							EngineMessage messageRep(m_manager);
							messageRep.message = EngineMessageType::SELECT_GAMEPLAY;
							messageRep.ints[EngineMessageKey::PLAYER_NUMBER] = client->id();
							if(message->ints[EngineMessageKey::GAMEPLAY_TYPE] == EngineMessageKey::RTS_GAMEPLAY)
							{
								if(client->joueur->equipe->getRTS() == nullptr)
								{
									messageRep.ints[EngineMessageKey::RESULT] = 1;
									client->joueur->equipe->setJoueurRTS(new JoueurRTS(client->joueur));
									client->joueur->setTypeGamplay(Joueur::TypeGameplay::RTS);
								}
								else 
								{
									messageRep.ints[EngineMessageKey::RESULT] = 0;
								}
							}
							else
							{
								messageRep.ints[EngineMessageKey::RESULT] = 1;
								client->joueur->equipe->addRPG(new JoueurRPG(client->joueur));
								client->joueur->setTypeGamplay(Joueur::TypeGameplay::RPG);
							}							
							messageRep.ints[EngineMessageKey::GAMEPLAY_TYPE] = message->ints[EngineMessageKey::GAMEPLAY_TYPE];
							sendToAllTcp(&messageRep);
						}
						break;
				}
				delete message;
            }
            while(client.tcp()->hasError())
            {
                std::cout << client.tcp()->getError().message() << std::endl;
            }
        }
    }
	while(m_udpConnexion->hasError())
	{
			std::cout << m_udpConnexion->getError().message() << std::endl;
	}
	while(m_udpConnexion->hasData())
	{
		auto data = m_udpConnexion->getData();
		boost::asio::ip::address adr = data.first.address();
		bool isClient=false;
		client_id cli_id;
		for(ServerClient client : clients)
		{
			if(client.tcp()->socket().remote_endpoint().address()==adr)
			{
				isClient = true;
				cli_id   = client.id();
				break;
			}
		}
		if(!isClient)
			continue;
		EngineMessage *message = deserialize(data.second);
		delete message;
	}
}
void ServerNetworkEngine::m_startAccept()
{
    TcpConnection::pointer connection = TcpConnection::create(m_service);
    m_acceptor.async_accept(connection->socket(),
                            boost::bind(&ServerNetworkEngine::m_handleAccept, this,
                                        connection, boost::asio::placeholders::error));
}
void ServerNetworkEngine::m_handleAccept(TcpConnection::pointer conn, const boost::system::error_code& e)
{
    if(!e)
    {
        {
            boost::mutex::scoped_lock l(m_mutex_clients);
            m_clients.push_back(ServerClient(conn, m_lastClient++));
            conn->setConnected(true);
            conn->startListen();
			ServerClient &client(m_clients.back());
			client.sel = SHA1(boost::lexical_cast<std::string>(client.id()) +
							client.tcp()->socket().remote_endpoint().address().to_string());
			EngineMessage messageSalt(m_manager);
			messageSalt.message = EngineMessageType::SETSALT;
			messageSalt.strings[EngineMessageKey::SEL] = client.sel;
			client.tcp()->send(serialize(&messageSalt));
		}
        m_startAccept();
    }
}
void ServerNetworkEngine::removeClient(ServerClient& c)
{
	EngineMessage message(m_manager);
	message.message = EngineMessageType::DEL_PLAYER;
	message.ints[EngineMessageKey::PLAYER_NUMBER] = c.joueur->id;
	{
		boost::mutex::scoped_lock l(m_mutex_clients);
    	for(auto it=m_clients.begin(); it!=m_clients.end(); ++it)
    	{
    	    if(it->tcp()==c.tcp())
    	    {
    	        m_clients.erase(it);
    	        break;
    	    }
    	}
	}
	sendToAllTcp(&message);
}
void ServerNetworkEngine::sendToAllTcp(EngineMessage* message)
{
    std::string data(NetworkEngine::serialize(message));

    boost::mutex::scoped_lock l(m_mutex_clients);
    for(ServerClient &c : m_clients)
    {
        sendToTcp(c,data);
    }
}
void ServerNetworkEngine::sendToTcp(ServerClient& c, EngineMessage* message)
{
    c.tcp()->send(NetworkEngine::serialize(message));
}
void ServerNetworkEngine::sendToTcp(ServerClient& c, std::string d)
{
    c.tcp()->send(d);
}
void ServerNetworkEngine::sendToAllExcluding(unsigned int id, EngineMessage* message)
{
    std::string data(NetworkEngine::serialize(message));

    boost::mutex::scoped_lock l(m_mutex_clients);
    for(ServerClient &c  :m_clients)
    {
        if(c.id()!=id)
            c.tcp()->send(data);
    }
}
void ServerNetworkEngine::setServerName(const std::string& name)
{
	m_server_name=name;	
}
void ServerNetworkEngine::setMaxClients(unsigned short number)
{
	m_max_clients=number;
}
void ServerNetworkEngine::setMapName(const std::string& name)
{
	m_map_name=name;	
}
EngineMessage* ServerNetworkEngine::m_createMapMessage()
{
	EngineMessage* message = new EngineMessage(m_manager);
	message->message = EngineMessageType::LOAD_MAP;
	message->strings[EngineMessageKey::MAP_NAME] = m_map_name;
	message->addToType(EngineType::GameEngineType);
	return message;
}
void ServerNetworkEngine::sendToTeam(Equipe* e, EngineMessage* message)
{
	boost::mutex::scoped_lock l(m_mutex_clients);
	for(ServerClient &c : m_clients)
	{
		for(Joueur *j : e->joueurs())
		{
			if(j == c.joueur)
			{
				sendToTcp(c, message);
				break;
			}
		}
	}
}
ServerClient* ServerNetworkEngine::findClient(client_id id)
{
	boost::mutex::scoped_lock l(m_mutex_clients);
	for(ServerClient &c : m_clients)
	{
		if(c.id() == id)
				return &c;
	}
	return nullptr;	
}
void ServerNetworkEngine::announcePlayerConnectionTeam(ServerClient &c)
{
	EngineMessage message(m_manager);
	message.message = EngineMessageType::NEW_PLAYER;
	message.ints[EngineMessageKey::PLAYER_NUMBER] = c.id();
	message.strings[EngineMessageKey::PSEUDO] = c.joueur->getNom();
	message.ints[EngineMessageKey::TEAM_ID] = c.joueur->equipe->id();
	if(c.joueur->getTypeGameplay() == Joueur::RPG)
		message.ints[EngineMessageKey::GAMEPLAY_TYPE] = EngineMessageKey::RPG_GAMEPLAY;
	else if(c.joueur->getTypeGameplay() == Joueur::RTS)
		message.ints[EngineMessageKey::GAMEPLAY_TYPE] = EngineMessageKey::RTS_GAMEPLAY;
	else
		message.ints[EngineMessageKey::GAMEPLAY_TYPE] = EngineMessageKey::NONE_GAMEPLAY;
	sendToAllExcluding(c.id(), &message);
}
