#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
#include <list>
#include "../../../Utils/Vector3D.h"
#include "../../ScriptEngine/XmlDocumentManager.h"
#include <Utils/rectangle.h>

class btCollisionShape;
class btDynamicsWorld;
class btRigidBody;
class WorldObject;
class GameEngine;
class MapListener;
class ObjetTerrain;
struct BulletRelationPtr;
class Map
{
public:
    Map(GameEngine*, btDynamicsWorld*);
    virtual ~Map();
    void load(const std::string& p_name);
    void unload();
    const std::string& getName() const;
    void addListener(MapListener*);
    void delListener(MapListener*);

    void update();
    bool getLoaded() const;
    float getHeightAt(float x, float z) const;
    Vector3D getNormalAt(float x, float z);

    GameEngine* game() const;
    XmlDocumentManager::Document& getXmlMap() const;
    std::string mapRootPath() const;

    const Rectangle<float>& bounds() const;

private:
    bool m_loaded;
    std::string m_name;
    bool m_cycle_enable;
    float m_cycle_coef;
    int m_cycle_hour;

    Rectangle<float> m_bounds;

    std::list<float*> m_terrainData;
    std::list<btRigidBody*> m_bodies;
    std::list<btCollisionShape*> m_shapes;

    GameEngine *m_game;

    std::vector<WorldObject*> m_worldObjects;

    void processNode(const XmlDocumentManager::Document &n);
    void processNodeServer(const XmlDocumentManager::Document&);

    std::list<MapListener*> m_listeners;
    btDynamicsWorld* m_world;
    std::list<BulletRelationPtr*> m_liensPhysique;
    std::vector<ObjetTerrain*> m_objectsTerrain;
};
#endif // MAP_H
