#include "GameEngine.h"
#include "../EngineManager/EngineManager.h"
#include "../GraphicEngine/GraphicEngine.h"
#include "Factions/Equipe.h"
#include "Factions/FactionManager.h"
#include "Factions/Faction.h"
#include "Preface/TeamState.h"
#include "../NetworkEngine/ServerNetworkEngine.h"
#include "Map/Map.h"
#include "Unites/UniteFactory.h"
#include "Preface/TeamList.h"
#include "Preface/SpawnState.h"
#include "../EngineMessage/EngineMessage.h"
#include "Heros/ClasseHeroManager.h"
#include "Heros/Hero.h"
#include "Unites/Unite.h"
#include "Interface/Chat.h"
#include <CEGUIString.h>

GameEngine::GameEngine(EngineManager* mng, Type t, Joueur* j):
    Engine(mng),
    m_type(t),
    m_change_sous_state(true)
{
	if(t==SERVER)
		m_map = new Map(nullptr, this);
	else
		m_map = new Map(mng->getGraphic()->getSceneManager(), this);
	m_sous_state = nullptr;
	m_type_sous_state = TypeState::TEAM_LIST;
	if(t==SERVER)
	{
		for(char i=0; i<3;++i)
		{
			m_current_joueur=nullptr;
			Equipe *e = new Equipe(i);
			e->setFaction(FactionManager::get()->getFaction(1));
			addTeam(e);
		}
	}
	else
	{
	    m_chat = new Chat(this);
        m_current_joueur = j;
		addPlayer(j);
		setSousStateType(TypeState::TEAM_LIST);
	}
}
GameEngine::~GameEngine()
{
    if (m_sous_state != nullptr)
    {
        m_sous_state->exit();
        delete m_sous_state;
    }
    delete m_map;
    delete m_chat;
}
void GameEngine::handleMessage(EngineMessage& message)
{
	if(message.message==EngineMessageType::CHAT_MESSAGE)
	{
		if(m_type==SERVER)
		{
			ServerNetworkEngine *net = (ServerNetworkEngine*) m_manager->getNetwork();
			if(message.ints[EngineMessageKey::RANGE]==EngineMessageKey::TEAM_RANGE)
		   	{
			   	Equipe *equipe = nullptr;
			   	int playerId = message.ints[EngineMessageKey::PLAYER_NUMBER];
			   	for(Joueur *j : m_joueurs)
			   		if(j->id == playerId)
			   			equipe = j->equipe();
			   	if(equipe==nullptr)
			   			return;
			   	net->sendToTeam(equipe, &message);
		   	}
		   	else if(message.ints[EngineMessageKey::RANGE] == EngineMessageKey::GLOBAL_RANGE)
		   		net->sendToAllTcp(&message);
		}
		else
		{
			std::string nom = "\\[ "+findJoueur(message.ints[EngineMessageKey::PLAYER_NUMBER])->getNom()+" ]:"+message.strings[EngineMessageKey::MESSAGE];
            m_chat->addMessage(nom);
		}
	}
	else if (message.message==EngineMessageType::SELECT_GAMEPLAY)
    {
        if (message.ints[EngineMessageKey::RESULT] == 1)
        {
			Joueur *joueur = findJoueur(message.ints[EngineMessageKey::PLAYER_NUMBER]);
			if(joueur==nullptr)
				return;
			joueur->setTypeGamplay(message.ints[EngineMessageKey::GAMEPLAY_TYPE]==EngineMessageKey::RTS_GAMEPLAY?
							Joueur::TypeGameplay::RTS : Joueur::TypeGameplay::RPG);
			if(joueur == m_current_joueur)
			{
				setSousStateType(TypeState::SPAWN_STATE);
			}
        }
    }
	else if (message.message==EngineMessageType::DEL_PLAYER)
	{
		deleteJoueur(message.ints[EngineMessageKey::PLAYER_NUMBER]);
	}
	else if (message.message==EngineMessageType::SELECT_TEAM)
	{
		int team_id = message.ints[EngineMessageKey::TEAM_ID];
		if(team_id==-1)
			return;
		Joueur *joueur = findJoueur(message.ints[EngineMessageKey::PLAYER_NUMBER]);
		Equipe *equ = getEquipe(team_id);
		if(joueur==nullptr || equ == nullptr)
			return;
		joueur->changeTeam(equ);
		if(joueur == m_current_joueur)
		{
		}
	}
	else if (message.message==EngineMessageType::ADDOBJECT)
	{
		UnitId type       = message.ints[EngineMessageKey::OBJECT_TYPE];
		UnitId id         = message.ints[EngineMessageKey::OBJECT_ID];
		Vector3D position = message.positions[EngineMessageKey::OBJECT_POSITION];
		char teamId = message.ints[EngineMessageKey::TEAM_ID];
		Equipe *e   = getEquipe(teamId);
		Unite *unit = e->factory()->create(m_manager->getGraphic()->getSceneManager(), type, id);
		unit->setPosition(position);
	}
	else if (message.message==EngineMessageType::SPAWN)
	{
		Joueur *j = findJoueur(message.ints[EngineMessageKey::PLAYER_NUMBER]);
		if(j==nullptr||j->getTypeGameplay() != Joueur::TypeGameplay::RPG)
			return;
		if(m_type == SERVER)
		{
			Unite *unit = j->equipe()->getUnite(message.ints[EngineMessageKey::OBJECT_ID]);
			ClasseHero* cl = j->equipe()->faction()->getClassesManager().classe(message.ints[EngineMessageKey::CLASS_ID]);
			ServerNetworkEngine* net = (ServerNetworkEngine*) m_manager->getNetwork();
			if(cl==nullptr||unit==nullptr)
			{
				message.ints.clear();
				message.ints[EngineMessageKey::RESULT] = 0;
				message.ints[EngineMessageKey::ERROR_CODE] = SpawnState::ErrorMessages::INVALID_SPAWN;
				net->sendToTcp(j, &message);
			}
			else
			{
				Vector3D position(unit->getPosition());
				message.ints[EngineMessageKey::RESULT] = 1;
				message.positions[EngineMessageKey::OBJECT_POSITION];
				int id = j->equipe()->factory()->getNextId();
				message.ints[EngineMessageKey::OBJECT_ID] = id;
				net->sendToAllTcp(&message);

				Hero *hero = new Hero(nullptr, j->getRPG(), j->avatar(message.ints[EngineMessageKey::AVATAR_ID]),
					id);
				hero->setPosition(message.positions[EngineMessageKey::OBJECT_POSITION]);
			}
		}
		else
		{
			if(message.ints[EngineMessageKey::RESULT] == 1)
			{
				Vector3D position(message.positions[EngineMessageKey::OBJECT_POSITION]);
				Hero *hero = new Hero(nullptr, j->getRPG(), j->avatar(message.ints[EngineMessageKey::AVATAR_ID]),
						message.ints[EngineMessageKey::OBJECT_ID]);
				hero->setPosition(message.positions[EngineMessageKey::OBJECT_POSITION]);
				setSousStateType(TypeState::PLAYING);
			}
			else if(m_sous_state!=nullptr)
			{
				SpawnState* sous_state = dynamic_cast<SpawnState*>(m_sous_state);
				if(sous_state)
				{
					sous_state->notifySpawnError((SpawnState::ErrorMessages)message.ints[EngineMessageKey::ERROR_CODE]);
				}
			}
		}
	}
}
void GameEngine::work()
{
    if(m_map->getLoaded() == true)
    {
        if (m_type == Type::CLIENT)
        {
            if (m_change_sous_state)
            {
                if (m_sous_state != nullptr)
                {
                    m_sous_state->exit();
                    delete m_sous_state;
                }
                switch (m_type_sous_state)
                {
                    case TypeState::TEAM_LIST:
                        m_sous_state = new TeamList(nullptr, this);
                        break;
                    case TypeState::TEAM_STATE:
                        m_sous_state = new TeamState(nullptr, this);
                        break;
					case TypeState::SPAWN_STATE:
						m_sous_state = new SpawnState(nullptr, this);
						break;
					default:
						m_sous_state = nullptr;
						break;
                }
				if(m_sous_state != nullptr)
	                m_sous_state->enter();
                m_change_sous_state = false;
            }
			if(m_sous_state)
				m_sous_state->work(0);
        }
        m_map->update();
    }
}
EngineType GameEngine::getType()
{
    return EngineType::GameEngineType;
}
Joueur* GameEngine::getCurrentJoueur()
{
    return m_current_joueur;
}
void GameEngine::loadMap(const std::string &map_name)
{
	m_map->load(map_name);
}
const std::vector<Equipe*>& GameEngine::getTeams() const
{
	return m_teams;
}
void GameEngine::addTeam(Equipe* e)
{
	m_teams.push_back(e);
}
void GameEngine::addPlayer(Joueur* j)
{
	m_joueurs.push_back(j);
}
Equipe* GameEngine::getEquipe(char id)
{
	for(Equipe *e : m_teams)
	{
		if(e->id() == id)
			return e;
	}
	return nullptr;
}
void GameEngine::setSousStateType(TypeState t)
{
    m_type_sous_state = t;
    m_change_sous_state = true;
}
bool GameEngine::tryJoinTeam(char id, Joueur* j)
{
	int nb_min=999, nb_cur = 9999;
	Equipe *eJoueur = nullptr;
	for(Equipe *e : m_teams)
	{
		int nb = e->joueurs().size();
		if(nb<nb_min)
			nb_min=nb;
		if(id==e->id())
		{
			nb_cur = nb;
			eJoueur = e;
		}
	}
	if(eJoueur==nullptr || nb_cur >= nb_min+3)
		return false;

	j->changeTeam(eJoueur);

	return true;
}
Joueur* GameEngine::findJoueur(int id)
{
    if (m_current_joueur!=nullptr && m_current_joueur->id == id)
        return m_current_joueur;
	for(Joueur *j : m_joueurs)
    {
		if(j->id==id)
				return j;
    }
	return nullptr;
}
void GameEngine::deleteJoueur(int id)
{
	Joueur *joueur = findJoueur(id);
	if(joueur==nullptr)
		return;
	joueur->changeTeam(nullptr);
	for(auto it=m_joueurs.begin();it!=m_joueurs.end();++it)
	{
		if(*it==joueur)
		{
			m_joueurs.erase(it);
			break;
		}
	}
	delete joueur;
}
GameEngine::Type GameEngine::getTypeServerClient() const
{
	return m_type;
}
