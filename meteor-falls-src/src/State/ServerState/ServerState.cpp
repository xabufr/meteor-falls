#include "ServerState.h"
#include "../../Application/applicationparameters.h"

ServerState::ServerState(StateManager* mng, Parameters* params): State(mng), m_param(params)
{
	if(m_param->server_wan)
		m_eManager = new EngineManager(EngineManager::SERVER);
	else
		m_eManager = new EngineManager(EngineManager::SERVER_LAN);
}
void ServerState::enter()
{
	
}
void ServerState::exit()
{

}
ret_code ServerState::work(unsigned int time)
{
	m_eManager->work();
	return ret_code::CONTINUE;
}
