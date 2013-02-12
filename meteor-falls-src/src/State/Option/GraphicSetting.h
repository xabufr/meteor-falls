#ifndef GRAPHICSETTING_H_INCLUDED
#define GRAPHICSETTING_H_INCLUDED

#include "../State.h"
#include "../StateManager.h"
#include <CEGUI.h>

class GraphicSetting : public State
{
    public:
        GraphicSetting(StateManager*);
        ~GraphicSetting();
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
        CEGUI::Combobox *m_render;
};

#endif // GRAPHICSETTING_H_INCLUDED
