#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <string>
#include "Map/Map.h"
#include "../EngineMessage/EngineMessage.h"
#include "../Engine.h"
#include "../../State/State.h"
#include "Preface/TeamList.h"

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

		void loadMap(const std::string &);

    protected:

    private:
        Map *m_map;
        Type m_type;
        State *m_sous_state;
		Joueur *m_currentJoueur;
};

#endif // GAMEENGINE_H
