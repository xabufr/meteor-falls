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
#include <CEGUI/String.h>
#include <SFML/System.hpp>
#include "../../Utils/Configuration/Config.h"
#include "Unites/Builder/BasicUniteBuilder.h"
#include "Unites/Builder/HeroBuilder.h"
#include "../ScriptEngine/MeshManager.h"
#include "Map/ObjetTerrainTypeManager.h"

#include <Utils/timeduration.h>


GameEngine::GameEngine(EngineManager* mng):
    Engine(mng)
{
    m_broadphase = new btDbvtBroadphase();
    m_collisionConfiguration = new btDefaultCollisionConfiguration();
    m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
    m_solver = new btSequentialImpulseConstraintSolver;

    m_world = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration);
    m_map = new Map(this, m_world);
    m_objectTypeManager = new ObjetTerrainTypeManager();

    MeshManager::get();
}
GameEngine::~GameEngine()
{
    delete m_map;
    delete m_world;
    delete m_solver;
    delete m_dispatcher;
    delete m_collisionConfiguration;
    delete m_broadphase;
}
void GameEngine::work(const TimeDuration &elapsed)
{
    m_world->stepSimulation(elapsed.seconds(), 5);
    if(m_map->getLoaded() == true)
    {
        m_map->update();
    }
    for(Equipe* e : m_teams)
        e->update(elapsed);
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
    e->factory()->addBuilder<TerrestreBuilder>();
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
btDiscreteDynamicsWorld* GameEngine::bulletWorld() const
{
    return m_world;
}
ObjetTerrainTypeManager* GameEngine::objetTerrainTypeManager() const
{
    return m_objectTypeManager;
}

const Map *GameEngine::getMap() const
{
    return m_map;
}
