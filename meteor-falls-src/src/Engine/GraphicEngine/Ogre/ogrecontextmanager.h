#ifndef OGRECONTEXTMANAGER_H
#define OGRECONTEXTMANAGER_H

#include "Utils/singleton.h"

class OgreApplication;
class OgreWindowInputManager;
class OgreContextManager : public Singleton<OgreContextManager>
{
    public:
        OgreContextManager();
        virtual ~OgreContextManager();
        OgreApplication* getOgreApplication();
        OgreWindowInputManager* getInputManager();
    protected:
    private:
        OgreApplication* m_application;
        OgreWindowInputManager* m_inputManager;
};

#endif // OGRECONTEXTMANAGER_H
