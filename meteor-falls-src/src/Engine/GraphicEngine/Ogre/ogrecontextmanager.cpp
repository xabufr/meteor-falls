#include "ogrecontextmanager.h"
#include "Engine/GraphicEngine/Ogre/OgreApplication.h"
#include "Engine/GraphicEngine/Ogre/OgreWindowInputManager.h"

OgreContextManager::OgreContextManager()
{
    m_application = new OgreApplication();
    m_inputManager = new OgreWindowInputManager(m_application->getWindow());
    m_inputManager->windowResized(m_application->getWindow());
    Ogre::WindowEventUtilities::addWindowEventListener(m_application->getWindow(), m_inputManager);
}

OgreContextManager::~OgreContextManager()
{
    Ogre::WindowEventUtilities::removeWindowEventListener(m_application->getWindow(), m_inputManager);
    m_inputManager->windowClosed(m_application->getWindow());
    delete m_inputManager;
    delete m_application;
}
OgreApplication* OgreContextManager::getOgreApplication()
{
    return m_application;
}
OgreWindowInputManager* OgreContextManager::getInputManager()
{
    return m_inputManager;
}
