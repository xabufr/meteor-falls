#include "application.h"
#include <iostream>

Application::Application(int argc, char **argv): m_params(argc, argv)
{
    const ApplicationParametersKeys &parameters = m_params.getKeys();
    if(parameters.find("help")->second=="y")
    {
        showHelp();
        return;
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
