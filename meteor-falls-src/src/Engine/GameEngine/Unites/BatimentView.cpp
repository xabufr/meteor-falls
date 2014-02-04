#include "BatimentView.h"
#include "Batiment.h"
#include "TypeUnite.h"
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>

BatimentView::BatimentView(Batiment* bat, Ogre::SceneNode* node): UniteView(bat, node)
{
    m_entity = node->getCreator()->createEntity(bat->type()->meshParameters().find("normal")->second);
    m_entity->getUserObjectBindings().setUserAny(Ogre::Any((WorldObject*) bat));
    m_node->attachObject(m_entity);
    m_node->showBoundingBox(true);
}
void BatimentView::positionChanged(const Vector3D& vec, WorldObject *sender)
{
    m_node->setPosition(vec);
}
