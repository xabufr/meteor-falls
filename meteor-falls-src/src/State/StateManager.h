#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <queue>
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
        std::queue<State*> m_states;
        bool m_end;
};

#endif // STATEMANAGER_H
