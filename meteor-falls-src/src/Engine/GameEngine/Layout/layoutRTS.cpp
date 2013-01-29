#include "layoutRTS.h"

LayoutRTS::LayoutRTS(StateManager* mgr)
: State(mgr)
{
    m_visible = false;
    CEGUI::WindowManager& m_window_manager = CEGUI::WindowManager::getSingleton();
    m_info_ressources = m_window_manager.createWindow("OgreTray/TabButtonPane", "WindowInfoRessource");
    m_info_ressources->setSize(CEGUI::UVector2(CEGUI::UDim(1,0), CEGUI::UDim(0.07,0)));
    m_info_ressources->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0), CEGUI::UDim(0,0)));
    CEGUI::System::getSingleton().getGUISheet()->addChildWindow(m_info_ressources);

    m_grille_batiments = m_window_manager.createWindow("OgreTray/TabButtonPane", "WindowGrilleBatiment");
    m_grille_batiments->setSize(CEGUI::UVector2(CEGUI::UDim(0.3,0), CEGUI::UDim(0.3,0)));
    m_grille_batiments->setPosition(CEGUI::UVector2(CEGUI::UDim(0.7,0), CEGUI::UDim(0.7,0)));
    CEGUI::System::getSingleton().getGUISheet()->addChildWindow(m_grille_batiments);

    m_position_map = m_window_manager.createWindow("OgreTray/TabButtonPane", "WindowCarte");
    m_position_map->setSize(CEGUI::UVector2(CEGUI::UDim(0.3,0), CEGUI::UDim(0.3,0)));
    m_position_map->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0), CEGUI::UDim(0.7,0)));
    CEGUI::System::getSingleton().getGUISheet()->addChildWindow(m_position_map);

    m_infos_unite = m_window_manager.createWindow("OgreTray/TabButtonPane", "WindowInfosUnites");
    m_infos_unite->setSize(CEGUI::UVector2(CEGUI::UDim(0.4,0), CEGUI::UDim(0.22,0)));
    m_infos_unite->setPosition(CEGUI::UVector2(CEGUI::UDim(0.3,0), CEGUI::UDim(0.78,0)));
    CEGUI::System::getSingleton().getGUISheet()->addChildWindow(m_infos_unite);


    m_position_map->hide();
    m_infos_unite->hide();
    m_grille_batiments->hide();
    m_info_ressources->hide();

}

LayoutRTS::~LayoutRTS()
{
    CEGUI::System::getSingleton().getGUISheet()->removeChildWindow(m_info_ressources);
    CEGUI::WindowManager::getSingleton().destroyWindow(m_info_ressources);
    CEGUI::System::getSingleton().getGUISheet()->removeChildWindow(m_grille_batiments);
    CEGUI::WindowManager::getSingleton().destroyWindow(m_grille_batiments);
    CEGUI::System::getSingleton().getGUISheet()->removeChildWindow(m_position_map);
    CEGUI::WindowManager::getSingleton().destroyWindow(m_position_map);
    CEGUI::System::getSingleton().getGUISheet()->removeChildWindow(m_infos_unite);
    CEGUI::WindowManager::getSingleton().destroyWindow(m_infos_unite);
}


ret_code LayoutRTS::work(unsigned int)
{
    return CONTINUE;
}


void LayoutRTS::exit()
{
    m_visible = false;
    m_info_ressources->hide();
    m_grille_batiments->hide();
    m_position_map->hide();
    m_infos_unite->hide();
}

void LayoutRTS::enter()
{
    m_visible = true;
    m_info_ressources->show();
    m_grille_batiments->show();
    m_position_map->show();
    m_infos_unite->show();
}


bool LayoutRTS::isVisible()
{
    return m_visible;
}

