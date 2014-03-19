#include "TerrestreView.h"
#include "Terrestre.h"
#include "TypeUnite.h"
#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>


TerrestreView::TerrestreView(Terrestre *terrestre, Ogre::SceneNode *node): UniteView(terrestre, node)
{
    m_entity = node->getCreator()->createEntity(terrestre->type()->meshParameters().find("normal")->second);
    m_entity->getUserObjectBindings().setUserAny(Ogre::Any((WorldObject*) terrestre));
    m_node->attachObject(m_entity);
    m_node->setScale(0.01, 0.01, 0.01);
    m_node->setVisible(false);
}

void TerrestreView::update(const TimeDuration &time, WorldObject *sender)
{
    m_node->setPosition(sender->position());
}

void TerrestreView::constructionFinished(WorldObject *sender)
{
    m_node->setVisible(true);
}
