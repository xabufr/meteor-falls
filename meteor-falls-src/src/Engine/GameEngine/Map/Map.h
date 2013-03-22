#ifndef MAP_H
#define MAP_H

#include <string>
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
        Map(GameEngine*);
        virtual ~Map();
        void load(const std::string& p_name);
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
        int m_size_x;
        int m_size_y;
        bool m_cycle_enable;
        float m_cycle_coef;
        int m_cycle_hour;

		GameEngine *m_game;

        std::vector<WorldObject*> m_worldObjects;

		void processNode(rapidxml::xml_node<>* n);
		void processNodeServer(rapidxml::xml_node<>*);

		std::list<MapListener*> m_listeners;
};
#endif // MAP_H
