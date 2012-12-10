#include "application.h"
#include <iostream>
#include "Engine/GraphicEngine/Ogre/ogrecontextmanager.h"
#include "State/Menu/MenuState.h"
#include "State/ServerState/ServerState.h"

Application::Application(int argc, char **argv): m_params(argc, argv)
{
    ApplicationParametersKeys &parameters = m_params.getKeys();
    if(parameters.find("help")->second=="y")
    {
        showHelp();
        return;
    }
    if(parameters["gui"]=="y"){
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

void Application::showHelp()
{
    std::cout << "Aide:" << std::endl;
    std::cout << "--option argument" << std::endl;
    std::cout << "--gui [y|n]" << std::endl;
    std::cout << "--netconsole [y|n]" << std::endl;
}
