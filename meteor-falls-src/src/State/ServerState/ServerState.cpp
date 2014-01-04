#include "ServerState.h"
#include "../../Application/applicationparameters.h"
#include "../../Engine/NetworkEngine/ServerNetworkEngine.h"

ServerState::ServerState(StateManager* mng, Parameters* params): State(mng), m_param(params)
{
    if(m_param->server_wan)
        m_eManager = new EngineManager(EngineManager::SERVER);
    else
        m_eManager = new EngineManager(EngineManager::SERVER_LAN);
    ServerNetworkEngine *net = static_cast<ServerNetworkEngine*>(m_eManager->getNetwork());
    net->setMapName(params->server_map);
    net->setServerName(params->server_name);
    net->setMaxClients(params->server_max_client);
}
void ServerState::enter()
{

}
void ServerState::exit()
{

}
ret_code ServerState::work(const TimeDuration &elapsed)
{
    m_eManager->work(elapsed);
    return ret_code::CONTINUE;
}
