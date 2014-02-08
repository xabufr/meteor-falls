#ifndef PROJECTIVEDECALSMANAGER_H
#define PROJECTIVEDECALSMANAGER_H

#include "WorldObjectListener.h"
#include <map>
#include <string>
#include <OgreColourValue.h>

#include <Utils/vector2d.h>

class MapView;
class WorldObjectView;
class GraphicEngine;
namespace Ogre {
class SceneNode;
class Terrain;
}
class ProjectiveDecalsManager : public WorldObjectListener
{
public:
    struct DecalProperties {
        DecalProperties();
        DecalProperties(const std::string &p_texture, const Ogre::ColourValue &p_color, float p_additionnalSize = 2.5);

        std::string texture;
        Ogre::ColourValue color;
        float additionnalSize;
        Vector2D<float> size, position;
    };
    class BasicDecalDefinition {
    public:
        BasicDecalDefinition(MapView *m_mapView, Ogre::SceneNode *parentNode, const ProjectiveDecalsManager::DecalProperties &properties);
        void setProperties(const ProjectiveDecalsManager::DecalProperties &properties);
        ProjectiveDecalsManager::DecalProperties& getProperties();
        void update();
        virtual ~BasicDecalDefinition();

        void setVisible(bool visible);

    protected:
        virtual Vector2D<float> getSize() const;
        virtual Vector2D<float> getPosition() const;
        virtual Ogre::AxisAlignedBox getBoundingBox() const;

    private:
        std::vector<Ogre::Terrain *> findMapParts();
        void createPassFor(Ogre::Terrain* terrain);
        void removePassFor(Ogre::Terrain* terrain);

    private:
        MapView *m_mapView;
        Ogre::Frustum *m_frustum;
        Ogre::SceneNode *m_node;
        std::map<Ogre::Terrain*, Ogre::Pass*> m_passes;
        ProjectiveDecalsManager::DecalProperties m_properties;
    };
    ProjectiveDecalsManager(GraphicEngine *graphic, MapView *mapView);


    void add(const WorldObjectView* object, const DecalProperties &properties = DecalProperties());
    void remove(const WorldObjectView* object);

    BasicDecalDefinition* addSimple(const DecalProperties &properties = DecalProperties());
    void remove(BasicDecalDefinition* definition);

private:
    class ViewDecalDefinition;
    MapView *m_mapView;
    std::map<const void*, BasicDecalDefinition*> m_decalsObjects;
    Ogre::SceneNode *m_sceneNode;
};

#endif // PROJECTIVEDECALSMANAGER_H
