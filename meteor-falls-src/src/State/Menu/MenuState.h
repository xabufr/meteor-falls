#ifndef MENUSTATE_H_INCLUDED
#define MENUSTATE_H_INCLUDED

#include <Ogre.h>
#include <OIS/OIS.h>
#include <CEGUI.h>
#include <RendererModules/Ogre/CEGUIOgreRenderer.h>
#include "Engine/GraphicEngine/Ogre/OgreWindowInputManager.h"
#include "../State.h"

class MenuState: public State
{
    private:
        bool quit(const CEGUI::EventArgs &);

    public:
        MenuState(StateManager*);
        ~MenuState();

        virtual void enter();
        virtual void exit();
        virtual ret_code work();

    private:
        CEGUI::OgreRenderer *m_renderer;
        OIS::Mouse *m_mouse;
        OIS::Keyboard *m_keyboard;
        Ogre::SceneManager *m_scene_mgr;
        Ogre::Camera *m_camera;
        Ogre::Rectangle2D *m_background;
};

#endif // MENUSTATE_H_INCLUDED
