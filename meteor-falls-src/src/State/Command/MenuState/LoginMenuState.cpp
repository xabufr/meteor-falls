#include "LoginMenuState.h"
#include "State/Menu/LoginState.h"
#include <iostream>

 LoginMenuState::~LoginMenuState()
{

}

 LoginMenuState::LoginMenuState(State *s, StateManager *mgr):Command("login"), m_state(s)
{
    m_properties.push_back("show");
    m_properties.push_back("hide");
    m_state_mgr = mgr;
}

void LoginMenuState::use()
{
    if (m_used_propertie == "hide")
            m_state->exit();
    else
            m_state->enter();
}

