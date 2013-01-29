#include "layoutRTS.h"

LayoutRTS::LayoutRTS(StateManager* mgr)
: State(mgr)
{
    m_visible = false;
std::cout << " 0 " << std::endl;
    CEGUI::WindowManager& m_window_manager = CEGUI::WindowManager::getSingleton();
std::cout << " init " << std::endl;
    m_info_res = m_window_manager.createWindow("OgreTray/TabButton", "WindowInfoRes");
std::cout << " create window " << std::endl;
    m_info_res->setSize(CEGUI::UVector2(CEGUI::UDim(1,0), CEGUI::UDim(0.1,0)));
    m_info_res->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0), CEGUI::UDim(0,0)));
std::cout << " size + dim " << std::endl;
    CEGUI::System::getSingleton().getGUISheet()->addChildWindow(m_info_res);

std::cout << " addchildwindow " << std::endl;

    m_info_res->hide();

std::cout << " hide " << std::endl;
}

LayoutRTS::~LayoutRTS()
{
    CEGUI::System::getSingleton().getGUISheet()->removeChildWindow(m_info_res);
    CEGUI::WindowManager::getSingleton().destroyWindow(m_info_res);
}


ret_code LayoutRTS::work(unsigned int)
{
    return CONTINUE;
}


void LayoutRTS::exit()
{
    m_visible = false;
    m_info_res->hide();
}

void LayoutRTS::enter()
{
    m_visible = true;
    m_info_res->show();
}


bool LayoutRTS::isVisible()
{
    return m_visible;
}

