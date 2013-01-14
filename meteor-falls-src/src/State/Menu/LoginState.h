#ifndef LOGINSTATE_H_INCLUDED
#define LOGINSTATE_H_INCLUDED

#include "State/State.h"
#include "Engine/GraphicEngine/Ogre/ogrecontextmanager.h"
#include <CEGUI.h>
#include <OIS/OIS.h>

class LoginState : public State
{
  public:
        LoginState(StateManager *mgr);
        ~LoginState();
        virtual bool isVisible();
        virtual void enter();
        virtual void exit();
        virtual ret_code work(unsigned int time);
  private:
        CEGUI::Window *m_playLan;
        CEGUI::Window *m_playOnline;
        CEGUI::Window *m_sheet;
        CEGUI::Window *m_loginText;
        CEGUI::Window *m_passwdText;
        CEGUI::Window *m_login;
        CEGUI::Window *m_passwd;
        CEGUI::Window *m_connect;
        CEGUI::Window *m_message;
        OIS::Mouse *m_mouse;
        OIS::Keyboard *m_keyboard;
        bool m_visible;
        void m_state_element(const bool);
        bool m_connection(const CEGUI::EventArgs &);
        bool send(const CEGUI::EventArgs &);

};

#endif // LOGINSTATE_H_INCLUDED
