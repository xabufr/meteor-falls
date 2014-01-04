#ifndef GRAPHICENGINE_H
#define GRAPHICENGINE_H

#include "../Engine.h"
#include <OgreSceneManager.h>

class GraphicEngine: public Engine
{
    public:
        GraphicEngine(EngineManager*);
        virtual ~GraphicEngine();
        Ogre::SceneManager* getSceneManager();

        virtual void handleMessage(EngineMessage&);
        virtual void work(const TimeDuration &elapsed);
        virtual EngineType getType();
    protected:
    private:
        Ogre::SceneManager* m_sceneManager;
};

#endif // GRAPHICENGINE_H
