#include "GameState.h"
#include "../StateManager.h"
#include "Engine/EngineManager/EngineManager.h"
#include "Engine/GraphicEngine/Ogre/ogrecontextmanager.h"
#include "Engine/GraphicEngine/Ogre/OgreWindowInputManager.h"

GameState::GameState(StateManager* mng):
    State(mng)
{
    m_keyboard = OgreContextManager::get()->getInputManager()->getKeyboard();
}

GameState::~GameState()
{

}
ret_code GameState::work(unsigned int time)
{
    m_engineManager->work();
    if (m_keyboard->isKeyDown(OIS::KC_ESCAPE))
        return ret_code::EXIT_PROGRAM;
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
