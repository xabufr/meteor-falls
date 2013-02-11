#ifndef MAP_H
#define MAP_H

#include <OgreSceneManager.h>
#include <OgreCamera.h>
#include <Hydrax/Hydrax.h>
#include <string>
#include <iostream>
#include "../Camera/CameraLibre.h"
#include <SkyX/SkyX.h>
#include <vector>
#include "../../../Utils/Vector3D.h"
#include "../Unites/Hero.h"
#include <Terrain/OgreTerrainGroup.h>
#include "../../ScriptEngine/XmlDocumentManager.h"

using namespace rapidxml;

class WorldObject;
class GameEngine;
class Map
{
    public:
        Map(Ogre::SceneManager*, GameEngine*);
        virtual ~Map();
        void load(std::string p_name);
        std::string getName();
        void update();
        bool getLoaded();
        float getHeightAt(float x, float z);
        Vector3D getNormalAt(float x, float z);

    private:
        Ogre::SceneManager *m_scene_mgr;
        Ogre::TerrainGlobalOptions *m_globals;
		Ogre::TerrainGroup *m_terrainGroup;
        bool m_loaded;
        std::string m_name;
        int m_size_x;
        int m_size_y;
        bool m_cycle_enable;
        float m_cycle_coef;
        int m_cycle_hour;
        Ogre::Camera* m_camera;
        CameraLibre* m_camera_test;
        SkyX::SkyX *m_skyx;
        SkyX::BasicController *m_controller;
        Hydrax::Hydrax *m_hydrax;

		GameEngine *m_game;

        std::vector<WorldObject*> m_worldObjects;

        static Ogre::ColourValue getRGBA(rapidxml::xml_node<>*);
		static Vector3D getPosition(rapidxml::xml_node<>*, const std::string& = "");
		static Ogre::Quaternion getRotation(rapidxml::xml_node<>*);
		void processNode(rapidxml::xml_node<>* n, Ogre::SceneNode*);
		void processNodeServer(rapidxml::xml_node<>*);
};

#endif // MAP_H
