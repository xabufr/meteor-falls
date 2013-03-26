#include "Console.h"
#include "../Engine/ScriptEngine/XmlDocumentManager.h"
#include "../Engine/GraphicEngine/Ogre/OgreWindowInputManager.h"
#include "../Engine/GraphicEngine/Ogre/ogrecontextmanager.h"
#include "../Engine/GraphicEngine/Ogre/OgreApplication.h"
#include "Game/GameState.h"
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <sstream>

Console::~Console()
{
    delete m_sheet;
    delete m_console;
}
Console::Console() : m_id(0), m_admin(false)
{
    CEGUI::WindowManager &m_window_mgr = CEGUI::WindowManager::getSingleton();

	m_sheet   = m_window_mgr.loadWindowLayout("console.layout");

	m_console = (CEGUI::MultiLineEditbox*)m_sheet->getChild("fenConsole/logger");
	m_lineCommand = (CEGUI::Editbox*) m_sheet->getChild("fenConsole/commandLine");

	m_console->getVertScrollbar()->setEndLockEnabled(true);

    CEGUI::System::getSingleton().getGUISheet()->addChildWindow(m_sheet);
    m_sheet->setVisible(false);
}
void Console::start()
{
	CEGUI::String line = m_lineCommand->getText();
    for (unsigned int i=0; i<m_commands.size(); ++i)
    {
        boost::regex expName("^"+m_commands[i]->getName()+"+[ .a-z0-9]*");
        if (boost::regex_match(line.c_str(), expName))
        {
            if (!m_commands[i]->getProperties().empty())
            {
                std::vector<std::string> properties = m_commands[i]->getProperties();
                for (unsigned int j=0; j<properties.size(); ++j)
                {
                    boost::regex expProp("^"+m_commands[i]->getName()+" "+properties[j]+"$");
                    if (boost::regex_match(line.c_str(), expProp))
                        m_commands[i]->setUsedPropertie(properties[j]);
                }
            }
            m_commands[i]->use(line.c_str());
            m_old_command.push_back(line);
            m_id = m_old_command.size()-1;
        }
    }
	m_console->appendText(line+"\n");
}
void Console::m_auto_completion()
{
	CEGUI::String line = m_lineCommand->getText();
    std::list<Command*> found_command;
    for (size_t i=0; i < m_commands.size(); ++i)
    {
        boost::regex exp(("^"+line+"[a-zA-Z]*").c_str());
        if (boost::regex_match(m_commands[i]->getName(), exp))
            found_command.push_back(m_commands[i]);
    }
    if (found_command.size() > 1)
    {
        for (Command* c : found_command)
            m_console->appendText(c->getName());
    }
    else if (found_command.size() == 1)
        m_lineCommand->setText(found_command.front()->getName()+" ");
	m_lineCommand->setCaratIndex(m_lineCommand->getText().size());
}
void Console::m_show_old_command(const OIS::KeyEvent &arg)
{
	/*
    char pattern;
    pattern = (m_admin)?'#':'$';

    if (arg.key == OIS::KeyCode::KC_UP
        && m_lines.substr(m_lines.find_last_of(pattern), m_old_command.at(m_id).size()) == m_old_command.at(m_id)
        && m_id > 0)
        --m_id;
    if (arg.key == OIS::KeyCode::KC_DOWN
        && m_lines.substr(m_lines.find_last_of(pattern), m_old_command.at(m_id).size()) == m_old_command.at(m_id)
        && m_id < m_old_command.size()-1)
        ++m_id;

    m_console->setText(m_lines.substr(0, m_lines.find_last_of(pattern))+m_old_command.at(m_id));

    if (arg.key == OIS::KeyCode::KC_UP && m_id > 0)
        --m_id;
    if (arg.key == OIS::KeyCode::KC_DOWN && m_id < m_old_command.size()-1)
        ++m_id;

    m_console->setProperty("CaratIndex", boost::lexical_cast<std::string>(m_console->getText().size()));
	*/
}
bool Console::isVisible()
{
    return m_sheet->isVisible();
}
void Console::setAdmin(const bool admin)
{
    m_admin = admin;
}
void Console::hide()
{
    m_sheet->setVisible(false);
}
void Console::show()
{
    m_sheet->setVisible(true);
    m_lineCommand->activate();
	m_lineCommand->setText("");
}
void Console::addCommand(Command *c)
{
    m_commands.push_back(c);
}
void Console::clearCommands()
{
	//for(Command *c : m_commands)
	//	delete c;
	m_commands.clear();
}
bool Console::keyPressed(const OIS::KeyEvent& arg)
{
    if (arg.text == 178)
    {
        if (!isVisible())
            show();
        else
            hide();
    }
    if (isVisible())
    {
        if (arg.key == OIS::KeyCode::KC_BACK)
        {
            //if ((m_lines.substr(m_lines.size()-2, 1) == "$") || (m_lines.substr(m_lines.size()-2, 1) == "#"))
            //{
            //    m_console->setText(m_lines);
            //    m_console->setProperty("CaratIndex", boost::lexical_cast<std::string>(m_console->getText().size()));
           // }
        }
        else if (arg.key == OIS::KeyCode::KC_TAB)
            m_auto_completion();
        else if (arg.key == OIS::KeyCode::KC_RETURN)
            start();
        //else if (arg.key == OIS::KeyCode::KC_LEFT || arg.key == OIS::KeyCode::KC_RIGHT)
        //    if (m_console->getProperty("CaratIndex") <= boost::lexical_cast<std::string>(m_lines.find_last_of(m_pattern)))
        //        m_console->setProperty("CaratIndex", boost::lexical_cast<std::string>(m_lines.find_last_of(m_pattern)+1));
        else if (arg.key == OIS::KeyCode::KC_UP || arg.key == OIS::KeyCode::KC_DOWN)
            if (!m_old_command.empty())
                m_show_old_command(arg);

        //m_lines = std::string(m_console->getText().c_str());
		m_console->getVertScrollbar()->setScrollPosition(m_console->getVertScrollbar()->getDocumentSize());
        return false;
    }
    return true;
}
bool Console::keyReleased(const OIS::KeyEvent& arg)
{
   // if (arg.key == OIS::KeyCode::KC_UP || arg.key == OIS::KeyCode::KC_DOWN)
     //   m_console->setProperty("CaratIndex", boost::lexical_cast<std::string>(m_console->getText().size()));
    return true;
}
bool Console::mouseMoved(const OIS::MouseEvent& arg)
{
    return true;
}
bool Console::mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id )
{
   // if (boost::lexical_cast<int>(m_console->getProperty("CaratIndex")) <= m_console->getText().find_last_of(m_pattern))
   //             m_console->setProperty("CaratIndex", boost::lexical_cast<std::string>(m_console->getText().size()));
    return true;
}
bool Console::mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id )
{
    //if (boost::lexical_cast<int>(m_console->getProperty("CaratIndex")) <= m_console->getText().find_last_of(m_pattern))
    //            m_console->setProperty("CaratIndex", boost::lexical_cast<std::string>(m_console->getText().size()));
    return true;
}
CEGUI::Window *Console::getConsole()
{
    return m_console;
}
