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

class Console : public Singleton<Console>, public OIS::KeyListener
{
    friend class Singleton<Console>;
    public:
        void show();
        void hide();
        std::string getPettern();
        bool isVisible();
        void setAdmin(const bool);
        void clearCommands();
        void addCommand(Command*);
        void start();
        void autoCompletion();
        CEGUI::Window *getConsole();
        virtual bool keyPressed(const OIS::KeyEvent &arg);
		virtual bool keyReleased(const OIS::KeyEvent &arg);
    protected:
        Console();
        ~Console();
    private:
        std::string m_pattern;
        bool m_visible;
        bool m_admin;
        std::string m_lines;
        std::vector<Command*> m_commands;
        OIS::Keyboard *m_keyboard;
        CEGUI::Window *m_sheet;
        CEGUI::Window *m_console;
};

#endif // CONSOLE_H_INCLUDED
