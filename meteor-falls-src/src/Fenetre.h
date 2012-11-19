#ifndef FENETRE_H_INCLUDED
#define FENETRE_H_INCLUDED

#include <Ogre.h>
#include "MenuState.h"

class Fenetre
{
    private :
        Ogre::Root *m_root;
        Ogre::RenderWindow *m_window;
        Ogre::SceneManager *m_scene_mgr;
        Ogre::Camera *m_camera;
        MenuState *m_menu;
    public :
        Fenetre();
        ~Fenetre();
        bool start();
};

#endif // FENETRE_H_INCLUDED
