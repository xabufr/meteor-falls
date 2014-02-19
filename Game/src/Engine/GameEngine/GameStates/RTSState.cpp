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

#include <Engine/EngineManager/EngineManager.h>
#include <Engine/GraphicEngine/GraphicEngine.h>

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


Ogre::Ray RTSState::getMouseRay() const
{
    const Ogre::Camera *camera = m_gameEngine->cameraManager()->camera();
    CEGUI::Vector2f mousePosition = CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().getDisplayIndependantPosition();
    Ogre::Ray requestRay = camera->getCameraToViewportRay(mousePosition.d_x,mousePosition.d_y);

    return requestRay;
}

Vector3D RTSState::getMouseProjectedPosition() const
{
    const MapView *mapView = m_gameEngine->getMapView();
    Ogre::Ray requestRay = getMouseRay();
    boost::optional<Vector3D> mapPosition = mapView->getIntersection(requestRay);
    if(mapPosition.is_initialized()) {
        return *mapPosition;
    }
    //TODO: projeter sur le plan de la mer, voire passer ça dans la méthode de la map pour plus de cohérence
    return Vector3D(0,0,0);
}

std::vector<Unite*> RTSState::getUnitesInRectangleUnderCamera(const Rectangle<float> &rectangle) const
{
    Ogre::PlaneBoundedVolume vol;
    Ogre::Camera *camera = m_gameEngine->cameraManager()->camera();
    Ogre::Ray topLeft = camera->getCameraToViewportRay(rectangle.left, rectangle.top);
    Ogre::Ray topRight = camera->getCameraToViewportRay(rectangle.left + rectangle.width, rectangle.top);
    Ogre::Ray bottomLeft = camera->getCameraToViewportRay(rectangle.left, rectangle.top + rectangle.height);
    Ogre::Ray bottomRight = camera->getCameraToViewportRay(rectangle.left + rectangle.width, rectangle.top + rectangle.height);

    vol.planes.push_back(Ogre::Plane(topLeft.getPoint(1), topRight.getPoint(1), bottomRight.getPoint(1)));         // front plane
    vol.planes.push_back(Ogre::Plane(topLeft.getOrigin(), topLeft.getPoint(100), topRight.getPoint(100)));         // top plane
    vol.planes.push_back(Ogre::Plane(topLeft.getOrigin(), bottomLeft.getPoint(100), topLeft.getPoint(100)));       // left plane
    vol.planes.push_back(Ogre::Plane(bottomLeft.getOrigin(), bottomRight.getPoint(100), bottomLeft.getPoint(100)));   // bottom plane
    vol.planes.push_back(Ogre::Plane(topRight.getOrigin(), topRight.getPoint(100), bottomRight.getPoint(100)));     // right plane

    Ogre::PlaneBoundedVolumeList volList;
    volList.push_back(vol);

    EngineManager *mng = m_gameEngine->getManager();

    Ogre::PlaneBoundedVolumeListSceneQuery *query = mng->getGraphic()->getSceneManager()->createPlaneBoundedVolumeQuery(volList);
    Ogre::SceneQueryResult result = query->execute();

    std::vector<Unite*> foundUnits;
    std::for_each(result.movables.begin(), result.movables.end(), [&foundUnits](Ogre::MovableObject *obj) {
        try {
            WorldObject *worldObj = Ogre::any_cast<WorldObject*>(obj->getUserObjectBindings().getUserAny());
            Unite *unite = dynamic_cast<Unite*>(worldObj);
            foundUnits.push_back(unite);
        } catch(...) {
        }
    });

    return foundUnits;
}

WorldObject *RTSState::getObjectUnderRay(const Ogre::Ray & ray) const
{
    EngineManager *mng = m_gameEngine->getManager();
    Ogre::RaySceneQuery *query = mng->getGraphic()->getSceneManager()->createRayQuery(ray);
    Ogre::RaySceneQueryResult& queryResult = query->execute();

    for(Ogre::RaySceneQueryResultEntry &entry : queryResult) {
        if(entry.movable) {
            WorldObject *worldObject;
            try {
            worldObject = Ogre::any_cast<WorldObject*>(entry.movable->getUserObjectBindings().getUserAny());
            if(worldObject)
                return worldObject;
            } catch (...) {}
        }
    }
    mng->getGraphic()->getSceneManager()->destroyQuery(query);

    return nullptr;
}


ClientGameEngine *RTSState::game()
{
    return m_gameEngine;
}
