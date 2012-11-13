#ifndef OGREWINDOWINPUTMANAGER_H
#define OGREWINDOWINPUTMANAGER_H

#include <OIS/OIS.h>
#include <Ogre.h>

class OgreWindowInputManager : public Ogre::WindowEventListener, public Ogre::FrameListener
{
    public:
        OgreWindowInputManager(Ogre::RenderWindow *window);
        virtual ~OgreWindowInputManager();

        virtual void windowResized(Ogre::RenderWindow *rw);
        virtual void windowClosed(Ogre::RenderWindow *rw);

        virtual bool frameStarted(const Ogre::FrameEvent& event);

        OIS::Mouse* getMouse();
        OIS::Keyboard* getKeyboard();

        void addPersonalizedDevice(OIS::Object*);
        void removePersonalizedDevice(OIS::Object*);
    protected:
    private:
        void m_initOIS();
        Ogre::RenderWindow *m_window;
        OIS::InputManager *m_inputManager;
        OIS::Mouse *m_mouse;
        OIS::Keyboard *m_keyboard;

        std::vector<OIS::Object*> m_personalizedDevices;
};

#endif // OGREWINDOWINPUTMANAGER_H
