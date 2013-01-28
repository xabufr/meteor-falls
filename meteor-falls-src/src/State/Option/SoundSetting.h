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
        CEGUI::PushButton *m_accept;
        CEGUI::PushButton *m_cancel;
        CEGUI::Checkbox *m_activate;
};

#endif // SOUNDSETTING_H_INCLUDED
