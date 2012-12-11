#ifndef LOGINMENUSTATE_H_INCLUDED
#define LOGINMENUSTATE_H_INCLUDED

#include "State/Command/Command.h"
#include "State/State.h"
#include "State/StateManager.h"

class LoginMenuState : public Command
{
    public:
        LoginMenuState(State*, StateManager*);
        ~LoginMenuState();
        virtual void use(std::string);
    private:
        State *m_state;
        StateManager *m_state_mgr;
};

#endif // LOGINMENUSTATE_H_INCLUDED
