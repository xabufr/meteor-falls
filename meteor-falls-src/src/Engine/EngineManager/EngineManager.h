#ifndef ENGINEMANAGER_H
#define ENGINEMANAGER_H

#include <list>
#include "../EngineType.h"
#include "../GameEngine/Joueur/Joueur.h"
#include <OgreFrameListener.h>

class SoundEngine;
class GraphicEngine;
class NetworkEngine;
class GameEngine;
class Engine;
class EngineMessage;
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
        EngineManager(Type t, const std::string& address = "", const std::string& password = "", Joueur *j=0);
        ~EngineManager();
        Engine* get(EngineType p_engine_type);
        void work();
        void setSoundEngine(SoundEngine*);
        SoundEngine *getSound();
        GraphicEngine *getGraphic();
        NetworkEngine *getNetwork();
        GameEngine *getGame();

		void addMessage(EngineMessage*);

        virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

    protected:

    private:
        SoundEngine *m_sound;
        GraphicEngine *m_graphic;
        NetworkEngine *m_network;
        GameEngine *m_game;
		std::list<EngineMessage*> m_messages;
};

#endif // ENGINEMANAGER_H
