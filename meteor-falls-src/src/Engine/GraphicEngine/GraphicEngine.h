#ifndef GRAPHICENGINE_H
#define GRAPHICENGINE_H

#include "../Engine.h"
#include <Ogre.h>

class GraphicEngine: public Engine
{
    public:
        GraphicEngine(EngineManager*);
        virtual ~GraphicEngine();
        Ogre::SceneManager* getSceneManager();

        virtual void handleMessage(const EngineMessage&);
        virtual void work();
        virtual EngineType getType();
    protected:
    private:
        Ogre::SceneManager* m_sceneManager;
};

#endif // GRAPHICENGINE_H
