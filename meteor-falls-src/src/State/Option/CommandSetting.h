#ifndef COMMANDSETTING_H_INCLUDED
#define COMMANDSETTING_H_INCLUDED

#include "../State.h"
#include "../StateManager.h"
#include <CEGUI.h>

class CommandSetting : public State
{
    public:
        CommandSetting(StateManager*);
        ~CommandSetting();
        virtual bool isVisible();
        virtual void enter();
        virtual void exit();
        virtual ret_code work(unsigned int);
    private:
        bool m_visible;
        bool m_button_pushed(const CEGUI::EventArgs&);
        StateManager* m_state_manager;
        CEGUI::PushButton *m_accept;
        CEGUI::PushButton *m_cancel;
        CEGUI::ScrollablePane *m_pane;
};


#endif // COMMANDSETTING_H_INCLUDED
