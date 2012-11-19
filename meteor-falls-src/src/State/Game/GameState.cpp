#include "GameState.h"
#include "../StateManager.h"
#include "Engine/EngineManager/EngineManager.h"

GameState::GameState(StateManager* mng):
    State(mng)
{
    m_engineManager = new EngineManager(EngineManager::Type::CLIENT);
}

GameState::~GameState()
{
    delete m_engineManager;
}
ret_code GameState::work()
{
    m_engineManager->work();
    return ret_code::CONTINUE;
}

void GameState::enter()
{

}

void GameState::exit()
{

}
