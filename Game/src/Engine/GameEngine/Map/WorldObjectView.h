#ifndef H_OBJET_TERRAIN_VIEW_H
#define H_OBJET_TERRAIN_VIEW_H

#include "WorldObjectListener.h"
namespace Ogre {
    class SceneManager;
    class SceneNode;
    class Entity;
    class AxisAlignedBox;
} // namespace
class WorldObject;
class WorldObjectView: virtual public WorldObjectListener
{
public:
    WorldObjectView(WorldObject*, Ogre::SceneNode*);
    ~WorldObjectView();
    WorldObject* model() const;
    const Ogre::AxisAlignedBox& getBoundingBox() const;
    virtual void update(float time, WorldObject *sender);
protected:
    Ogre::SceneNode *m_node;
    WorldObject *m_model;
};
#endif
