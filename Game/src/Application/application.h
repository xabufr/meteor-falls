#ifndef APPLICATION_H
#define APPLICATION_H

#include "applicationparameters.h"

class StateManager;
class State;
class MenuState;
class Application
{
    public:
        Application(int argc, char **argv);
        ~Application();
		static Application* instance();
		State *currentState() const;
		MenuState *menuState() const;
		StateManager *manager() const;
    private:
        ApplicationParameters m_params;
		static Application* m_instance; // Pour les scripts
		MenuState *m_menu;
		StateManager *m_manager;
};

#endif // APPLICATION_H
