#ifndef OPTIONSTATE_H_INCLUDED
#define OPTIONSTATE_H_INCLUDED

#include "../State.h"
#include "../StateManager.h"
#include <vector>
#include <CEGUI.h>
#include <OIS/OIS.h>

class OptionState : public State
{
    public:
        OptionState(StateManager*);
        ~OptionState(){}
        virtual bool isVisible();
        virtual void enter();
        virtual void exit();
        virtual ret_code work(unsigned int);
    private:
        bool m_visible;
        bool m_choix_option(const CEGUI::EventArgs &);
        OIS::Keyboard *m_keyboard;
        State* m_sous_state;
        StateManager* m_state_manager;
        CEGUI::TabButton *m_window;
        CEGUI::PushButton *m_graphics;
        CEGUI::PushButton *m_sound;
        CEGUI::PushButton *m_control;
};

#endif // OPTIONSTATE_H_INCLUDED
