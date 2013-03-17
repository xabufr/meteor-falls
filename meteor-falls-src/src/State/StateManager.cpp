#include "StateManager.h"
#include "../Engine/GraphicEngine/Ogre/ogrecontextmanager.h"
#include "../Engine/GraphicEngine/Ogre/OgreApplication.h"
#include "../precompiled/sfml_system.h"
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

    size_t time;
    while(!m_end&&!m_states.empty())
    {
        time = timer.getElapsedTime().asMilliseconds();
        timer.restart();
        if(m_audio)
            Playlist::get()->work();

        if(last!=m_states.top())
        {
            last->exit();
            last = m_states.top();
            m_states.top()->enter();
        }
        code = m_states.top()->work(time);
        if(code == ret_code::FINISHED){                     //ancien etat du state different du nouveau
            m_states.top()->exit();
			delete m_states.top();
            removeState();
            m_states.top()->enter();
			last = m_states.top();
        }
        else if(code == ret_code::EXIT_PROGRAM)
            exit();

        if(m_graphic&&!OgreContextManager::get()->getOgreApplication()->RenderOneFrame())
            exit();
		else if(!m_graphic&&time < 1000.f/100.f)
		{
			boost::this_thread::sleep(boost::posix_time::milliseconds((1000.f/100.f) - time));
		}
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
State* StateManager::current() const
{
	return m_states.top();
}
