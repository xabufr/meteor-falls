#include "State/Console.h"
#include "Engine/GraphicEngine/Ogre/OgreWindowInputManager.h"
#include "Engine/GraphicEngine/Ogre/ogrecontextmanager.h"
#include "Engine/GraphicEngine/Ogre/OgreApplication.h"
#include "State/Game/GameState.h"

 Console::~Console()
{
    delete m_sheet;
    delete m_console;
}

 Console::Console()
{
    m_mouse = OgreContextManager::get()->getInputManager()->getMouse();
    m_keyboard = OgreContextManager::get()->getInputManager()->getKeyboard();

    CEGUI::WindowManager &m_window_mgr = CEGUI::WindowManager::getSingleton();

    m_sheet = m_window_mgr.createWindow("OgreTray/TabButtonPane", "FenetreConsole");

    m_console = m_window_mgr.createWindow("Ogre/Editbox", "Console");
    m_sheet->addChildWindow(m_console);

    CEGUI::System::getSingleton().setGUISheet(m_sheet);
    m_sheet->hide();
}

void Console::hide()
{
    m_sheet->hide();
}

void Console::show()
{
    m_sheet->show();
}

