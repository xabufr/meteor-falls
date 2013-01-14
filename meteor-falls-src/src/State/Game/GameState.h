#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "../State.h"
#include "../../Engine/EngineManager/EngineManager.h"
#include "../../Engine/GameEngine/Joueur/Joueur.h"
#include <OIS/OIS.h>
class EngineManager;
class GameState : public State
{
    public:
        GameState(StateManager*, const EngineManager::Type, const std::string& address = "", const std::string& password = "", Joueur *j=0);
        virtual ~GameState();
        virtual bool isVisible();
        virtual ret_code work(unsigned int);
        virtual void enter();
        virtual void exit();

    protected:
    private:
        OIS::Keyboard *m_keyboard;
        EngineManager *m_engineManager;
        Joueur *m_player;
        std::string m_address;
        std::string m_password;
        EngineManager::Type m_type;
        bool m_visible;
};

#endif // GAMESTATE_H
