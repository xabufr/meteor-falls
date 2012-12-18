#include "GameEngine.h"
#include "../EngineManager/EngineManager.h"
#include "../GraphicEngine/GraphicEngine.h"

GameEngine::GameEngine(EngineManager* mng, Type t):
    Engine(mng),
    m_type(t)
{
    std::cout << "teste 1" << std::endl;
    m_map = new Map(mng->getGraphic()->getSceneManager());
}
GameEngine::~GameEngine()
{
    delete m_map;
}
void GameEngine::handleMessage(const EngineMessage&)
{

}
void GameEngine::work()
{
    if(m_map->getLoaded() == true)
    {
        if (m_type == Type::CLIENT)
            if (m_sous_state == nullptr)
                m_sous_state = new TeamList(nullptr, this);
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
