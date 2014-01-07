#ifndef GRAPHICSETTING_H_INCLUDED
#define GRAPHICSETTING_H_INCLUDED

#include "../State.h"
#include "../StateManager.h"
#include <CEGUI/CEGUI.h>

class GraphicSetting : public State
{
    public:
        GraphicSetting(StateManager*);
        ~GraphicSetting();
        virtual bool isVisible();
        virtual void enter();
        virtual void exit();
        virtual ret_code work(const TimeDuration &elapsed);
    private:
        bool m_visible;
        bool m_button_pushed(const CEGUI::EventArgs&);
        int m_value_water[3];
        StateManager* m_state_manager;
        CEGUI::Combobox *m_water;
        CEGUI::PushButton *m_accept;
        CEGUI::PushButton *m_cancel;
        CEGUI::Combobox *m_render;
};

#endif // GRAPHICSETTING_H_INCLUDED
