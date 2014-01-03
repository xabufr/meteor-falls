#include <Engine/GameEngine/Camera/CameraRTS.h>
#include <Engine/GameEngine/GameStates/RTSState.h>
#include <Utils/Configuration/CommandConfig.h>

#include "../ClientGameEngine.h"

#include "../Camera/CameraManager.h"

#include "Utils/Configuration/Config.h"

RTSState::RTSState(StateManager *manager, ClientGameEngine *gameEngine) :
        State(manager), m_gameEngine(gameEngine)
{
    m_commandConfig = Config::get()->getCommandConfig();
    m_camera = new CameraRTS(gameEngine->getMap(), m_commandConfig);
}

RTSState::~RTSState()
{
}

bool RTSState::isVisible()
{
    return true;
}

void RTSState::enter()
{
    CameraManager* cameraManager = m_gameEngine->cameraManager();
    cameraManager->setCameraContener(m_camera);
}

void RTSState::exit()
{
}

ret_code RTSState::work(unsigned int time)
{
    injectCameraEvents();
    return ret_code::CONTINUE;
}

void RTSState::injectCameraEvents()
{
}
