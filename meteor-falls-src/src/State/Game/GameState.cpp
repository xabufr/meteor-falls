#include "GameState.h"
#include "../StateManager.h"
#include "Engine/EngineManager/EngineManager.h"
#include "Engine/GraphicEngine/Ogre/ogrecontextmanager.h"
#include "Engine/GraphicEngine/Ogre/OgreWindowInputManager.h"

GameState::GameState(StateManager* mng, const EngineManager::Type t, const std::string& address, const std::string& password):
    State(mng),
    m_address(address),
    m_password(password),
    m_type(t)
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

bool GameState::isVisible()
{
    return m_visible;
}

void GameState::enter()
{
    m_engineManager = new EngineManager(m_type, m_address, m_password);
    m_visible = true;
}

void GameState::exit()
{
    delete m_engineManager;
    m_visible = false;
}
