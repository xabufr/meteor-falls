#ifndef CREDITSTATE_H_INCLUDED
#define CREDITSTATE_H_INCLUDED

#include "../State.h"
#include "../StateManager.h"
#include <CEGUI.h>

class CreditState : public State
{
    public:
        CreditState(StateManager *mgr);
        ~CreditState();
        virtual bool isVisible();
        virtual void enter();
        virtual void exit();
        virtual ret_code work(unsigned int time);
    private:
        CEGUI::TextComponent *m_credit;
        bool m_visible;
};
#endif // CREDITSTATE_H_INCLUDED
