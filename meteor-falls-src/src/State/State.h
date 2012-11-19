#ifndef STATE_H
#define STATE_H

#include "StateManager.h"

class StateManager;

enum ret_code{
    FINISHED = 0,
    HIDE = 1,
    EXIT_PROGRAM = 2,
    CONTINUE
};

class State
{
    public:
        State(StateManager *p_state_manager);
        virtual void enter() = 0;
        virtual void exit() = 0;
        virtual ret_code work() = 0;

    protected:

    private:
        void addState(State *p_state);
        void removeState(State *p_state);
        StateManager *m_state_manager;
        std::vector<State*> m_states;
};

#endif // STATE_H
