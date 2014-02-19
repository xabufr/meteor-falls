#ifndef OPTIONSTATE_H_INCLUDED
#define OPTIONSTATE_H_INCLUDED

#include "../State.h"
#include "../StateManager.h"
#include <vector>
#include <CEGUI/CEGUI.h>
#include <OIS/OIS.h>

class SoundSetting;
class GraphicSetting;
class CommandSetting;
class MenuState;
class OptionState : public State
{
    public:
        OptionState(StateManager*, MenuState*);
        ~OptionState();
        virtual bool isVisible();
        virtual void enter();
        virtual void exit();
        virtual ret_code work(const TimeDuration &elapsed);
    private:
        bool m_visible;
        bool m_choix_option(const CEGUI::EventArgs &);
        MenuState* m_menu;
        OIS::Keyboard *m_keyboard;
        State* m_sous_state;
        StateManager* m_state_manager;
        SoundSetting *m_sound_setting;
        GraphicSetting *m_graphic_setting;
        CommandSetting *m_command_setting;
        CEGUI::Window *m_window;
        CEGUI::PushButton *m_graphics;
        CEGUI::PushButton *m_sound;
        CEGUI::PushButton *m_control;
};

#endif // OPTIONSTATE_H_INCLUDED
