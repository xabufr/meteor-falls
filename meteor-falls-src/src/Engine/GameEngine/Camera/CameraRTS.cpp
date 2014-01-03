#include "CameraRTS.h"
#include <OIS/OIS.h>
#include "Engine/GraphicEngine/Ogre/ogrecontextmanager.h"
#include "Engine/GraphicEngine/Ogre/OgreWindowInputManager.h"
#include "Engine/GameEngine/Map/Map.h"
#include <Utils/Configuration/CommandConfig.h>

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

void CameraRTS::update(int deltaTime){
    Ogre::Quaternion rotation(computeCameraRotation());
    Ogre::Vector3 deplacement(computeRelativeCameraMovements());

    float velocity = computeCameraVelocity();
    m_cameraPosition+= (rotation * deplacement * velocity);
    OIS::Mouse* mouse = OgreContextManager::get()->getInputManager()->getMouse();
    zoom(-0.1*mouse->getMouseState().Z.rel);

    m_cameraPosition.y = computeCameraAltitude(m_cameraPosition);
    m_camera->setPosition(m_cameraPosition);
    m_camera->setOrientation(rotation * computeCameraAngleAltitude());
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

Ogre::Quaternion CameraRTS::computeCameraRotation()
{
    if(m_commandConfig->eventActif(CommandConfig::RPG_KEY, CommandConfig::RPG_JUMP))
        m_yaw += 10;
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

Ogre::Quaternion CameraRTS::computeCameraAngleAltitude()
{

    float altitudeLookFactor = (m_relativeAltitude - m_minAltitude) / (m_maxAltitude - m_minAltitude);
    float altitudeAngle = (-altitudeLookFactor) * (m_maxAltitudeAngle - m_minAltitudeAngle) + m_minAltitudeAngle;
    return Ogre::Quaternion(Ogre::Radian(altitudeAngle), Ogre::Vector3(1, 0, 0));
}
