#ifndef SOUNDSETTING_H_INCLUDED
#define SOUNDSETTING_H_INCLUDED

#include "../State.h"
#include "../StateManager.h"
#include <CEGUI.h>

class SoundSetting : public State
{
    public:
        SoundSetting(StateManager*);
        ~SoundSetting();
        virtual bool isVisible();
        virtual void enter();
        virtual void exit();
        virtual ret_code work(unsigned int);
    private:
        bool m_visible;
        bool m_button_pushed(const CEGUI::EventArgs&);
        bool m_checkbox_used(const CEGUI::EventArgs&);
        bool m_modif_slide(const CEGUI::EventArgs&);
        StateManager* m_state_manager;
        CEGUI::PushButton *m_accept;
        CEGUI::PushButton *m_cancel;
        CEGUI::ToggleButton *m_activate;
        CEGUI::Slider *m_music_volume;
        CEGUI::Slider *m_ambiant_volume;
        CEGUI::Slider *m_effect_volume;
        CEGUI::Slider *m_interface_volume;
        CEGUI::Window *m_text_music;
        CEGUI::Window *m_text_ambiant;
        CEGUI::Window *m_text_effect;
        CEGUI::Window *m_text_interface;
};

#endif // SOUNDSETTING_H_INCLUDED
