#ifndef H_OBJET_TERRAIN_VIEW_H
#define H_OBJET_TERRAIN_VIEW_H

#include "WorldObjectListener.h"
namespace Ogre {
	class SceneManager;
	class SceneNode;
	class Entity;
} // namespace 
class WorldObject;
class WorldObjectView: public WorldObjectListener
{
public:
	WorldObjectView(WorldObject*, Ogre::SceneNode*);
	~WorldObjectView();
protected:
	Ogre::SceneNode *m_node;
	WorldObject *m_model;
};
#endif 
