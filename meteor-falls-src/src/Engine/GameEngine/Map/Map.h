#ifndef MAP_H
#define MAP_H

#include <OgreSceneManager.h>
#include <OgreCamera.h>
#include <Hydrax.h>
#include <string>
#include <iostream>
#include "../Camera/CameraLibre.h"
#include "../../../../SkyX/Include/SkyX.h"
#include <Terrain/OgreTerrain.h>

class Map
{
    public:
        Map(Ogre::SceneManager*);
        virtual ~Map();
        void load(std::string p_name);
        std::string getName();
        void update();
        bool getLoaded();

    protected:

    private:
        Ogre::SceneManager *m_scene_mgr;
        Ogre::TerrainGlobalOptions *m_globals;
        Ogre::Light *light;
        Ogre::Timer m_timer;
        bool m_loaded;
        std::string m_name;
        int m_size_x;
        int m_size_y;
        bool m_cycle_enable;
        float m_cycle_coef;
        int m_cycle_hour;
        Ogre::Entity *m_Eninja;
        Ogre::SceneNode *m_node;
        Ogre::AnimationState *mAnimationState;
        Ogre::Camera* m_camera;
        CameraLibre* m_camera_test;
        SkyX::SkyX *m_skyx;
        SkyX::BasicController *m_controller;
        Hydrax::Hydrax *m_hydrax;
        int m_posx_hero;
        int m_posy_hero;
        int m_posz_hero;

};

#endif // MAP_H
