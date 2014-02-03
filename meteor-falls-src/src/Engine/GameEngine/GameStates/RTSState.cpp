#include <Engine/GameEngine/Camera/CameraRTS.h>
#include <Engine/GameEngine/GameStates/RTSState.h>
#include <Utils/Configuration/CommandConfig.h>
#include <Utils/rectangle.h>

#include "../ClientGameEngine.h"
#include "../Map/MapView.h"

#include "../Camera/CameraManager.h"

#include "Utils/Configuration/Config.h"
#include "../Unites/Unite.h"
#include "../Map/WorldObjectView.h"

#include "RTS/rtsselectionmanager.h"

RTSState::RTSState(StateManager *manager, ClientGameEngine *gameEngine) :
    State(manager), m_gameEngine(gameEngine), m_selectionManager(new RTSSelectionManager(this))
{
    m_commandConfig = Config::get()->getCommandConfig();
    m_camera = new CameraRTS(gameEngine->getMap(), m_commandConfig);
}

RTSState::~RTSState()
{
    delete m_selectionManager;
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

ret_code RTSState::work(const TimeDuration &elapsed)
{
    injectCameraEvents();
    return ret_code::CONTINUE;
}

void RTSState::injectCameraEvents()
{
}


Vector3D RTSState::getMouseProjectedPosition() const
{
    const MapView *mapView = m_gameEngine->getMapView();
    const Ogre::Camera *camera = m_gameEngine->cameraManager()->camera();
    CEGUI::Vector2f mousePosition = CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().getDisplayIndependantPosition();
    Ogre::Ray requestRay = camera->getCameraToViewportRay(mousePosition.d_x,mousePosition.d_y);
    boost::optional<Vector3D> mapPosition = mapView->getIntersection(requestRay);
    if(mapPosition.is_initialized()) {
        return *mapPosition;
    }
    //TODO: projeter sur le plan de la mer, voire passer ça dans la méthode de la map pour plus de cohérence
    return Vector3D(0,0,0);
}

std::vector<Unite*> RTSState::getUnitesInRectangle(const Rectangle<float> &rectangle) const
{
    std::vector<Unite*> foundUnits;
    for(Equipe* equipe : m_gameEngine->getTeams()) {
        for(Unite* unite : equipe->unites()) {
            Vector2D<float> positionUnite(unite->position().x, unite->position().z);
            if(rectangle.contains(positionUnite)) {
                foundUnits.push_back(unite);
            }
        }
    }
    return foundUnits;
}
