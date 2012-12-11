#ifndef MENUSTATE_H_INCLUDED
#define MENUSTATE_H_INCLUDED

#include <OgreRectangle2D.h>
#include <OgreSceneNode.h>
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreSceneQuery.h>
#include <OIS/OIS.h>
#include "../../Engine/GraphicEngine/Ogre/OgreWindowInputManager.h"
#include "../State.h"
#include "../../precompiled/sfml_system.h"
#include <boost/function.hpp>


class MenuState: public State
{
    private:
        bool quit(const CEGUI::EventArgs &);
        bool startGame();

    public:
        MenuState(StateManager*);
        ~MenuState();

        virtual bool isVisible();
        virtual void enter();
        virtual void exit();
        virtual ret_code work(unsigned int time);

    private:
        CEGUI::Window *m_sheet;
        OIS::Mouse *m_mouse;
        OIS::Keyboard *m_keyboard;
        Ogre::SceneManager *m_scene_mgr;
        Ogre::Camera *m_camera;
        Ogre::Rectangle2D *m_background;
        Ogre::SceneNode *m_nodeTerre;
        Ogre::SceneNode *m_nodeLune;
        Ogre::SceneNode *m_nodeSoleil;
        sf::Clock m_timerClick;
        Ogre::SceneNode* terreAtmosphere;
        Ogre::Entity* m_currentSelected;
        Ogre::RaySceneQuery* m_sceneQuery;
        bool m_visible;
        State *m_sousState;

        /**
            Les entités qui vont correspondre à des entrées menu
        */
        Ogre::Entity *m_eTerre, *m_eAtmoTerre, *m_eSoleil, *m_eLune;

        /**
            Gestion des transitions
        */
        bool m_transitionning;
        enum{
            TERRE,
            MENU
        } m_transitionTo;
        sf::Clock m_timerTranslation;
        struct{
            Ogre::Vector3 from, to;
            float duration;
            boost::function<void()> function;
        } m_transitionParams;
};

#endif // MENUSTATE_H_INCLUDED
