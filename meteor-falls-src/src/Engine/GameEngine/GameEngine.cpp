#include "GameEngine.h"
#include "../EngineManager/EngineManager.h"
#include "../GraphicEngine/GraphicEngine.h"

GameEngine::GameEngine(EngineManager* mng, Type t):
    Engine(mng),
    m_type(t)
{
//    m_map = new Map(mng->getGraphic()->getSceneManager());
}


GameEngine::~GameEngine()
{
  //  delete m_map;
}

void GameEngine::handleMessage(const EngineMessage&){

}

void GameEngine::work(){
    /*if(m_map->getLoaded() == true)
        m_map->update();
    else
        m_map->load("test");*/
}
EngineType GameEngine::getType()
{
    return EngineType::GameEngineType;
}
