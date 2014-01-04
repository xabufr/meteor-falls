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
        virtual ret_code work(const TimeDuration &elapsed);
    private:
        CEGUI::Window *m_credit;
        int m_nbr_loop;
        bool m_visible;
};
#endif // CREDITSTATE_H_INCLUDED
