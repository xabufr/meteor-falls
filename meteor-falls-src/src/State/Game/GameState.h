#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "../State.h"
#include <OIS/OIS.h>

class EngineManager;
class GameState : public State
{
    public:
        GameState(StateManager*);
        virtual ~GameState();
        virtual ret_code work(unsigned int);
        virtual void enter();
        virtual void exit();

    protected:
    private:
        OIS::Keyboard *m_keyboard;
        EngineManager *m_engineManager;
};

#endif // GAMESTATE_H
