#include "StateManager.h"
#include "Engine/GraphicEngine/Ogre/ogrecontextmanager.h"
#include "Engine/GraphicEngine/Ogre/OgreApplication.h"
#include "precompiled/sfml_system.h"
#include "../Engine/SoundEngine/Playlist.h"

void StateManager::addState(State *p_state)
{
    m_states.push(p_state);
}

bool StateManager::isEmpty()
{
    return m_states.empty();
}

StateManager::StateManager(): m_graphic(true), m_audio(true)
{

}

void StateManager::startLoop()
{     //lance boucle infinie
    m_end = false;
    State *last = m_states.top();
    m_states.top()->enter();
    sf::Clock timer;
    ret_code code;
    Playlist *pl;
    if(m_audio)
        pl = Playlist::get();
    while(!m_end&&!m_states.empty())
    {
        if(m_audio)
            pl->work();

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

        if(m_graphic&&!OgreContextManager::get()->getOgreApplication()->RenderOneFrame())
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
