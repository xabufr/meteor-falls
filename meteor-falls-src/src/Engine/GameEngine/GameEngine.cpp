#include "GameEngine.h"
#include "../EngineManager/EngineManager.h"
#include "../GraphicEngine/GraphicEngine.h"
#include "Factions/Equipe.h"
#include "Factions/FactionManager.h"

GameEngine::GameEngine(EngineManager* mng, Type t):
    Engine(mng),
    m_type(t)
{
    std::cout << "teste 1" << std::endl;
    m_map = new Map(mng->getGraphic()->getSceneManager());
	m_sous_state = nullptr;
	if(t==SERVER)
	{
		for(char i=1; i<3;++i)
		{
			Equipe *e = new Equipe(i);
			e->setFaction(FactionManager::get()->getFaction(i));
			std::cout << FactionManager::get()->getFaction(i) << std::endl;
			addTeam(e);
		}
	}
}
GameEngine::~GameEngine()
{
  //  delete m_map;
}
void GameEngine::handleMessage(EngineMessage& message)
{
	if(message.message==EngineMessageType::CHAT_MESSAGE)
	{
		if(message.ints[EngineMessageKey::RANGE]==EngineMessageKey::TEAM_RANGE)
		{
			if(m_type==SERVER)
			{
			}
			else
			{

			}
		}
		else
		{

		}
	}
}
void GameEngine::work()
{
    if(m_map->getLoaded() == true)
    {
        if (m_type == Type::CLIENT)
        {
            if (m_sous_state == nullptr)
                m_sous_state = new TeamList(nullptr, this);
            m_sous_state->work(0);
        }
        m_map->update();
    }
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
