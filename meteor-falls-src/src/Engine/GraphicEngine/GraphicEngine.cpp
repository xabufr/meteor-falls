#include "GraphicEngine.h"
#include "Engine/GraphicEngine/Ogre/OgreApplication.h"
#include "Engine/GraphicEngine/Ogre/ogrecontextmanager.h"

GraphicEngine::GraphicEngine(EngineManager* m):
    Engine(m)
{
    m_sceneManager = OgreContextManager::get()->getOgreApplication()->getRoot()->createSceneManager(Ogre::ST_EXTERIOR_REAL_FAR);
}
GraphicEngine::~GraphicEngine()
{
    //dtor
}
Ogre::SceneManager* GraphicEngine::getSceneManager()
{
    return m_sceneManager;
}
void GraphicEngine::handleMessage(EngineMessage&)
{

}
void GraphicEngine::work()
{

}
EngineType GraphicEngine::getType()
{
    return EngineType::GraphicEngineType;
}
