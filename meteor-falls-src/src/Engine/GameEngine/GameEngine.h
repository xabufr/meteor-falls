#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <string>
#include "Map/Map.h"
#include "../EngineMessage/EngineMessage.h"
#include "../Engine.h"

class Joueur;
class GameEngine : public Engine
{
    public:
        enum Type{
            CLIENT,
            SERVER
        };
        GameEngine(EngineManager*, Type);
        virtual ~GameEngine();
        virtual void handleMessage(const EngineMessage&);
        virtual void work();
        virtual EngineType getType();

    protected:

    private:
        Map *m_map;
        Type m_type;
		Joueur *m_currentJoueur;
};

#endif // GAMEENGINE_H
