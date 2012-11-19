#include "StateManager.h"

void StateManager::addState(State *p_state){
    m_states.push(p_state);
}

void StateManager::startLoop(){     //lance boucle infinie
    m_end = false;
    m_states.front()->enter();
    ret_code code = ret_code::HIDE;
    while(m_end != true && !m_states.empty()){
        if(code == ret_code::FINISHED){                       //ancien etat du state different du nouveau
            m_states.front()->exit();
            removeState();
            m_states.front()->enter();
        }
        else if(code == ret_code::EXIT_PROGRAM)
            exit();
        else
            code = m_states.front()->work();
    }
}

void StateManager::exit(){          //arrete la boucle infinie
    m_end = true;
    m_states.front()->exit();
}

void StateManager::removeState(){
    m_states.pop();
}
