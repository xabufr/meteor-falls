#include "ObjetTerrain.h"
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>

ObjetTerrain::ObjetTerrain(Ogre::SceneManager* mng)
{
    m_sceneNode = mng->getRootSceneNode()->createChildSceneNode();
}

ObjetTerrain::~ObjetTerrain()
{
    //dtor
}
const Vector3D& ObjetTerrain::getPosition() const
{
    return m_position;
}

void ObjetTerrain::setPosition(const Vector3D& p)
{
    m_position=p;
    m_sceneNode->setPosition(m_position.convert<Ogre::Vector3>());
}
Ogre::SceneNode* ObjetTerrain::getNode()
{
    return m_sceneNode;
}
