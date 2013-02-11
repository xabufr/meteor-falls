#include "ogrecontextmanager.h"
#include "Engine/GraphicEngine/Ogre/OgreApplication.h"
#include "Engine/GraphicEngine/Ogre/OgreWindowInputManager.h"

bool OgreContextManager::createGraphics = true;
OgreContextManager::OgreContextManager()
{
    m_application = new OgreApplication(createGraphics);
	if(createGraphics)
	{
    	m_inputManager = new OgreWindowInputManager(m_application->getWindow());
    	m_inputManager->windowResized(m_application->getWindow());
    	Ogre::WindowEventUtilities::addWindowEventListener(m_application->getWindow(), m_inputManager);
    	m_application->getRoot()->addFrameListener(m_inputManager);
	}
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
OgreContextManager* OgreContextManager::get()
{
    return Singleton<OgreContextManager>::get();
}

void OgreContextManager::reinitialise()
{
    Ogre::WindowEventUtilities::removeWindowEventListener(m_application->getWindow(), m_inputManager);
    m_inputManager->windowClosed(m_application->getWindow());
    delete m_inputManager;

    m_application->recreateWindow();

	if(createGraphics)
	{
    	m_inputManager = new OgreWindowInputManager(m_application->getWindow());
    	m_inputManager->windowResized(m_application->getWindow());
    	Ogre::WindowEventUtilities::addWindowEventListener(m_application->getWindow(), m_inputManager);
    	m_application->getRoot()->addFrameListener(m_inputManager);
	}
}
