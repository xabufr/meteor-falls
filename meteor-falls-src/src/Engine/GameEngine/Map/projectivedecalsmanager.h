#ifndef PROJECTIVEDECALSMANAGER_H
#define PROJECTIVEDECALSMANAGER_H

#include "WorldObjectListener.h"
#include <map>

class MapView;
class WorldObjectView;
class GraphicEngine;
namespace Ogre {
    class SceneNode;
}
class ProjectiveDecalsManager : public WorldObjectListener
{
public:
    ProjectiveDecalsManager(GraphicEngine *graphic, MapView *mapView);
    void add(const WorldObjectView* object);
    void remove(const WorldObjectView* object);

private:
    class DecalDefinition;
    MapView *m_mapView;
    std::map<const WorldObjectView*, DecalDefinition*> m_decalsObjects;
    Ogre::SceneNode *m_sceneNode;
};

#endif // PROJECTIVEDECALSMANAGER_H
