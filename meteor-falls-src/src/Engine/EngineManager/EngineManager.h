#ifndef ENGINEMANAGER_H
#define ENGINEMANAGER_H

#include <vector>
#include "../EngineType.h"

class SoundEngine;
class GraphicEngine;
class NetworkEngine;
class Engine;
class EngineManager
{
private:

public:
    enum Type{
        SERVER,
        CLIENT,
        SERVER_LAN,
        CLIENT_LAN
    };
private:
    Type m_type;

    public:
        EngineManager(Type t);
        Engine* get(EngineType p_engine_type);
        void work();
        void setSoundEngine(SoundEngine*);
        SoundEngine *getSound();
        GraphicEngine *getGraphic();
        NetworkEngine *getNetwork();

    protected:

    private:
        std::vector<Engine*> m_engines;
        SoundEngine *m_sound;
        GraphicEngine *m_graphic;
        NetworkEngine *m_network;


};

#endif // ENGINEMANAGER_H
