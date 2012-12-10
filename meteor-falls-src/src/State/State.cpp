#include "State.h"

State::State(StateManager *p_state_manager){
    m_state_manager = p_state_manager;
}

void State::addState(State *p_state){
    m_states.push_back(p_state);
}

void State::removeState(State *p_state){
    for(unsigned int i=0;i<=m_states.size();i++){
        if(m_states[i] == p_state){
            m_states.erase(m_states.begin()+i-1);
            return;
        }
    }
}
