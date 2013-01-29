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
        bool isEmpty();
        void setAudio(bool a){ m_audio=a; }
        void setGraphic(bool g){ m_graphic=g; }

        StateManager();

    protected:

    private:
        std::stack<State*> m_states;
        bool m_end, m_graphic, m_audio;
};

#endif // STATEMANAGER_H
