#ifndef COMMANDSETTING_H_INCLUDED
#define COMMANDSETTING_H_INCLUDED

#include "../State.h"
#include "../StateManager.h"
#include <CEGUI.h>
#include <OIS/OIS.h>

class CommandSetting : public State, public OIS::KeyListener, public OIS::MouseListener
{
    public:
        CommandSetting(StateManager*);
        ~CommandSetting();
        virtual bool isVisible();
        virtual void enter();
        virtual void exit();
        virtual ret_code work(unsigned int);
        virtual bool mouseMoved( const OIS::MouseEvent &arg );
		virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
		virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

		virtual bool keyPressed(const OIS::KeyEvent &arg);
		virtual bool keyReleased(const OIS::KeyEvent &arg);
    private:
        bool m_visible;
        OIS::KeyCode m_old_key;
        OIS::MouseButtonID m_old_mouse;
        bool m_button_pushed(const CEGUI::EventArgs&);
        bool m_box_pushed(const CEGUI::EventArgs&);
        OIS::Keyboard *m_keyboard ;
        OIS::Mouse *m_mouse;
        CEGUI::Editbox *m_box_selected;
        StateManager* m_state_manager;
        CEGUI::PushButton *m_accept;
        CEGUI::PushButton *m_cancel;
        CEGUI::TabControl *m_pane;
};


#endif // COMMANDSETTING_H_INCLUDED
