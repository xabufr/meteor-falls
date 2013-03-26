#include "GameEngine.h"
#include "../EngineManager/EngineManager.h"
#include "../GraphicEngine/Ogre/ogrecontextmanager.h"
#include "../GraphicEngine/Ogre/OgreWindowInputManager.h"
#include "Factions/Equipe.h"
#include "Factions/FactionManager.h"
#include "Factions/Faction.h"
#include "../NetworkEngine/ServerNetworkEngine.h"
#include "../NetworkEngine/clientnetworkengine.h"
#include "Map/Map.h"
#include "Unites/UniteFactory.h"
#include "../EngineMessage/EngineMessage.h"
#include "Heros/ClasseHeroManager.h"
#include "Heros/Hero.h"
#include "Unites/Unite.h"
#include "Joueur/JoueurRPG.h"
#include <CEGUIString.h>
#include <SFML/System.hpp>
#include "../../Utils/Configuration/Config.h"
#include "Unites/Builder/BasicUniteBuilder.h"
#include "Unites/Builder/HeroBuilder.h"

GameEngine::GameEngine(EngineManager* mng):
    Engine(mng)
{
	m_map = new Map(this);
}
GameEngine::~GameEngine()
{
    delete m_map;
}
void GameEngine::work()
{
	static sf::Clock clock;
    if(m_map->getLoaded() == true)
    {
        m_map->update();
    }
	for(Equipe* e : m_teams)
		for(Unite *u : e->unites())
			u->update(clock.getElapsedTime().asMilliseconds());
	clock.restart();
}
EngineType GameEngine::getType()
{
    return EngineType::GameEngineType;
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
	e->factory()->addBuilder<BatimentBuilder>();
	e->factory()->addBuilder<HeroBuilder>();
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
Joueur* GameEngine::findJoueur(int id)
{
	for(Joueur *j : m_joueurs)
    {
		if(j->id()==id)
				return j;
    }
	return nullptr;
}
void GameEngine::deleteJoueur(int id)
{
	Joueur *joueur = findJoueur(id);
	if(joueur==nullptr)
		return;
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
