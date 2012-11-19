#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "../State.h"
class EngineManager;
class GameState : public State
{
    public:
        GameState(StateManager*);
        virtual ~GameState();
        virtual ret_code work();
        virtual void enter();
        virtual void exit();

    protected:
    private:
        EngineManager *m_engineManager;
};

#endif // GAMESTATE_H
