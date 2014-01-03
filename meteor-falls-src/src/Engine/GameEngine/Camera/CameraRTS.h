#ifndef CAMERARTS_H
#define CAMERARTS_H

#include "Camera.h"

class Map;
class CommandConfig;
class CameraRTS : public Camera
{
public:
    CameraRTS(const Map *map, CommandConfig *commandConfig);
    virtual ~CameraRTS();
    void setCamera(Ogre::Camera*);
    void update(int deltaTime);
    void zoom(int);

private:
    float computeCameraVelocity();
    float computeCameraAltitude(Ogre::Vector3 &position);
    Ogre::Quaternion computeCameraRotation();
    Ogre::Vector3 computeRelativeCameraMovements();
    Ogre::Quaternion computeCameraAngleAltitude();

private:
    float m_relativeAltitude;
    float m_yaw;
    float m_maxAltitude, m_minAltitude;
    float m_maxAltitudeAngle, m_minAltitudeAngle;
    float m_minVelocity, m_maxVelocity;
    const Map *m_map;
    Ogre::Vector3 m_cameraPosition;
    CommandConfig *m_commandConfig;
};

#endif // CAMERARTS_H
