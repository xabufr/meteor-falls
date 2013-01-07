#include "GameState.h"
#include "../StateManager.h"
#include "Engine/EngineManager/EngineManager.h"
#include "Engine/GraphicEngine/Ogre/ogrecontextmanager.h"
#include "Engine/GraphicEngine/Ogre/OgreWindowInputManager.h"

GameState::GameState(StateManager* mng, const EngineManager::Type t, const std::string& address, const std::string& password, Joueur *j):
    State(mng),
    m_address(address),
    m_password(password),
    m_player(j),
    m_type(t)
{
    std::cout << "teste 2" << std::endl;
    m_keyboard = OgreContextManager::get()->getInputManager()->getKeyboard();
}
GameState::~GameState()
{
    delete m_player;
}
ret_code GameState::work(unsigned int time)
{
    m_engineManager->work();
    if (m_keyboard->isKeyDown(OIS::KC_ESCAPE))
	{
		std::cout << "term" << std::endl;
        return ret_code::FINISHED;
	}
    return ret_code::CONTINUE;
}
bool GameState::isVisible()
{
    return m_visible;
}
void GameState::enter()
{
    m_engineManager = new EngineManager(m_type, m_address, m_password, m_player);
    m_visible = true;
}
void GameState::exit()
{
    delete m_engineManager;
    m_visible = false;
}
