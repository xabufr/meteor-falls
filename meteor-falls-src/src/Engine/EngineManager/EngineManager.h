#ifndef ENGINEMANAGER_H
#define ENGINEMANAGER_H

#include <vector>
#include "../EngineType.h"
#include <OgreFrameListener.h>

class SoundEngine;
class GraphicEngine;
class NetworkEngine;
class GameEngine;
class Engine;
class EngineManager: public Ogre::FrameListener
{
private:

	public:
    enum Type{
        SERVER,
        CLIENT,
        SERVER_LAN,
        CLIENT_LAN
    };
    enum State{
        CONNECTING,
        AUTHENTIFICATING,
        LOADING_MAP,
        PLAYING
    };
	private:
    Type m_type;

    public:
        EngineManager(Type t);
        ~EngineManager();
        Engine* get(EngineType p_engine_type);
        void work();
        void setSoundEngine(SoundEngine*);
        SoundEngine *getSound();
        GraphicEngine *getGraphic();
        NetworkEngine *getNetwork();
        GameEngine *getGame();

        virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

    protected:

    private:
        SoundEngine *m_sound;
        GraphicEngine *m_graphic;
        NetworkEngine *m_network;
        GameEngine *m_game;


};

#endif // ENGINEMANAGER_H
