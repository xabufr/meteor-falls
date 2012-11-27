#include "GameState.h"
#include "../StateManager.h"
#include "Engine/EngineManager/EngineManager.h"

GameState::GameState(StateManager* mng):
    State(mng)
{

}

GameState::~GameState()
{

}
ret_code GameState::work()
{
    m_engineManager->work();
    return ret_code::CONTINUE;
}

void GameState::enter()
{
    m_engineManager = new EngineManager(EngineManager::Type::CLIENT);
}

void GameState::exit()
{
    delete m_engineManager;
}
