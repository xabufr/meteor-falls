#ifndef APPLICATION_H
#define APPLICATION_H

#include "Application/applicationparameters.h"

class Application
{
    public:
        Application(int argc, char **argv);
        ~Application();
        void showHelp();
    protected:
    private:
        ApplicationParameters m_params;
};

#endif // APPLICATION_H
