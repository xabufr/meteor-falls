#include "ObjetTerrain.h"
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>

ObjetTerrain::ObjetTerrain(Ogre::SceneManager* mng)
{
	if(mng!=nullptr)
   		m_sceneNode = mng->getRootSceneNode()->createChildSceneNode();
	else
		m_sceneNode = nullptr;
}
ObjetTerrain::~ObjetTerrain()
{
}
const Vector3D& ObjetTerrain::getPosition() const
{
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
