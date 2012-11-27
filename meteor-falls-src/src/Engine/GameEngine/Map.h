#ifndef MAP_H
#define MAP_H

#include <Ogre.h>
#include <string>
#include <iostream>
#include "Engine/GameEngine/Unites/Hero.h"

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
        Ogre::Entity *m_eNinja;
        bool m_loaded;
        std::string m_name;
        int m_size_x;
        int m_size_y;
        int m_size_z;
        bool m_cycle_enable;
        int m_cycle_duration;
        int m_cycle_hour;


};

#endif // MAP_H
