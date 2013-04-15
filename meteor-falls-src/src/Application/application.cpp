#include "application.h"
#include <iostream>
#include "../Engine/GraphicEngine/Ogre/ogrecontextmanager.h"
#include "../State/Menu/MenuState.h"
#include "../State/ServerState/ServerState.h"
#include "Utils/Configuration/Config.h"
#include "../Utils/ResourceGroupManager.h"

Application* Application::m_instance = nullptr;
Application::Application(int argc, char **argv): m_params(argc, argv), m_menu(nullptr)
{
	m_instance = this;
    StateManager manager;
	m_manager = &manager;
    ResourceGroupManager::get()->loadFromFile("resources.cfg");
	ResourceGroupManager::get()->initialiseResourceGroup();
    if(!m_params.parametres.server){
        Config::get();
        manager.setAudio(true);
		m_menu = new MenuState(&manager);
        manager.addState(m_menu);
        manager.startLoop();
    }
    else{
		manager.setAudio(false);
		manager.setGraphic(false);

		manager.addState(new ServerState(&manager, &m_params.parametres));
		manager.startLoop();
    }
}
Application::~Application()
{
}
Application* Application::instance()
{
	return m_instance;
}
MenuState* Application::menuState() const
{
	return m_menu;
}
State* Application::currentState() const
{
	return m_manager->current();
}
StateManager* Application::manager() const
{
	return m_manager;
}
