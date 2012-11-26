#include "../../meteor-falls-src/src/Engine/GraphicEngine/GraphicEngine.h"
#include "../../meteor-falls-src/src/Engine/GraphicEngine/Ogre/OgreApplication.h"
#include "../../meteor-falls-src/src/Engine/GraphicEngine/Ogre/ogrecontextmanager.h"

GraphicEngine::GraphicEngine(EngineManager* m):
    Engine(m)
{
    m_sceneManager = OgreContextManager::get()->getOgreApplication()->getRoot()->createSceneManager("DefaultSceneManager");
}

GraphicEngine::~GraphicEngine()
{
    //dtor
}
Ogre::SceneManager* GraphicEngine::getSceneManager()
{
    return m_sceneManager;
}
void GraphicEngine::handleMessage(const EngineMessage&)
{

}

void GraphicEngine::work()
{

}

EngineType GraphicEngine::getType()
{
    return EngineType::GraphicEngineType;
}
