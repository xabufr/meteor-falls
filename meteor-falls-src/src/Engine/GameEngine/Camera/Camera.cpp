#include "Camera.h"

Camera::Camera()
{
    //ctor
}

Camera::~Camera()
{
    //dtor
}

void Camera::setCamera(Ogre::Camera* p_camera){
    m_camera = p_camera;
}

Ogre::Camera* Camera::getCamera(){
    return m_camera;
}
