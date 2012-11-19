#include "GameEngine.h"

/*GameEngine::GameEngine()
{
    //ctor
}

GameEngine::~GameEngine()
{
    //dtor
}*/

void GameEngine::handleMessage(const EngineMessage&){

}

void GameEngine::work(){
    m_map->update();
}
