#include "../../meteor-falls-src/src/Engine/GameEngine/GameEngine.h"

GameEngine::GameEngine(EngineManager* mng, Type t):
    Engine(mng),
    m_type(t)
{

}


GameEngine::~GameEngine()
{
    //dtor
}

void GameEngine::handleMessage(const EngineMessage&){

}

void GameEngine::work(){
    m_map->update();
}
EngineType GameEngine::getType()
{
    return EngineType::GameEngineType;
}
