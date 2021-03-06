#include "OgreWindowInputManager.h"
#include "precompiled/lexical_cast.h"
#include <CEGUI/CEGUI.h>
#include <OgreLogManager.h>
#include "ogrecontextmanager.h"
#include "OgreApplication.h"
#ifdef __linux__
#include <X11/Xutil.h>
#endif

OgreWindowInputManager::~OgreWindowInputManager()
{
}
OgreWindowInputManager::OgreWindowInputManager(Ogre::RenderWindow* window) :
        m_window(window)
{
    m_initOIS();
    m_injectMouse = true;
    m_injectKeyboard = true;
    m_injectWindowEvent = true;
#ifdef __linux__
    m_mouseLock = false;
    m_display = XOpenDisplay(0);
    m_x_delta = m_y_delta = 0;
#endif
}
void OgreWindowInputManager::m_initOIS()
{
    Ogre::LogManager::getSingleton().logMessage("***Initializing OIS***");
    OIS::ParamList pl;
    size_t windowHnd = 0;

    m_window->getCustomAttribute("WINDOW", &windowHnd);
    pl.insert(
            std::make_pair<std::string, std::string>("WINDOW",
                    boost::lexical_cast<std::string>(windowHnd)));

#ifndef __linux__
    pl.insert(
            std::make_pair(std::string("x11_mouse_grab"), std::string("true")));
#else
    pl.insert(
            std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
#endif
    pl.insert(
            std::make_pair(std::string("x11_mouse_hide"),
                    std::string("true")));
    pl.insert(
            std::make_pair(std::string("x11_keyboard_grab"),
                    std::string("false")));
    //pl.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));

    m_inputManager = OIS::InputManager::createInputSystem(pl);

    m_mouse = static_cast<OIS::Mouse*>(m_inputManager->createInputObject(
            OIS::Type::OISMouse, true));
    m_keyboard = static_cast<OIS::Keyboard*>(m_inputManager->createInputObject(
            OIS::Type::OISKeyboard, true));

    m_mouse->setEventCallback(this);
    m_keyboard->setEventCallback(this);

}
void OgreWindowInputManager::windowResized(Ogre::RenderWindow* rw)
{
    if (rw != m_window || !m_mouse)
        return;
    const OIS::MouseState &ms = m_mouse->getMouseState();
    ms.width = rw->getWidth();
    ms.height = rw->getHeight(); //bug X11 OU OIS
    static bool first = true;
    if (m_injectWindowEvent && !first)
    {
        CEGUI::Size<float> s;
        s.d_height = rw->getHeight();
        s.d_width = rw->getWidth();
        CEGUI::System::getSingleton().notifyDisplaySizeChanged(s);
    }
    first = false;
}
void OgreWindowInputManager::windowClosed(Ogre::RenderWindow* rw)
{
    if (rw != m_window || !m_inputManager)
        return;
    m_inputManager->destroyInputObject(m_mouse);
    m_inputManager->destroyInputObject(m_keyboard);

    OIS::InputManager::destroyInputSystem(m_inputManager);
    m_inputManager = 0;
    m_mouse = 0;
    m_keyboard = 0;
}
bool OgreWindowInputManager::frameStarted(const Ogre::FrameEvent& event)
{
    if (m_mouse)
        m_mouse->capture();

    if( (m_mouse->getMouseState().X.abs >= 0) && (m_mouse->getMouseState().X.abs < m_window->getWidth()) &&
            (m_mouse->getMouseState().Y.abs >= 0) && (m_mouse->getMouseState().Y.abs < m_window->getHeight())    )
    {
        int x_center = (m_window->getWidth() / 2);
        int y_center = (m_window->getHeight() / 2);
        m_x_delta = x_center - m_mouse->getMouseState().X.abs;
        m_y_delta = y_center - m_mouse->getMouseState().Y.abs;

        if( m_x_delta != 0 || m_y_delta != 0 )
        {
            XWarpPointer(static_cast<Display*>(m_display), None, None, 0, 0, 0, 0, m_x_delta, m_y_delta);
            XFlush(static_cast<Display*>(m_display));
            m_mouse->capture();
        }
        else
        {
            m_mouseLock = false;
        }
    }

    if (m_keyboard)
        m_keyboard->capture();
    for (OIS::Object* o : m_personalizedDevices)
        o->capture();
    if (m_injectWindowEvent)
        CEGUI::System::getSingleton().injectTimePulse(event.timeSinceLastFrame);
    if (m_injectKeyboard)
        update(event.timeSinceLastFrame);
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
CEGUI::MouseButton OgreWindowInputManager::convertButton(
        OIS::MouseButtonID buttonID)
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
    for (auto it = m_personalizedDevices.begin();
            it != m_personalizedDevices.end(); ++it)
    {
        if (*it == o)
        {
            m_personalizedDevices.erase(it);
            return;
        }
    }
}
void OgreWindowInputManager::injectKeyboardEventToCEGUI(bool i)
{
    m_injectKeyboard = i;
}
void OgreWindowInputManager::injectMouseEventToCEGUI(bool i)
{
    m_injectMouse = i;
}
void OgreWindowInputManager::injectWindowEventToCEGUI(bool i)
{
    m_injectWindowEvent = i;
}
void OgreWindowInputManager::addMouseListener(OIS::MouseListener* l)
{
    m_mouseListeners.push_back(l);
}
void OgreWindowInputManager::delMouseListener(OIS::MouseListener*l)
{
    for (auto it = m_mouseListeners.begin(); it != m_mouseListeners.end(); ++it)
    {
        if ((*it) == l)
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
    for (auto it = m_keyboardListeners.begin(); it != m_keyboardListeners.end();
            ++it)
    {
        if ((*it) == l)
        {
            m_keyboardListeners.erase(it);
            return;
        }
    }
}
bool OgreWindowInputManager::mouseMoved(const OIS::MouseEvent& arg)
{
    if (m_injectMouse)
    {
        CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(
                arg.state.X.rel - m_x_delta, arg.state.Y.rel - m_y_delta);
        CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseWheelChange(
                arg.state.Z.rel);
    }

    OIS::MouseState state(arg.state);
    state.X.rel -= m_x_delta;
    state.Y.rel -= m_y_delta;
    OIS::MouseEvent event(m_mouse, state);
    for (OIS::MouseListener *l : m_mouseListeners)
    {
        if (!l->mouseMoved(event))
            return false;
    }
    return true;
}
bool OgreWindowInputManager::mousePressed(const OIS::MouseEvent& arg,
        OIS::MouseButtonID id)
{
    if (m_injectMouse)
        CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(
                OgreWindowInputManager::convertButton(id));

    for (OIS::MouseListener *l : m_mouseListeners)
    {
        if (!l->mousePressed(arg, id))
            return false;
    }
    return true;
}
bool OgreWindowInputManager::mouseReleased(const OIS::MouseEvent& arg,
        OIS::MouseButtonID id)
{
    if (m_injectMouse)
        CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(
                convertButton(id));
    for (OIS::MouseListener *l : m_mouseListeners)
    {
        if (!l->mouseReleased(arg, id))
            return false;
    }
    return true;
}
bool OgreWindowInputManager::keyPressed(const OIS::KeyEvent& arg)
{
    if (m_injectKeyboard)
    {
        CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(
                (CEGUI::Key::Scan) arg.key);
        CEGUI::System::getSingleton().getDefaultGUIContext().injectChar(
                arg.text);
        begin(arg);
    }
    for (OIS::KeyListener *l : m_keyboardListeners)
    {
        if (!l->keyPressed(arg))
            return false;
    }
    return true;
}
bool OgreWindowInputManager::keyReleased(const OIS::KeyEvent& arg)
{
    if (m_injectKeyboard)
    {
        CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(
                (CEGUI::Key::Scan) arg.key);
        end(arg);
    }
    for (OIS::KeyListener *l : m_keyboardListeners)
    {
        if (!l->keyReleased(arg))
            return false;
    }
    return true;
}
void OgreWindowInputManager::repeatKey(OIS::KeyCode code, unsigned int text)
{
    if (!m_injectKeyboard)
        return;
    CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(
            (CEGUI::Key::Scan) code);
    CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(
            (CEGUI::Key::Scan) code);
    CEGUI::System::getSingleton().getDefaultGUIContext().injectChar(text);
}
