#ifndef MAP_H
#define MAP_H

#include <string>
#include <btBulletDynamicsCommon.h>
#include <Bullet-C-Api.h>
#include <btBulletCollisionCommon.h>
#include <bullet/BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h>
#include <vector>
#include <list>
#include "../../../Utils/Vector3D.h"
#include "../../ScriptEngine/XmlDocumentManager.h"

class WorldObject;
class GameEngine;
class MapListener;
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
	rapidxml::xml_document<>* getXmlMap() const;
	std::string mapRootPath() const;

private:
	bool m_loaded;
	std::string m_name;
	bool m_cycle_enable;
	float m_cycle_coef;
	int m_cycle_hour;
	std::list<float*> m_terrainData;

	GameEngine *m_game;

	std::vector<WorldObject*> m_worldObjects;

	void processNode(rapidxml::xml_node<>* n);
	void processNodeServer(rapidxml::xml_node<>*);

	std::list<MapListener*> m_listeners;
	btDynamicsWorld* m_world;
};
#endif // MAP_H
