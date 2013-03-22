#include "CameraRPG.h"
#include "../Heros/Hero.h"
#include <OgreSceneNode.h>
#include <OgreCamera.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>

CameraRPG::CameraRPG(Hero* h): m_hero(h)
{
	//TODO revoir le système de caméra
	//m_sceneNode = m_hero->getNode()->createChildSceneNode();
	//m_sceneNode->setPosition(0.f, m_hero->entity()->getBoundingBox().getHalfSize().y, 400);
}
CameraRPG::~CameraRPG()
{
	//m_hero->getNode()->removeChild(m_sceneNode);
//	m_camera->setAutoTracking(false);
//	m_sceneNode->getCreator()->destroySceneNode(m_sceneNode);
}
void CameraRPG::setCamera(Ogre::Camera* c)
{
	Camera::setCamera(c);
	c->setPosition(0,0,0);
	//m_sceneNode->attachObject(m_camera);
	//m_camera->setAutoTracking(true, m_hero->getNode(), Ogre::Vector3(0, 0, 0)); 
}
void CameraRPG::update(int)
{

}
