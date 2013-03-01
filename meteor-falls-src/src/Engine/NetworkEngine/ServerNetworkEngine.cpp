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
#include "../GameEngine/Unites/Unite.h"
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
void ServerNetworkEngine::handleMessage(EngineMessage&)
{

}
void ServerNetworkEngine::work()
{
	const long pingTimeout = 10000;
	std::vector<ServerClient> clients;
	{
		boost::recursive_mutex::scoped_lock l(m_mutex_clients);
		for(auto it=m_clients.begin();it!=m_clients.end();)
		{
			if(it->data->toDel)
				it = m_clients.erase(it);
			else
			{
				++it;
			}
			clients = m_clients;
		}
	}
	EngineMessage *message;
	for(ServerClient& client : clients)
	{
		if(!client.tcp()->isConnected()||!client.tcp()->isListening()
				||(client.data->waitingPing && client.data->timePing.getTime() >= pingTimeout)||client.tcp()->hasError())
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
							bool alertOther = client->joueur->equipe() == nullptr;
							bool canJoin = m_manager->getGame()->tryJoinTeam(teamId, client->joueur);
							EngineMessage messageTeam(m_manager);
							messageTeam.message = EngineMessageType::SELECT_TEAM;
							messageTeam.ints[EngineMessageKey::PLAYER_NUMBER] = client->id();
							if(canJoin)
							{
								if(alertOther)
									announcePlayerConnectionTeam(*client);
								messageTeam.ints[EngineMessageKey::TEAM_ID] = teamId;
								sendToAllTcp(&messageTeam);
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
								if(client->joueur->equipe()->getRTS() == nullptr)
								{
									messageRep.ints[EngineMessageKey::RESULT] = 1;
								}
								else
								{
									messageRep.ints[EngineMessageKey::RESULT] = 0;
								}
							}
							else
							{
								messageRep.ints[EngineMessageKey::RESULT] = 1;
							}
							messageRep.ints[EngineMessageKey::GAMEPLAY_TYPE] = message->ints[EngineMessageKey::GAMEPLAY_TYPE];
							sendToAllTcp(&messageRep);
							messageRep.addToType(EngineType::GameEngineType);
							m_manager->addMessage(EngineMessage::clone(&messageRep));
						}
						break;
					case EngineMessageType::SYNC_TIME:
						{
							EngineMessage messageTime(m_manager);
							messageTime.message = EngineMessageType::SYNC_TIME;
							messageTime.time    = m_clock.getTime();
							sendToTcp(client, &messageTime);
						}
						break;
					case EngineMessageType::PING:
						{
							client.data->timeSinceLastPingRep.reset();
							client.data->waitingPing = false;
							client.joueur->ping = client.data->timePing.getTime()/2;
							sendSetPing(client);
						}
						break;
					case EngineMessageType::GETOBJECTSLIST:
						{
							for(Equipe *e : m_manager->getGame()->getTeams())
							{
								for(Unite *u : e->unites())
								{
									if(!u->type()) //C'est un héro, nécessite une synchro plus poussée (avatar)
										continue;
									EngineMessage messageUnit(m_manager);
									messageUnit.message = EngineMessageType::ADDOBJECT;
									messageUnit.positions[EngineMessageKey::OBJECT_POSITION] = u->getPosition();
									messageUnit.ints[EngineMessageKey::TEAM_ID] = e->id();
									messageUnit.ints[EngineMessageKey::OBJECT_ID] = u->id();
									messageUnit.ints[EngineMessageKey::OBJECT_TYPE] = u->type()->id();
									sendToTcp(client, &messageUnit);
								}
								//Synchro des héros
								for(JoueurRPG *j : e->getRPG())
								{
									if(!j->hero())
										continue;
									EngineMessage messageHero(m_manager);
									messageHero.message = EngineMessageType::SPAWN;
									messageHero.ints[EngineMessageKey::PLAYER_NUMBER] = j->joueur()->id;
									j->hero()->avatar()->serialize(&messageHero);
									messageHero.ints[EngineMessageKey::OBJECT_ID] = j->hero()->id();
									messageHero.positions[EngineMessageKey::OBJECT_POSITION] = j->hero()->getPosition();
									messageHero.addToType(EngineType::GameEngineType);
									messageHero.ints[EngineMessageKey::RESULT] = 1;
									sendToTcp(client, &messageHero);
								}
							}
						}
						break;
					case EngineMessageType::SPAWN:
						{
							EngineMessage *messageSpawn = EngineMessage::clone(message);
							m_manager->addMessage(messageSpawn);
						}
						break;
					case EngineMessageType::PLAYER_POSITION:
						{
							Joueur *j = m_manager->getGame()->findJoueur(message->ints[EngineMessageKey::PLAYER_NUMBER]);
							if(j&&j->getTypeGameplay()==Joueur::TypeGameplay::RPG&&j->getRPG()->hero())
							{
								j->getRPG()->hero()->setPosition(message->positions[EngineMessageKey::OBJECT_POSITION]);
								sendToAllExcluding(client.id(), message);
							}
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
		UdpConnection::Data data(m_udpConnexion->getData());
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
		switch(message->message)
		{
		}
		delete message;
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
void ServerNetworkEngine::m_handleAccept(TcpConnection::pointer conn, const boost::system::error_code& e)
{
	if(!e)
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
			messageSalt.message = EngineMessageType::SETSALT;
			messageSalt.strings[EngineMessageKey::SEL] = client.data->sel;
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
		boost::recursive_mutex::scoped_lock l(m_mutex_clients);
		for(auto it=m_clients.begin(); it!=m_clients.end(); ++it)
		{
			if(it->tcp()==c.tcp())
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
void ServerNetworkEngine::sendToAllTcp(EngineMessage* message)
{
	std::string data(NetworkEngine::serialize(message));

	boost::recursive_mutex::scoped_lock l(m_mutex_clients);
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

	boost::recursive_mutex::scoped_lock l(m_mutex_clients);
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
	m_manager->getGame()->loadMap(name);
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
	boost::recursive_mutex::scoped_lock l(m_mutex_clients);
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
	boost::recursive_mutex::scoped_lock l(m_mutex_clients);
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
	message.ints[EngineMessageKey::TEAM_ID] = c.joueur->equipe()->id();
	if(c.joueur->getTypeGameplay() == Joueur::RPG)
		message.ints[EngineMessageKey::GAMEPLAY_TYPE] = EngineMessageKey::RPG_GAMEPLAY;
	else if(c.joueur->getTypeGameplay() == Joueur::RTS)
		message.ints[EngineMessageKey::GAMEPLAY_TYPE] = EngineMessageKey::RTS_GAMEPLAY;
	else
		message.ints[EngineMessageKey::GAMEPLAY_TYPE] = EngineMessageKey::NONE_GAMEPLAY;
	sendToAllExcluding(c.id(), &message);
}
void ServerNetworkEngine::pingClients()
{
	boost::recursive_mutex::scoped_lock l(m_mutex_clients);
	for(ServerClient& c : m_clients)
	{
		if(!c.data->waitingPing && c.data->timeSinceLastPingRep.getTime() > 2000)
		{
			c.data->waitingPing = true;
			EngineMessage mess(m_manager);
			mess.message = EngineMessageType::PING;
			sendToTcp(c, &mess);
			c.data->timePing.reset();
		}
	}
}
void ServerNetworkEngine::sendSetPing(ServerClient& c)
{
	EngineMessage mess(m_manager);
	mess.message = EngineMessageType::SET_PING;
	mess.ints[EngineMessageKey::TIME] = c.joueur->ping;
	mess.ints[EngineMessageKey::PLAYER_NUMBER] = c.joueur->id;
	sendToAllTcp(&mess);
}
void ServerNetworkEngine::sendToTcp(Joueur* j, EngineMessage* message)
{
	boost::recursive_mutex::scoped_lock(m_mutex_clients);
	for(ServerClient &c : m_clients)
	{
		if(c.joueur == j)
		{
			sendToTcp(c, message);
			return;
		}
	}
}
