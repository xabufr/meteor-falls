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

class Console : public Singleton<Console>, public OIS::KeyListener, public OIS::MouseListener
{
    friend class Singleton<Console>;
    public:
        void show();
        void hide();
        bool isVisible();
        void setAdmin(const bool);
        void clearCommands();
        void addCommand(Command*);
        void start();
        CEGUI::Window *getConsole();
        virtual bool keyPressed(const OIS::KeyEvent &arg);
		virtual bool keyReleased(const OIS::KeyEvent &arg);
		virtual bool mouseMoved(const OIS::MouseEvent &arg);
		virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id );
		virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    protected:
        Console();
        ~Console();
    private:
        void m_auto_completion();
        void m_show_old_command(const OIS::KeyEvent &arg);
        std::string m_pattern;
        bool m_visible;
        bool m_admin;
        std::string m_lines;
        std::vector<std::string> m_old_command;
        size_t m_id;
        std::vector<Command*> m_commands;
        CEGUI::Window *m_sheet;
        CEGUI::Window *m_console;
};

#endif // CONSOLE_H_INCLUDED
