#include "OgreWindowInputManager.h"
#include <boost/lexical_cast.hpp>
#include <CEGUI.h>

OgreWindowInputManager::~OgreWindowInputManager()
{
    m_injectMouse=true;
    m_injectKeyboard=true;
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

    m_mouse->setEventCallback(this);
    m_keyboard->setEventCallback(this);
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

CEGUI::MouseButton OgreWindowInputManager::convertButton(OIS::MouseButtonID buttonID)
{
    switch (buttonID)
    {
    case OIS::MB_Left:
        return CEGUI::LeftButton;
    case OIS::MB_Right:
        return CEGUI::RightButton;
    case OIS::MB_Middle:
        return CEGUI::MiddleButton;
    case OIS::MB_Button3:
        return CEGUI::X1Button;
    case OIS::MB_Button4:
        return CEGUI::X2Button;
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
    for(auto it = m_personalizedDevices.begin(); it!=m_personalizedDevices.end(); ++it)
    {
        if(*it == o)
        {
            m_personalizedDevices.erase(it);
            return;
        }
    }
}
void OgreWindowInputManager::injectKeyboardEventToCEGUI(bool i)
{
    m_injectKeyboard=i;
}

void OgreWindowInputManager::injectMouseEventToCEGUI(bool i)
{
    m_injectMouse=i;
}
void OgreWindowInputManager::addMouseListener(OIS::MouseListener* l)
{
    m_mouseListeners.push_back(l);
}

void OgreWindowInputManager::delMouseListener(OIS::MouseListener*l)
{
    for(auto it=m_mouseListeners.begin(); it!=m_mouseListeners.end(); ++it)
    {
        if((*it)==l)
        {
            m_mouseListeners.erase(it);
            return;
        }
    }
}

void OgreWindowInputManager::addKeyboardListener(OIS::KeyListener *l)
{
    m_keyboardListeners.push_back(l);
}

void OgreWindowInputManager::delKeyboardListener(OIS::KeyListener *l)
{
    for(auto it=m_keyboardListeners.begin(); it!=m_keyboardListeners.end(); ++it)
    {
        if((*it)==l)
        {
            m_keyboardListeners.erase(it);
            return;
        }
    }
}

bool OgreWindowInputManager::mouseMoved(const OIS::MouseEvent& arg)
{
    if(m_injectMouse)
    {
        CEGUI::System::getSingleton().injectMouseMove(arg.state.X.rel, arg.state.Y.rel);
    }
    for(OIS::MouseListener *l : m_mouseListeners)
    {
        if(!l->mouseMoved(arg))
            return false;
    }
    return true;
}

bool OgreWindowInputManager::mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
{
    if(m_injectMouse)
        CEGUI::System::getSingleton().injectMouseButtonDown(OgreWindowInputManager::convertButton(id));

    for(OIS::MouseListener *l : m_mouseListeners)
    {
        if(!l->mousePressed(arg, id))
            return false;
    }
    return true;
}

bool OgreWindowInputManager::mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
{
    if(m_injectMouse)
        CEGUI::System::getSingleton().injectMouseButtonUp(convertButton(id));
    for(OIS::MouseListener *l : m_mouseListeners)
    {
        if(!l->mouseReleased(arg, id))
            return false;
    }
    return true;
}

bool OgreWindowInputManager::keyPressed(const OIS::KeyEvent& arg)
{
    if(m_injectKeyboard)
    {
        CEGUI::System::getSingleton().injectKeyDown(arg.key);
        CEGUI::System::getSingleton().injectChar(arg.text);
    }
    for(OIS::KeyListener *l : m_keyboardListeners)
    {
        if(!l->keyPressed(arg))
            return false;
    }
    return true;
}

bool OgreWindowInputManager::keyReleased(const OIS::KeyEvent& arg)
{
    if(m_injectKeyboard)
    {
        CEGUI::System::getSingleton().injectKeyUp(arg.key);
    }
    for(OIS::KeyListener *l : m_keyboardListeners)
    {
        if(!l->keyReleased(arg))
            return false;
    }
    return true;
}
