#ifndef PROJECTIVEDECALSMANAGER_H
#define PROJECTIVEDECALSMANAGER_H

#include "WorldObjectListener.h"
#include <map>
#include <string>
#include <OgreColourValue.h>

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

    struct DecalProperties {
        DecalProperties();
        DecalProperties(const std::string &p_texture, const Ogre::ColourValue &p_color, float p_additionnalSize = 2.5);

        std::string texture;
        Ogre::ColourValue color;
        float additionnalSize;
    };

    void add(const WorldObjectView* object, const DecalProperties &properties = DecalProperties());
    void remove(const WorldObjectView* object);

private:
    class DecalDefinition;
    MapView *m_mapView;
    std::map<const WorldObjectView*, DecalDefinition*> m_decalsObjects;
    Ogre::SceneNode *m_sceneNode;
};

#endif // PROJECTIVEDECALSMANAGER_H
