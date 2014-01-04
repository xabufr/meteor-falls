#include "CameraRTS.h"
#include <OIS/OIS.h>
#include "Engine/GraphicEngine/Ogre/ogrecontextmanager.h"
#include "Engine/GraphicEngine/Ogre/OgreWindowInputManager.h"
#include "Engine/GameEngine/Map/Map.h"
#include <Utils/Configuration/CommandConfig.h>
#include <Utils/timeduration.h>
#include <algorithm>

CameraRTS::CameraRTS(const Map *map, CommandConfig *commandConfig): m_map(map), m_commandConfig(commandConfig)
{
    m_maxAltitude = 500;
    m_minAltitude = 2;
    m_maxAltitudeAngle = 3.14 / 2.f;
    m_minAltitudeAngle = 0.02;
    m_minVelocity = 5;
    m_maxVelocity = 25;
}

CameraRTS::~CameraRTS()
{
}

void CameraRTS::setCamera(Ogre::Camera* p_camera){
    m_camera = p_camera;
}

void CameraRTS::update(const TimeDuration &elapsed){
    Ogre::Quaternion rotation(computeCameraRotation(elapsed));
    Ogre::Vector3 deplacement(computeRelativeCameraMovements());

    float velocity = computeCameraVelocity();
    m_cameraPosition+= (rotation * deplacement * velocity * elapsed.seconds());
    OIS::Mouse* mouse = OgreContextManager::get()->getInputManager()->getMouse();
    zoom(-elapsed.seconds()*mouse->getMouseState().Z.rel);

    m_cameraPosition.y = computeCameraAltitude(m_cameraPosition);
    Ogre::Radian cameraAngleAltitude = computeCameraAngleAltitude();
    correctCameraPosition(cameraAngleAltitude);
    m_camera->setPosition(m_cameraPosition);
    m_camera->setOrientation(rotation * Ogre::Quaternion(cameraAngleAltitude, Ogre::Vector3(1,0,0)));
}

void CameraRTS::zoom(int p_tour)
{
    m_relativeAltitude += p_tour;
    if(m_relativeAltitude > m_maxAltitude) {
        m_relativeAltitude = m_maxAltitude;
    } else if(m_relativeAltitude < m_minAltitude) {
        m_relativeAltitude = m_minAltitude;
    }
}

float CameraRTS::computeCameraVelocity()
{
    float velocity = (m_relativeAltitude - m_minAltitude) / (m_maxAltitude - m_minAltitude);
    velocity = velocity * (m_maxVelocity - m_minVelocity) + m_minVelocity;
    return velocity;
}

float CameraRTS::computeCameraAltitude(Ogre::Vector3 &position)
{
    float altitude = m_relativeAltitude;
    altitude += m_map->getHeightAt(position.x, position.z);
    return altitude;
}

void CameraRTS::correctCameraPosition(const Ogre::Radian &angleAltitude)
{
    const Rectangle<float> &mapBounds = m_map->bounds();

    float deltaAngle = 0.f;
    Ogre::Radian finalAngle = Ogre::Degree(90)+angleAltitude;
    if(finalAngle.valueDegrees() <= 80) {
        deltaAngle = m_relativeAltitude * Ogre::Math::Tan(Ogre::Degree(90)+angleAltitude);
    }

    m_cameraPosition.x = std::max(mapBounds.left - deltaAngle, m_cameraPosition.x);
    m_cameraPosition.x = std::min(mapBounds.left + mapBounds.width + deltaAngle, m_cameraPosition.x);
    m_cameraPosition.z = std::max(mapBounds.top - deltaAngle, m_cameraPosition.z);
    m_cameraPosition.z = std::min(mapBounds.top + mapBounds.height + deltaAngle, m_cameraPosition.z);
}

Ogre::Quaternion CameraRTS::computeCameraRotation(const TimeDuration &elapsed)
{
    if(m_commandConfig->eventActif(CommandConfig::RPG_KEY, CommandConfig::RPG_JUMP))
        m_yaw += 10 * elapsed.seconds();
    return Ogre::Quaternion(Ogre::Degree(m_yaw), Ogre::Vector3(0,1,0));
}

Ogre::Vector3 CameraRTS::computeRelativeCameraMovements()
{
    Ogre::Vector3 deplacement(0,0,0);
    CEGUI::Vector2f relativeMousePosition = CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().getDisplayIndependantPosition();
    if(m_commandConfig->eventActif(CommandConfig::RPG_KEY, CommandConfig::RPG_FORWARD) || relativeMousePosition.d_y <= 0.02)
        deplacement.z += -10;
    if(m_commandConfig->eventActif(CommandConfig::RPG_KEY, CommandConfig::RPG_BACKWARD) || relativeMousePosition.d_y >= 0.98)
        deplacement.z += 10;
    if(m_commandConfig->eventActif(CommandConfig::RPG_KEY, CommandConfig::RPG_RIGHT) || relativeMousePosition.d_x >= 0.98)
        deplacement.x += 10;
    if(m_commandConfig->eventActif(CommandConfig::RPG_KEY, CommandConfig::RPG_LEFT) || relativeMousePosition.d_x <= 0.02)
        deplacement.x += -10;

    return deplacement;
}

Ogre::Radian CameraRTS::computeCameraAngleAltitude()
{

    float altitudeLookFactor = (m_relativeAltitude - m_minAltitude) / (m_maxAltitude - m_minAltitude);
    float altitudeAngle = (-altitudeLookFactor) * (m_maxAltitudeAngle - m_minAltitudeAngle) + m_minAltitudeAngle;
    return Ogre::Radian(altitudeAngle);
}
