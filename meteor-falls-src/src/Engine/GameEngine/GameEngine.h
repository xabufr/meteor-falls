#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <string>
#include "Map.h"
#include "../EngineMessage/EngineMessage.h"

class GameEngine : public Engine
{
    public:
        /*GameEngine();
        virtual ~GameEngine();*/
        void handleMessage(const EngineMessage&);
        void work();

    protected:

    private:
        Map *m_map;
};

#endif // GAMEENGINE_H
