#include "CameraLibre.h"
#include <OIS/OIS.h>
#include "Engine/GraphicEngine/Ogre/ogrecontextmanager.h"
#include "Engine/GraphicEngine/Ogre/OgreWindowInputManager.h"

CameraLibre::CameraLibre()
{
    m_angle_up_down = 0;
}

CameraLibre::~CameraLibre()
{
    //dtor
}

void CameraLibre::update(const TimeDuration &elapsed){
    OIS::Mouse* mouse;
    mouse = OgreContextManager::get()->getInputManager()->getMouse();

    if(m_forward)
        m_camera->moveRelative(Ogre::Vector3(0, 0, -10));
    if(m_back)
        m_camera->moveRelative(Ogre::Vector3(0, 0, 10));
    if(m_right)
        m_camera->moveRelative(Ogre::Vector3(10, 0, 0));
    if(m_left)
        m_camera->moveRelative(Ogre::Vector3(-10, 0, 0));
    lookRightLeft(Ogre::Degree(-0.03*mouse->getMouseState().X.rel));
    lookUpDown(Ogre::Degree(-0.03*mouse->getMouseState().Y.rel));
}

void CameraLibre::forward(bool p_forward){
    m_forward = p_forward;
}

void CameraLibre::back(bool p_back){
    m_back = p_back;
}

void CameraLibre::right(bool p_right){
    m_right = p_right;
}

void CameraLibre::left(bool p_left){
    m_left = p_left;
}

void CameraLibre::lookUpDown(Ogre::Degree p_degree){
    Ogre::Degree angle_temp = m_angle_up_down + p_degree;
    if(angle_temp.valueDegrees() > 80){
        Ogre::Degree surplus;
        surplus = angle_temp.valueDegrees() - 80;
        m_camera->pitch(p_degree - surplus);
        m_angle_up_down = 80;
    }
    else if(angle_temp.valueDegrees() < -80){
        Ogre::Degree surplus;
        surplus = angle_temp.valueDegrees() + 80;
        m_camera->pitch(p_degree - surplus);
        m_angle_up_down = -80;
    }
    else{
        m_camera->pitch(p_degree);
        m_angle_up_down = angle_temp;
    }
}

void CameraLibre::lookRightLeft(Ogre::Degree p_degree){
    m_camera->yaw(p_degree);
}
