#include "WorldObject.h"
#include "WorldObjectType.h"
#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "OgreEntity.h"

WorldObject::WorldObject(GameEngine* g, Ogre::SceneManager* mng, WorldObjectType* type):
    ObjetTerrain(g, mng),
    m_type(type)
{
    m_entity = mng->createEntity(m_type->mesh_name);
    m_entity->setCastShadows(true);
    m_sceneNode->attachObject(m_entity);
    m_sceneNode->setOrientation(m_type->quaternion);
}

WorldObject::~WorldObject()
{
    //dtor
}
void WorldObject::setPosition(const Vector3D& vec)
{
    m_position=vec;
    Vector3D p = m_type->offset + m_position;
    m_sceneNode->setPosition(p.convert<Ogre::Vector3>());
}
WorldObjectType* WorldObject::getType() const
{
    return m_type;
}
