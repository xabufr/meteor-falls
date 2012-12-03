#ifndef CONSOLE_H_INCLUDED
#define CONSOLE_H_INCLUDED

#include "Utils/singleton.h"
#include "Engine/GraphicEngine/Ogre/ogrecontextmanager.h"
#include <CEGUI.h>
#include <OIS/OIS.h>

class Console : public Singleton<Console>
{
    friend class Singleton<Console>;
    public:
        void show();
        void hide();
    protected:
        Console();
        ~Console();
    private:
        CEGUI::Window *m_sheet;
        CEGUI::Window *m_console;
        OIS::Mouse *m_mouse;
        OIS::Keyboard *m_keyboard;
};

#endif // CONSOLE_H_INCLUDED
