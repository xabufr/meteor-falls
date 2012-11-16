#include "SateManager.h"

void addState(State *p_state){
    m_states->push_back(*p_state);
}

void startLoop(){

}

void exit(){

}

void removeState(State *p_state){
    int i;
    for(i=0;i<=m_states.size();i++){
        if(m_states[i] == *p_state){
            m_states->erase(i);
        }
    }
}
