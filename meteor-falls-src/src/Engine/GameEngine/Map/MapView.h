#ifndef _HOME_THOMAS_METEOR_FALLS_METEOR_FALLS_SRC_SRC_ENGINE_GAMEENGINE_MAP_MAPVIEW_H__
#define _HOME_THOMAS_METEOR_FALLS_METEOR_FALLS_SRC_SRC_ENGINE_GAMEENGINE_MAP_MAPVIEW_H__
#include <OgrePrerequisites.h>
#include "../../ScriptEngine/XmlDocumentManager.h"
#include "MapListener.h"
#include <Utils/Vector3D.h>
#include <boost/optional.hpp>

class Map;
class GraphicEngine;
namespace Forests {
    class PagedGeometry;
    class TreeLoader3D;
} // namespace Forest
namespace Ogre {
    class SceneManager;
    class TerrainGroup;
    class TerrainGlobalOptions;
    class SceneNode;
    class Light;
} // namespace Ogre
namespace SkyX {
    class SkyX;
    class BasicController;
} // namespace SkyX
namespace Hydrax {
    class Hydrax;
} // namespace Hydrax
class MapView: public MapListener
{
public:
    MapView(Map*);
    ~MapView();
    static Ogre::Real staticGetHeightAt(Ogre::Real x, Ogre::Real z, void *map);
    virtual void mapLoaded(const std::string&);
    virtual void mapUnloaded();
    virtual void update();
    virtual bool autoDelete() const;
    virtual void objetAdded(ObjetTerrain*) {
    }
    virtual void objetRemoved(ObjetTerrain*) {
    }
    float getHeightAt(float x, float z) const;
    boost::optional<Vector3D> getIntersection(Ogre::Ray &ray) const;

    Ogre::TerrainGroup *terrain() const;

private:
    Ogre::SceneManager *m_scene_mgr;
    Ogre::TerrainGlobalOptions *m_globals;
    Ogre::TerrainGroup *m_terrainGroup;
    Ogre::Light *m_sunLight;
    std::string m_temp_dir;

    SkyX::SkyX *m_skyx;
    SkyX::BasicController *m_controller;
    Hydrax::Hydrax *m_hydrax;
    Forests::PagedGeometry *m_pageGrass;
    std::list<Forests::PagedGeometry*> m_pages;

    Map *m_map;

    void processNode(XmlDocumentManager::Document const &, Ogre::SceneNode*);
    void loadPagedFile(const std::string& path, Forests::TreeLoader3D *, Ogre::Entity* ent);
};

#endif
