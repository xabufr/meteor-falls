#include "application.h"
#include <iostream>
#include "Engine/GraphicEngine/Ogre/ogrecontextmanager.h"
#include "MenuState.h"

Application::Application(int argc, char **argv): m_params(argc, argv)
{
    ApplicationParametersKeys &parameters = m_params.getKeys();
    if(parameters.find("help")->second=="y")
    {
        showHelp();
        return;
    }
    if(parameters["gui"]=="y"){
        OgreContextManager::get();
        MenuState menu;
        menu.show();
    }
    else{

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
