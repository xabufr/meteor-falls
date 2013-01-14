#include "State/Console.h"
#include "Engine/ScriptEngine/XmlDocumentManager.h"
#include "Engine/GraphicEngine/Ogre/OgreWindowInputManager.h"
#include "Engine/GraphicEngine/Ogre/ogrecontextmanager.h"
#include "Engine/GraphicEngine/Ogre/OgreApplication.h"
#include "State/Game/GameState.h"
#include <boost/regex.hpp>

 Console::~Console()
{
    delete m_sheet;
    delete m_console;
}

Console::Console() : m_visible(false), m_lines("")
{
    m_keyboard = OgreContextManager::get()->getInputManager()->getKeyboard();

    CEGUI::WindowManager &m_window_mgr = CEGUI::WindowManager::getSingleton();

    m_sheet = m_window_mgr.createWindow("DefaultWindow", "FenetreConsole");


    m_console = m_window_mgr.createWindow("OgreTray/MultiLineEditbox", "Console");
    m_console->setSize(CEGUI::UVector2(CEGUI::UDim(1, 0), CEGUI::UDim(0.2, 0)));
    m_sheet->addChildWindow(m_console);

    CEGUI::System::getSingleton().getGUISheet()->addChildWindow(m_sheet);
    m_sheet->hide();
}

void Console::start()
{
    if (m_lines == std::string(m_console->getText().c_str()))
        return;
    int debut = m_lines.length()-1;
    m_lines = std::string(m_console->getText().c_str());
    int fin=m_lines.length()-2;

    debut = (debut < 0)?0:debut;
    std::string line = m_lines.substr(debut, (fin-debut));
    for (unsigned int i=0; i<m_commands.size(); ++i)
    {
        boost::regex expName("^"+m_commands[i]->getName()+"+[ a-z]*");
        if (boost::regex_match(line, expName))
        {
            if (!m_commands[i]->getProperties().empty())
            {
                std::vector<std::string> properties = m_commands[i]->getProperties();
                for (unsigned int j=0; j<properties.size(); ++j)
                {
                    boost::regex expProp("^"+m_commands[i]->getName()+" "+properties[j]+"$");
                    if (boost::regex_match(line, expProp))
                        m_commands[i]->setUsedPropertie(properties[j]);
                }
            }
            m_commands[i]->use();
        }
    }
}

bool Console::isVisible()
{
    return m_visible;
}

void Console::hide()
{
    m_sheet->hide();
    m_visible = false;
    m_console->setText("");
}

void Console::show()
{
    m_sheet->show();
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


