#include "application.h"
#include <iostream>
#include "../Engine/GraphicEngine/Ogre/ogrecontextmanager.h"
#include "../State/Menu/MenuState.h"
#include "../State/ServerState/ServerState.h"

Application::Application(int argc, char **argv): m_params(argc, argv)
{
    if(!m_params.parametres.server){
        StateManager manager;
        manager.addState(new MenuState(&manager));
        manager.startLoop();
    }
    else{
		StateManager manager;
		manager.setAudio(false);
		manager.setGraphic(false);

		manager.addState(new ServerState(&manager));
		manager.startLoop();
    }
}

Application::~Application()
{
}

