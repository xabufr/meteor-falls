#include "StateManager.h"
#include "Engine/GraphicEngine/Ogre/ogrecontextmanager.h"
#include "Engine/GraphicEngine/Ogre/OgreApplication.h"
#include "precompiled/sfml_system.h"

void StateManager::addState(State *p_state)
{
    m_states.push(p_state);
}

bool StateManager::isEmpty()
{
    return m_states.empty();
}


void StateManager::startLoop()
{     //lance boucle infinie
    m_end = false;
    State *last = m_states.top();
    m_states.top()->enter();
    sf::Clock timer;
    ret_code code;
    while(!m_end&&!m_states.empty())
    {
        if(last!=m_states.top())
        {
            last->exit();
            last = m_states.top();
            m_states.top()->enter();
        }
        code = m_states.top()->work(timer.getElapsedTime().asMilliseconds());
        timer.restart();
        if(code == ret_code::FINISHED){                     //ancien etat du state different du nouveau
            m_states.top()->exit();
            removeState();
            m_states.top()->enter();
        }
        else if(code == ret_code::EXIT_PROGRAM)
            exit();

        if(!OgreContextManager::get()->getOgreApplication()->RenderOneFrame())
            exit();
    }
}

void StateManager::exit()
{   //arrete la boucle infinie
    m_end = true;
    m_states.top()->exit();
}

void StateManager::removeState()
{
    m_states.pop();
}
