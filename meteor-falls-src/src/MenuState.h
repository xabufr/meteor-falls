#ifndef MENUSTATE_H_INCLUDED
#define MENUSTATE_H_INCLUDED

#include <Ogre.h>
#include <CEGUI.h>
#include <RendererModules/Ogre/CEGUIOgreRenderer.h>
#include "Engine/GraphicEngine/Ogre/OgreWindowInputManager.h"

class MenuState
{
    private:
        Ogre::SceneManager *m_scene_mgr;
        bool quit(const CEGUI::EventArgs &);
    public:
        MenuState();
        ~MenuState();
        void show();
    protected:
        CEGUI::OgreRenderer *m_renderer;
};

#endif // MENUSTATE_H_INCLUDED
