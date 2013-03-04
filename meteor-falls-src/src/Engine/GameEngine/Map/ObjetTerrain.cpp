#include "ObjetTerrain.h"
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>

ObjetTerrain::ObjetTerrain(GameEngine* g, Ogre::SceneManager* mng): 
m_game(g),
m_sceneManager(mng)
{
	if(mng!=nullptr)
   		m_sceneNode = mng->getRootSceneNode()->createChildSceneNode();
	else
		m_sceneNode = nullptr;
}
ObjetTerrain::~ObjetTerrain()
{
	if(m_sceneNode)
	{
		m_sceneNode->removeAndDestroyAllChildren();
		m_sceneManager->destroySceneNode(m_sceneNode);
	}
}
const Vector3D& ObjetTerrain::getPosition() const
{
	if(m_sceneNode)
		return m_sceneNode->getPosition();
    return m_position;
}
void ObjetTerrain::setPosition(const Vector3D& p)
{
    m_position=p;
	if(m_sceneNode != nullptr)
	    m_sceneNode->setPosition(m_position.convert<Ogre::Vector3>());
}
Ogre::SceneNode* ObjetTerrain::getNode()
{
    return m_sceneNode;
}
