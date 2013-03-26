#include "WorldObjectView.h"
#include "WorldObject.h"

WorldObjectView::WorldObjectView(WorldObject* model, Ogre::SceneNode* node): m_node(node), m_model(model)
{
	m_model->addListener(this);
}
WorldObjectView::~WorldObjectView()
{
}
