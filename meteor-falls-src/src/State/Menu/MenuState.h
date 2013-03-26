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
#include "ServerList.h"
#include "LoginState.h"
#include "CreditState.h"
#include "OptionState.h"
#include "../../Engine/GameEngine/Joueur/Joueur.h"
#include "../../precompiled/sfml_system.h"
#include <boost/function.hpp>
#include "Engine/GameEngine/Layout/layoutRTS.h"


class MenuState: public State
{
    private:
        bool quit(const CEGUI::EventArgs &);
        bool startGame();
        bool showLanServer();
        bool showCredit();
        bool showOption();

    public:
        MenuState(StateManager*);
        ~MenuState();

        void setEscape(bool var){m_escape = var;}
        bool getEscape() const{return m_escape;}
        virtual bool isVisible();
        virtual void enter();
        virtual void exit();
        virtual ret_code work(unsigned int time);
		State* sousState() const;

    private:
        Joueur *m_player;
        CEGUI::Window *m_sheet;
        CEGUI::Window *m_state;
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
        bool m_hide_sous_state();
        bool m_escape;
        State *m_sousState;
        LoginState *m_login_state;
        LayoutRTS *m_layout_state;
        CreditState *m_credit_state;
        ServerList *m_server_list;
        OptionState *m_option_state;
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
