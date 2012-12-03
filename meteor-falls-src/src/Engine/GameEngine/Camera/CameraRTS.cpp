#include "CameraRTS.h"
#include <OIS/OIS.h>
#include "Engine/GraphicEngine/Ogre/ogrecontextmanager.h"
#include "Engine/GraphicEngine/Ogre/OgreWindowInputManager.h"

CameraRTS::CameraRTS()
{
    //ctor
}

CameraRTS::~CameraRTS()
{
    //dtor
}

void CameraRTS::setCamera(Ogre::Camera* p_camera){
    m_camera = p_camera;
    m_camera->setPosition(Ogre::Vector3(0, 200, 0));
    m_camera->lookAt(Ogre::Vector3(0, 0, 0));
}

void CameraRTS::update(int){
    OIS::Mouse* mouse;
    mouse = OgreContextManager::get()->getInputManager()->getMouse();

    if(m_forward)
        m_camera->move(Ogre::Vector3(0, 0, -10));
    if(m_back)
        m_camera->move(Ogre::Vector3(0, 0, 10));
    if(m_right)
        m_camera->move(Ogre::Vector3(10, 0, 0));
    if(m_left)
        m_camera->move(Ogre::Vector3(-10, 0, 0));
    zoom(-0.1*mouse->getMouseState().Z.rel);
}

void CameraRTS::forward(bool p_forward){
    m_forward = p_forward;
}

void CameraRTS::back(bool p_back){
    m_back = p_back;
}

void CameraRTS::right(bool p_right){
    m_right = p_right;
}

void CameraRTS::left(bool p_left){
    m_left = p_left;
}

void CameraRTS::zoom(int p_tour){
    Ogre::Vector3 cam_pos = m_camera->getPosition();
    int temp = cam_pos[1] + p_tour;
    if(temp > 500){
        int surplus = temp - 500;
        m_camera->setPosition(cam_pos[0], cam_pos[1] + p_tour - surplus, cam_pos[2]);
    }
    else if(temp < 100){
        int surplus = 100 - temp;
        m_camera->setPosition(cam_pos[0], cam_pos[1] + p_tour + surplus, cam_pos[2]);
    }
    else
        m_camera->setPosition(cam_pos[0], cam_pos[1] + p_tour, cam_pos[2]);
}
