#ifndef HERO_H
#define HERO_H
#include <string>
#include "Engine/GraphicEngine/Ogre/ogrecontextmanager.h"
#include "Engine/GraphicEngine/Ogre/OgreApplication.h"
#include "Engine/GraphicEngine/Ogre/OgreWindowInputManager.h"
#include "Engine/GraphicEngine/Ogre/GetMeshInformation.h"
#include <boost/bind.hpp>
#include "Terrestre.h"

class Hero : public Terrestre
{
    public:

        Hero(std::string name, std::string chemin);
        virtual ~Hero();


    private:

        void m_insert_hero_in_scene();
        std::string m_name;
        std::string m_chemin;
        Ogre::Entity *m_eNinja;

};

#endif // HERO_H
