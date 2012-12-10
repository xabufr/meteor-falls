#ifndef CONSOLE_H_INCLUDED
#define CONSOLE_H_INCLUDED

#include <string>
#include <vector>
#include <iostream>
#include "Utils/singleton.h"
#include "Engine/GraphicEngine/Ogre/ogrecontextmanager.h"
#include <CEGUI.h>
#include <OIS/OIS.h>
#include "Command/Command.h"

class Console : public Singleton<Console>
{
    friend class Singleton<Console>;
    public:
        void show();
        void hide();
        bool isVisible();
        void clearCommands();
        void addCommand(Command*);
        void start();
    protected:
        Console();
        ~Console();
    private:
        bool m_visible;
        std::string m_lines;
        std::vector<Command*> m_commands;
        OIS::Keyboard *m_keyboard;
        CEGUI::Window *m_sheet;
        CEGUI::Window *m_console;
};

#endif // CONSOLE_H_INCLUDED
