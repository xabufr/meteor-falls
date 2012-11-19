#include "EngineManager.h"
#include "Engine/NetworkEngine/NetworkEngine.h"
#include "Engine/SoundEngine/SoundEngine.h"
#include "Engine/NetworkEngine/ClientNetworkEngineLan.h"
#include "Engine/NetworkEngine/clientnetworkengine.h"
#include "Engine/NetworkEngine/ServerNetworkEngine.h"

Engine* EngineManager::get(EngineType p_engine_type){
    unsigned int i;
    for(i=0;i<=m_engines.size();i++){
        if(p_engine_type == m_engines[i]->getType()){
            return m_engines[i];
        }
    }
    return 0;
}
void EngineManager::work()
{

}
EngineManager::EngineManager(Type t):
    m_type(t),
    m_sound(0)
{
    //m_graphic = new GraphicEngine(this);
    switch(t)
    {
    case Type::CLIENT:
        m_network = new ClientNetworkEngine(this);
        break;
    case Type::CLIENT_LAN:
        m_network = new ClientNetworkEngineLan(this);
        break;
    case Type::SERVER:
    case Type::SERVER_LAN:
        m_network = new ServerNetworkEngine(this, 8888);
        break;
    }

    //m_engines.push_back(m_graphic);
    m_engines.push_back(m_network);
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

void EngineManager::setSoundEngine(SoundEngine* e)
{
    if(m_sound==0){
        m_engines.push_back((Engine*)(e));
        m_sound=e;
    }
}
