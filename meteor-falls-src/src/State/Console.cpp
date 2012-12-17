#include "State/Console.h"
#include "Engine/ScriptEngine/XmlDocumentManager.h"
#include "Engine/GraphicEngine/Ogre/OgreWindowInputManager.h"
#include "Engine/GraphicEngine/Ogre/ogrecontextmanager.h"
#include "Engine/GraphicEngine/Ogre/OgreApplication.h"
#include "State/Game/GameState.h"
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <sstream>

Console::~Console()
{
    delete m_sheet;
    delete m_console;
}

Console::Console() : m_visible(false), m_lines(""), m_id(0), m_admin(false)
{
    CEGUI::WindowManager &m_window_mgr = CEGUI::WindowManager::getSingleton();

    m_sheet = m_window_mgr.createWindow("DefaultWindow", "FenetreConsole");


    m_console = m_window_mgr.createWindow("OgreTray/MultiLineEditbox", "Console");
    m_console->setSize(CEGUI::UVector2(CEGUI::UDim(1, 0), CEGUI::UDim(0.2, 0)));
    m_console->setAlwaysOnTop(true);
    m_sheet->addChildWindow(m_console);

    CEGUI::System::getSingleton().getGUISheet()->addChildWindow(m_sheet);
    m_pattern = "$";
    m_sheet->hide();
}

void Console::start()
{
    if (m_lines == std::string(m_console->getText().c_str()))
        return;
    int debut = m_lines.find_last_of(m_pattern);
    m_lines = std::string(m_console->getText().c_str());
    int fin=m_lines.length()-2;

    debut = (debut < 0)?0:debut;
    std::string line = m_lines.substr(debut, (fin-debut));
    for (unsigned int i=0; i<m_commands.size(); ++i)
    {
        boost::regex expName("^[$#]"+m_commands[i]->getName()+"+[ .a-z0-9]*");
        if (boost::regex_match(line, expName))
        {
            if (!m_commands[i]->getProperties().empty())
            {
                std::vector<std::string> properties = m_commands[i]->getProperties();
                for (unsigned int j=0; j<properties.size(); ++j)
                {
                    boost::regex expProp("^[$#]"+m_commands[i]->getName()+" "+properties[j]+"$");
                    if (boost::regex_match(line, expProp))
                        m_commands[i]->setUsedPropertie(properties[j]);
                }
            }
            m_commands[i]->use(line);
            m_old_command.push_back(line);
            m_id = m_old_command.size()-1;
        }
    }
    m_console->setText(m_console->getText().substr(0, m_console->getText().size()-1)+m_pattern);

    std::ostringstream oss;
    oss << m_console->getText().size();

    m_console->setProperty("CaratIndex", oss.str());
}

void Console::m_auto_completion()
{
    int debut = m_lines.find_last_of(m_pattern);
    m_lines = std::string(m_console->getText().c_str());
    int fin=m_lines.length()-1;

    debut = (debut < 0)?0:debut;
    std::string line = m_lines.substr(debut, (fin-debut));
    line = (line == m_pattern)?"":line.substr(1);
    std::list<Command*> found_command;
    for (size_t i=0; i < m_commands.size(); ++i)
    {
        boost::regex exp("^"+line+"[a-zA-Z]*");
        if (boost::regex_match(m_commands[i]->getName(), exp))
            found_command.push_back(m_commands[i]);
    }
    if (found_command.size() > 1)
    {
        for (Command* c : found_command)
            m_console->setText(m_console->getText()+c->getName());
        m_console->setText(m_console->getText()+m_pattern);
    }
    else if (found_command.size() == 1)
        m_console->setText(m_console->getText().substr(0, m_console->getText().find_last_of(m_pattern)+1)+found_command.front()->getName()+" ");

    m_lines = std::string(m_console->getText().c_str());

    std::ostringstream oss;
    oss << m_console->getText().size();

    m_console->setProperty("CaratIndex", oss.str());
}

void Console::m_show_old_command(const OIS::KeyEvent &arg)
{
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
}

bool Console::isVisible()
{
    return m_visible;
}

void Console::setAdmin(const bool admin)
{
    m_admin = admin;
    m_pattern = (m_admin)?"#":"$";
}


void Console::hide()
{
    m_sheet->hide();
    m_visible = false;
    m_console->setText("");
}

void Console::show()
{
    m_console->setText(m_pattern);
    m_lines = m_pattern;
    m_sheet->show();
    m_console->setProperty("CaratIndex", "1");
    m_console->activate();
    m_visible = true;
}

void Console::addCommand(Command *c)
{
    m_commands.push_back(c);
}

void Console::clearCommands()
{
    while (!m_commands.empty())
        m_commands.pop_back();
}

bool Console::keyPressed(const OIS::KeyEvent& arg)
{
    if (arg.key == OIS::KeyCode::KC_UNASSIGNED)
    {
        m_visible = !m_visible;

        if (m_visible)
            show();
        else
            hide();
    }

    if (isVisible())
    {
        if (arg.key == OIS::KeyCode::KC_BACK)
        {
            if ((m_lines.substr(m_lines.size()-2, 1) == "$") || (m_lines.substr(m_lines.size()-2, 1) == "#"))
            {
                m_console->setText(m_lines);
                m_console->setProperty("CaratIndex", boost::lexical_cast<std::string>(m_console->getText().size()));
            }
        }
        else if (arg.key == OIS::KeyCode::KC_TAB)
            m_auto_completion();
        else if (arg.key == OIS::KeyCode::KC_RETURN)
            start();
        else if (arg.key == OIS::KeyCode::KC_LEFT || arg.key == OIS::KeyCode::KC_RIGHT)
            if (m_console->getProperty("CaratIndex") <= boost::lexical_cast<std::string>(m_lines.find_last_of(m_pattern)))
                m_console->setProperty("CaratIndex", boost::lexical_cast<std::string>(m_lines.find_last_of(m_pattern)+1));
        else if (arg.key == OIS::KeyCode::KC_UP || arg.key == OIS::KeyCode::KC_DOWN)
            if (!m_old_command.empty())
                m_show_old_command(arg);

        m_lines = std::string(m_console->getText().c_str());
    }

    return false;
}

bool Console::keyReleased(const OIS::KeyEvent& arg)
{
    if (arg.key == OIS::KeyCode::KC_UP || arg.key == OIS::KeyCode::KC_DOWN)
        m_console->setProperty("CaratIndex", boost::lexical_cast<std::string>(m_console->getText().size()));
    return true;
}

bool Console::mouseMoved(const OIS::MouseEvent& arg)
{
    return true;
}

bool Console::mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id )
{
    if (boost::lexical_cast<int>(m_console->getProperty("CaratIndex")) <= m_console->getText().find_last_of(m_pattern))
                m_console->setProperty("CaratIndex", boost::lexical_cast<std::string>(m_console->getText().size()));
    return true;
}

bool Console::mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id )
{
    return true;
}


CEGUI::Window *Console::getConsole()
{
    return m_console;
}
