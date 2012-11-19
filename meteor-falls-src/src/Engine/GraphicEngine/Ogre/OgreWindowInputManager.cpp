#include "OgreWindowInputManager.h"
#include <boost/lexical_cast.hpp>

OgreWindowInputManager::~OgreWindowInputManager()
{
}
OgreWindowInputManager::OgreWindowInputManager(Ogre::RenderWindow* window) : m_window(window)
{
    m_initOIS();
}

void OgreWindowInputManager::m_initOIS()
{
    Ogre::LogManager::getSingleton().logMessage("***Initializing OIS***");
    OIS::ParamList pl;
    size_t windowHnd = 0;

    m_window->getCustomAttribute("WINDOW", &windowHnd);
    pl.insert(std::make_pair<std::string, std::string>("WINDOW", boost::lexical_cast<std::string>(windowHnd)));
    m_inputManager = OIS::InputManager::createInputSystem(pl);

    m_mouse =   static_cast<OIS::Mouse*>   (m_inputManager->createInputObject(OIS::Type::OISMouse,    true));
    m_keyboard= static_cast<OIS::Keyboard*>(m_inputManager->createInputObject(OIS::Type::OISKeyboard, true));
}
void OgreWindowInputManager::windowResized(Ogre::RenderWindow* rw)
{
    if(rw!=m_window||!m_mouse) return;
    const OIS::MouseState &ms = m_mouse->getMouseState();
    ms.width = rw->getWidth();
    ms.height = rw->getHeight();
}

void OgreWindowInputManager::windowClosed(Ogre::RenderWindow* rw)
{
    if(rw!=m_window||!m_inputManager) return;
    m_inputManager->destroyInputObject(m_mouse);
    m_inputManager->destroyInputObject(m_keyboard);

    OIS::InputManager::destroyInputSystem(m_inputManager);
    m_inputManager = 0;
    m_mouse = 0;
    m_keyboard = 0;
}
bool OgreWindowInputManager::frameStarted(const Ogre::FrameEvent& event)
{
    if(m_mouse)
        m_mouse->capture();
    if(m_keyboard)
        m_keyboard->capture();
    for(OIS::Object* o : m_personalizedDevices)
        o->capture();
    return true;
}
OIS::Mouse* OgreWindowInputManager::getMouse()
{
    return m_mouse;
}

OIS::Keyboard* OgreWindowInputManager::getKeyboard()
{
    return m_keyboard;
}

CEGUI::MouseButton OgreWindowInputManager::convertButton(OIS::MouseButtonID buttonID){
    switch (buttonID){
    case OIS::MB_Left:
        return CEGUI::LeftButton;

    case OIS::MB_Right:
        return CEGUI::RightButton;

    case OIS::MB_Middle:
        return CEGUI::MiddleButton;

    default:
        return CEGUI::LeftButton;
    }
}

void OgreWindowInputManager::addPersonalizedDevice(OIS::Object* o)
{
    m_personalizedDevices.push_back(o);
}

void OgreWindowInputManager::removePersonalizedDevice(OIS::Object* o)
{
    for(auto it = m_personalizedDevices.begin();it!=m_personalizedDevices.end();++it){
        if(*it == o){
            m_personalizedDevices.erase(it);
            return;
        }
    }
}
