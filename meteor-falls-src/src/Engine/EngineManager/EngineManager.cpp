#include "EngineManager.h"
#include "../NetworkEngine/NetworkEngine.h"
#include "../SoundEngine/SoundEngine.h"
#include "../NetworkEngine/ClientNetworkEngineLan.h"
#include "../NetworkEngine/clientnetworkengine.h"
#include "../NetworkEngine/ServerNetworkEngineLan.h"
#include "../NetworkEngine/ServerNetworkEngineWan.h"
#include "../GraphicEngine/GraphicEngine.h"
#include "../GameEngine/GameEngine.h"
#include "../GraphicEngine/Ogre/ogrecontextmanager.h"
#include "../GraphicEngine/Ogre/OgreApplication.h"
#include "../EngineMessage/EngineMessage.h"

Engine* EngineManager::get(EngineType p_engine_type){
    switch(p_engine_type)
    {
    case EngineType::GameEngineType:
        return m_game;
    case EngineType::GraphicEngineType:
        return m_graphic;
    case EngineType::NetworkEngineType:
        return m_network;
    case EngineType::PhysicalEngineType:
    case EngineType::ScriptEngineType:
    case EngineType::SoundEngineType:
        return m_sound;
    }
    return 0;
}
void EngineManager::work()
{
    if(m_type==SERVER || m_type==SERVER_LAN) //Sinon les autres moteurs doivent travailler pendant le rendu
    {
		m_network->work();
		m_game->work();
    }
	for(EngineMessage *message : m_messages)
	{
		for(Engine *e : message->getTo())
		{
			e->handleMessage(*message);
		}
		delete message;
	}
	m_messages.clear();
}
EngineManager::EngineManager(Type t, const std::string& address, const std::string& password, Joueur *j):
    m_type(t),
    m_sound(0)
{
	if(t==Type::SERVER||t==Type::SERVER_LAN)
		OgreContextManager::createGraphics = false;
    m_graphic = new GraphicEngine(this);
    if(t==Type::CLIENT||t==Type::CLIENT_LAN)
    {
        OgreContextManager::get()->getOgreApplication()->getRoot()->addFrameListener(this);
    }

    switch(t)
    {
    case Type::CLIENT:
        m_network = new ClientNetworkEngine(this, address, 8888, j, password);
        break;
    case Type::CLIENT_LAN:
        m_network = new ClientNetworkEngineLan(this, address, 8888, j, password);
        break;
    case Type::SERVER:
	  //  m_network = new ServerNetworkEngineWan(this, 8888);
		break;
    case Type::SERVER_LAN:
        m_network = new ServerNetworkEngineLan(this, 8888);
        break;
    }
    m_game = (t==CLIENT||t==CLIENT_LAN)?new GameEngine(this, GameEngine::Type::CLIENT, j)
                                      : new GameEngine(this, GameEngine::Type::SERVER);
}
EngineManager::~EngineManager()
{
    delete m_game;
    if(m_type==Type::CLIENT||m_type==Type::CLIENT_LAN)
    {
        delete m_graphic;
        OgreContextManager::get()->getOgreApplication()->getRoot()->removeFrameListener(this);
    }
    delete m_network;
}
SoundEngine* EngineManager::getSound()
{
    return m_sound;
}
GraphicEngine* EngineManager::getGraphic()
{
    return m_graphic;
}
NetworkEngine* EngineManager::getNetwork()
{
    return m_network;
}
GameEngine* EngineManager::getGame()
{
    return m_game;
}
void EngineManager::setSoundEngine(SoundEngine* e)
{
    if(m_sound==0)
    {
        m_sound=e;
    }
}
bool EngineManager::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    m_network->work();
    m_game->work();
    if(m_sound)
        m_sound->work();
    return true;
}
void EngineManager::addMessage(EngineMessage* message)
{
	m_messages.push_back(message);
}

