#include "GameEngine.h"
#include "../EngineManager/EngineManager.h"
#include "../GraphicEngine/GraphicEngine.h"
#include "Factions/Equipe.h"
#include "Factions/FactionManager.h"
#include "Preface/TeamState.h"
#include "../NetworkEngine/ServerNetworkEngine.h"

GameEngine::GameEngine(EngineManager* mng, Type t, Joueur* j):
    Engine(mng),
    m_type(t),
    m_change_sous_state(false)
{
    m_map = new Map(mng->getGraphic()->getSceneManager());
	m_sous_state = nullptr;
	m_type_sous_state = TypeState::TEAM_LIST;
	if(t==SERVER)
	{
		for(char i=1; i<3;++i)
		{
			m_current_joueur=nullptr;
			Equipe *e = new Equipe(i);
			e->setFaction(FactionManager::get()->getFaction(i));
			std::cout << FactionManager::get()->getFaction(i) << std::endl;
			addTeam(e);
		}
	}
	else
	{
        m_current_joueur = j;
		addPlayer(j);
	}
}
GameEngine::~GameEngine()
{
    if (m_sous_state != nullptr)
    {
        m_sous_state->exit();
        delete m_sous_state;
    }
  //  delete m_map;
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
			   			equipe = j->equipe;
			   	if(equipe==nullptr)
			   			return;
			   	net->sendToTeam(equipe, &message);
		   	}
		   	else if(message.ints[EngineMessageKey::RANGE] == EngineMessageKey::GLOBAL_RANGE)
		   		net->sendToAllTcp(&message);
		}
		else
		{
			CEGUI::String nom = "{ "+findJoueur(message.ints[EngineMessageKey::PLAYER_NUMBER])->getNom()+" }:"+message.strings[EngineMessageKey::MESSAGE];
            TeamState *team_state = (TeamState*)m_sous_state;
            team_state->setMessage(nom);
		}
	}
	else if (message.message==EngineMessageType::SELECT_GAMEPLAY)
    {
        if (message.ints[EngineMessageKey::RESULT] == 1)
        {
            switch (m_current_joueur->getTypeGameplay())
            {
                case Joueur::TypeGameplay::RTS:
                    m_current_joueur->setRTS(new JoueurRTS(m_current_joueur));
                break;
                case Joueur::TypeGameplay::RPG:
                    m_current_joueur->setRPG(new JoueurRPG(m_current_joueur));
                break;
            }
			Joueur *joueur = findJoueur(message.ints[EngineMessageKey::PLAYER_NUMBER]);
			if(joueur==nullptr)
				return;
			switch(message.ints[EngineMessageKey::GAMEPLAY_TYPE])
			{
				case EngineMessageKey::RTS_GAMEPLAY:
					if(joueur->getTypeGameplay()==Joueur::TypeGameplay::RTS)
						break;
					else if (joueur->getTypeGameplay() == Joueur::TypeGameplay::RPG) 
					{
						joueur->equipe->removeRPG(joueur->getRPG());
						delete joueur->getRPG();
					}
					joueur->setTypeGamplay(Joueur::TypeGameplay::RTS);
					joueur->setRTS(new JoueurRTS(joueur));
					joueur->equipe->setJoueurRTS(joueur->getRTS());
					break;
				case EngineMessageKey::RPG_GAMEPLAY:
					if(joueur->getTypeGameplay()==Joueur::TypeGameplay::RPG)
						break;
					else if (joueur->getTypeGameplay() == Joueur::TypeGameplay::RTS) 
					{
						joueur->equipe->setJoueurRTS(nullptr);
						delete joueur->getRTS();
					}
					joueur->setTypeGamplay(Joueur::TypeGameplay::RPG);
					joueur->setRPG(new JoueurRPG(joueur));
					joueur->equipe->addRPG(joueur->getRPG());
					break;
			}
        }
    }
	else if (message.message==EngineMessageType::DEL_PLAYER)
	{
		deleteJoueur(message.ints[EngineMessageKey::PLAYER_NUMBER]);
	}
}
void GameEngine::work()
{
    if(m_map->getLoaded() == true)
    {
        if (m_type == Type::CLIENT)
        {
            if (m_sous_state == nullptr)
            {
                m_sous_state = new TeamList(nullptr, this);
                m_sous_state->enter();
            }
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
                }
                m_sous_state->enter();
                m_change_sous_state = false;
            }
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
	return 0;
}
void GameEngine::setSousStateType(TypeState t)
{
    m_type_sous_state = t;
    m_change_sous_state = true;
}
bool GameEngine::tryJoinTeam(char id, Joueur* j)
{
	int nb_min=999, nb_cur = 9999;
	Equipe *eJoueur;
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
	if(nb_cur >= nb_min+3)
		return false;
	j->equipe=eJoueur;
	eJoueur->addJoueur(j);
	m_joueurs = eJoueur->joueurs();
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
	joueur->equipe->removeJoueur(joueur);
	switch(joueur->getTypeGameplay())
	{
		case Joueur::TypeGameplay::RTS:
			delete joueur->getRTS();
			joueur->equipe->setJoueurRTS(nullptr);
			break;
		case Joueur::TypeGameplay::RPG:
			joueur->equipe->removeRPG(joueur->getRPG());
			delete joueur->getRPG();
			break;
	}
	joueur->equipe->removeJoueur(joueur);
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
