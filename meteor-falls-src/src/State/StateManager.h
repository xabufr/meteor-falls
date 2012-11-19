#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <stack>
#include "State.h"

class State;

class StateManager
{
    public:
        void addState(State *p_state);
        void startLoop();
        void exit();
        void removeState();

    protected:

    private:
        std::stack<State*> m_states;
        bool m_end;
};

#endif // STATEMANAGER_H
