#include "CameraRPG.h"
#include "../Heros/Hero.h"
#include <OgreSceneNode.h>
#include <OgreCamera.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <cmath>
#include "../../GraphicEngine/Ogre/ogrecontextmanager.h"
#include "../../GraphicEngine/Ogre/OgreWindowInputManager.h"

CameraRPG::CameraRPG(Hero* h): m_hero(h), m_distance(10)
{

}
CameraRPG::~CameraRPG()
{

}
void CameraRPG::setCamera(Ogre::Camera* c)
{
	Camera::setCamera(c);
	float posz = m_hero->position().z + m_distance;
	c->setPosition(m_hero->position().x,m_hero->position().y,posz);
	c->lookAt(m_hero->position());
}
void CameraRPG::update(int)
{
    if (OgreContextManager::get()->getInputManager()->getMouse()->getMouseState().Z.rel>0)
        m_distance = (m_distance==0)?0:--m_distance;
    else if (OgreContextManager::get()->getInputManager()->getMouse()->getMouseState().Z.rel<0)
        m_distance = (m_distance==10)?10:++m_distance;

    float posx, posy, posz;
    posx = m_hero->position().x + (sin(m_hero->rotation().getYaw().valueRadians())*m_distance);
    posy = m_hero->position().y + (sin(m_hero->look().getPitch().valueRadians())*m_distance);
    posz = m_hero->position().z + (cos(m_hero->rotation().getYaw().valueRadians())*m_distance);

	m_camera->setPosition(posx,posy,posz);
	m_camera->lookAt(m_hero->position());
}
