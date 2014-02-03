#ifndef H_OBJET_TERRAIN_VIEW_H
#define H_OBJET_TERRAIN_VIEW_H

#include "WorldObjectListener.h"
namespace Ogre {
    class SceneManager;
    class SceneNode;
    class Entity;
} // namespace
class WorldObject;
class WorldObjectView: virtual public WorldObjectListener
{
public:
    WorldObjectView(WorldObject*, Ogre::SceneNode*);
    ~WorldObjectView();
    WorldObject* model() const;
    void setSelected(bool selected);
    bool selected() const;
    virtual void update(float time);
protected:
    Ogre::SceneNode *m_node;
    WorldObject *m_model;
    bool m_isSelected;
};
#endif
