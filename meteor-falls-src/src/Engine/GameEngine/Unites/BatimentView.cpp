#include "BatimentView.h"
#include "Batiment.h"
#include "TypeUnite.h"
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>

BatimentView::BatimentView(Batiment* bat, Ogre::SceneNode* node): UniteView(bat, node)
{
	m_entity = node->getCreator()->createEntity(bat->type()->meshParameters().find("normal")->second);
	m_node->attachObject(m_entity);
}
void BatimentView::positionChanged(const Vector3D& vec)
{
	m_node->setPosition(vec);
}
