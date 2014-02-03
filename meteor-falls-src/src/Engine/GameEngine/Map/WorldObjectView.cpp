#include "WorldObjectView.h"
#include "WorldObject.h"
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>

WorldObjectView::WorldObjectView(WorldObject* model, Ogre::SceneNode* node): m_node(node), m_model(model)
{
    m_model->addListener(this);
    m_isSelected = false;
    m_node->showBoundingBox(true);
}
WorldObjectView::~WorldObjectView()
{
    m_node->getCreator()->destroySceneNode(m_node);
}

WorldObject *WorldObjectView::model() const
{
    return m_model;
}

void WorldObjectView::setSelected(bool selected)
{
    m_isSelected = selected;
}

bool WorldObjectView::selected() const
{
    return m_isSelected;
}

void WorldObjectView::update(float time)
{
    m_node->showBoundingBox(m_isSelected);
}
