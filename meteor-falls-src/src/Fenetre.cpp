#include "Fenetre.h"

Fenetre::Fenetre() : m_root(0), m_window(0), m_scene_mgr(0), m_camera(0)
{
    m_menu = new MenuState();
}

Fenetre::~Fenetre()
{
    delete m_root;
    delete m_window;
    delete m_scene_mgr;
    delete m_camera;
    delete m_menu;
}

bool Fenetre::start()
{
    m_menu->show();

    while(true)
    {
        Ogre::WindowEventUtilities::messagePump();

        if(m_window->isClosed())
            return false;

        if(!m_root->renderOneFrame())
            return false;
    }

    return true;
}
