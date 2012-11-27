#ifndef OGREWINDOWINPUTMANAGER_H
#define OGREWINDOWINPUTMANAGER_H

#include <OIS/OIS.h>
#include <CEGUI.h>
#include <Ogre.h>

class OgreWindowInputManager :
    public Ogre::WindowEventListener,
    public Ogre::FrameListener,
    public OIS::MouseListener,
    public OIS::KeyListener
{
    public:
        OgreWindowInputManager(Ogre::RenderWindow *window);
        virtual ~OgreWindowInputManager();

        virtual void windowResized(Ogre::RenderWindow *rw);
        virtual void windowClosed(Ogre::RenderWindow *rw);

        virtual bool frameStarted(const Ogre::FrameEvent& event);

        OIS::Mouse* getMouse();
        OIS::Keyboard* getKeyboard();
        static CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);

        void addPersonalizedDevice(OIS::Object*);
        void removePersonalizedDevice(OIS::Object*);

        void injectKeyboardEventToCEGUI(bool);
        void injectMouseEventToCEGUI(bool);

        void addMouseListener(OIS::MouseListener*);
        void delMouseListener(OIS::MouseListener*);

        void addKeyboardListener(OIS::KeyListener*);
        void delKeyboardListener(OIS::KeyListener*);

        virtual bool mouseMoved( const OIS::MouseEvent &arg );
		virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
		virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

		virtual bool keyPressed(const OIS::KeyEvent &arg);
		virtual bool keyReleased(const OIS::KeyEvent &arg);

    private:
        void m_initOIS();
        Ogre::RenderWindow *m_window;
        OIS::InputManager *m_inputManager;
        OIS::Mouse *m_mouse;
        OIS::Keyboard *m_keyboard;
        bool m_injectMouse, m_injectKeyboard;

        std::vector<OIS::Object*> m_personalizedDevices;
        std::vector<OIS::MouseListener*> m_mouseListeners;
        std::vector<OIS::KeyListener*> m_keyboardListeners;
};

#endif // OGREWINDOWINPUTMANAGER_H
