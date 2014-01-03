#include "Camera.h"

Camera::Camera()
{
    m_camera = nullptr;
}

Camera::~Camera()
{
}

void Camera::setCamera(Ogre::Camera* p_camera){
    m_camera = p_camera;
}

Ogre::Camera* Camera::getCamera(){
    return m_camera;
}
