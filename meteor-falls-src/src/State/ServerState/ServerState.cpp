#include "ServerState.h"

ServerState::ServerState(StateManager* mng): State(mng)
{
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
