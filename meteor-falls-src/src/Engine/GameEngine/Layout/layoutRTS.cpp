#include "layoutRTS.h"

LayoutRTS::LayoutRTS(StateManager* mgr, Joueur *j)
: State(mgr)
, m_joueur(j)
{
    m_visible = false;

    CEGUI::WindowManager& m_window_manager = CEGUI::WindowManager::getSingleton();
    m_info_ressources = m_window_manager.createWindow("OgreTray/TabButtonPane", "WindowInfoRessource");
    m_info_ressources->setSize(CEGUI::UVector2(CEGUI::UDim(1,0), CEGUI::UDim(0.07,0)));
    m_info_ressources->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0), CEGUI::UDim(0,0)));
    CEGUI::System::getSingleton().getGUISheet()->addChildWindow(m_info_ressources);

    /**
        Grille batiments
    **/

    m_grille_batiments = m_window_manager.createWindow("OgreTray/TabButtonPane", "WindowGrilleBatiment");
    m_grille_batiments->setSize(CEGUI::UVector2(CEGUI::UDim(0.3,0), CEGUI::UDim(0.3,0)));
    m_grille_batiments->setPosition(CEGUI::UVector2(CEGUI::UDim(0.7,0), CEGUI::UDim(0.7,0)));
    CEGUI::System::getSingleton().getGUISheet()->addChildWindow(m_grille_batiments);

    m_grille_batimentsA = (CEGUI::PushButton*)m_window_manager.createWindow("OgreTray/Button", "BUTTONGrilleBatiment_LettreA");
    m_grille_batimentsA->setSize(CEGUI::UVector2(CEGUI::UDim(0.1,0), CEGUI::UDim(0.1,0)));
    m_grille_batimentsA->setPosition(CEGUI::UVector2(CEGUI::UDim(0.7,0), CEGUI::UDim(0.7,0)));
    m_grille_batimentsA->setText("Batiment principal");
    m_grille_batimentsA->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&LayoutRTS::m_choix_grille, this));
    CEGUI::System::getSingleton().getGUISheet()->addChildWindow(m_grille_batimentsA);

    m_grille_batimentsZ = (CEGUI::PushButton*)m_window_manager.createWindow("OgreTray/Button", "BUTTONGrilleBatiment_LettreZ");
    m_grille_batimentsZ->setSize(CEGUI::UVector2(CEGUI::UDim(0.1,0), CEGUI::UDim(0.1,0)));
    m_grille_batimentsZ->setPosition(CEGUI::UVector2(CEGUI::UDim(0.8,0), CEGUI::UDim(0.7,0)));
    m_grille_batimentsZ->setText("Depot");
    m_grille_batimentsZ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&LayoutRTS::m_choix_grille, this));
    CEGUI::System::getSingleton().getGUISheet()->addChildWindow(m_grille_batimentsZ);

    m_grille_batimentsE = (CEGUI::PushButton*)m_window_manager.createWindow("OgreTray/Button", "BUTTONGrilleBatiment_LettreE");
    m_grille_batimentsE->setSize(CEGUI::UVector2(CEGUI::UDim(0.1,0), CEGUI::UDim(0.1,0)));
    m_grille_batimentsE->setPosition(CEGUI::UVector2(CEGUI::UDim(0.9,0), CEGUI::UDim(0.7,0)));
    m_grille_batimentsE->setText("Caserne");
    m_grille_batimentsE->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&LayoutRTS::m_choix_grille, this));
    CEGUI::System::getSingleton().getGUISheet()->addChildWindow(m_grille_batimentsE);

    m_grille_batimentsQ = (CEGUI::PushButton*)m_window_manager.createWindow("OgreTray/Button", "BUTTONGrilleBatiment_LettreQ");
    m_grille_batimentsQ->setSize(CEGUI::UVector2(CEGUI::UDim(0.1,0), CEGUI::UDim(0.1,0)));
    m_grille_batimentsQ->setPosition(CEGUI::UVector2(CEGUI::UDim(0.7,0), CEGUI::UDim(0.8,0)));
    m_grille_batimentsQ->setText("Centre Technique");
    m_grille_batimentsQ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&LayoutRTS::m_choix_grille, this));
    CEGUI::System::getSingleton().getGUISheet()->addChildWindow(m_grille_batimentsQ);

    m_grille_batimentsS = (CEGUI::PushButton*)m_window_manager.createWindow("OgreTray/Button", "BUTTONGrilleBatiment_LettreS");
    m_grille_batimentsS->setSize(CEGUI::UVector2(CEGUI::UDim(0.1,0), CEGUI::UDim(0.1,0)));
    m_grille_batimentsS->setPosition(CEGUI::UVector2(CEGUI::UDim(0.8,0), CEGUI::UDim(0.8,0)));
    m_grille_batimentsS->setText("Boutique");
    m_grille_batimentsS->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&LayoutRTS::m_choix_grille, this));
    CEGUI::System::getSingleton().getGUISheet()->addChildWindow(m_grille_batimentsS);

    m_grille_batimentsD = (CEGUI::PushButton*)m_window_manager.createWindow("OgreTray/Button", "BUTTONGrilleBatiment_LettreD");
    m_grille_batimentsD->setSize(CEGUI::UVector2(CEGUI::UDim(0.1,0), CEGUI::UDim(0.1,0)));
    m_grille_batimentsD->setPosition(CEGUI::UVector2(CEGUI::UDim(0.9,0), CEGUI::UDim(0.8,0)));
    m_grille_batimentsD->setText("Batiment population");
    m_grille_batimentsD->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&LayoutRTS::m_choix_grille, this));
    CEGUI::System::getSingleton().getGUISheet()->addChildWindow(m_grille_batimentsD);

    m_grille_batimentsW = (CEGUI::PushButton*)m_window_manager.createWindow("OgreTray/Button", "BUTTONGrilleBatiment_LettreW");
    m_grille_batimentsW->setSize(CEGUI::UVector2(CEGUI::UDim(0.1,0), CEGUI::UDim(0.1,0)));
    m_grille_batimentsW->setPosition(CEGUI::UVector2(CEGUI::UDim(0.7,0), CEGUI::UDim(0.9,0)));
    m_grille_batimentsW->setText("Defense");
    m_grille_batimentsW->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&LayoutRTS::m_choix_grille, this));
    CEGUI::System::getSingleton().getGUISheet()->addChildWindow(m_grille_batimentsW);

    m_grille_batimentsX = (CEGUI::PushButton*)m_window_manager.createWindow("OgreTray/Button", "BUTTONGrilleBatiment_LettreX");
    m_grille_batimentsX->setSize(CEGUI::UVector2(CEGUI::UDim(0.1,0), CEGUI::UDim(0.1,0)));
    m_grille_batimentsX->setPosition(CEGUI::UVector2(CEGUI::UDim(0.8,0), CEGUI::UDim(0.9,0)));
    m_grille_batimentsX->setText("Meteorite");
    m_grille_batimentsX->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&LayoutRTS::m_choix_grille, this));
    CEGUI::System::getSingleton().getGUISheet()->addChildWindow(m_grille_batimentsX);

    m_grille_batimentsC = (CEGUI::PushButton*)m_window_manager.createWindow("OgreTray/Button", "BUTTONGrilleBatiment_LettreC");
    m_grille_batimentsC->setSize(CEGUI::UVector2(CEGUI::UDim(0.1,0), CEGUI::UDim(0.1,0)));
    m_grille_batimentsC->setPosition(CEGUI::UVector2(CEGUI::UDim(0.9,0), CEGUI::UDim(0.9,0)));
    m_grille_batimentsC->setText("Batiment special");
    m_grille_batimentsC->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&LayoutRTS::m_choix_grille, this));
    CEGUI::System::getSingleton().getGUISheet()->addChildWindow(m_grille_batimentsC);


    /**
        Général
    **/

    m_position_map = m_window_manager.createWindow("OgreTray/TabButtonPane", "WindowCarte");
    m_position_map->setSize(CEGUI::UVector2(CEGUI::UDim(0.3,0), CEGUI::UDim(0.25,0)));
    m_position_map->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0), CEGUI::UDim(0.75,0)));
    CEGUI::System::getSingleton().getGUISheet()->addChildWindow(m_position_map);

    m_infos_unite = m_window_manager.createWindow("OgreTray/TabButtonPane", "WindowInfosUnites");
    m_infos_unite->setSize(CEGUI::UVector2(CEGUI::UDim(0.4,0), CEGUI::UDim(0.17,0)));
    m_infos_unite->setPosition(CEGUI::UVector2(CEGUI::UDim(0.3,0), CEGUI::UDim(0.83,0)));
    CEGUI::System::getSingleton().getGUISheet()->addChildWindow(m_infos_unite);
// setenable()=false
//

    m_position_map->hide();
    m_infos_unite->hide();
    m_grille_batiments->hide();
    m_grille_batimentsA->hide();
    m_grille_batimentsZ->hide();
    m_grille_batimentsE->hide();
    m_grille_batimentsQ->hide();
    m_grille_batimentsS->hide();
    m_grille_batimentsD->hide();
    m_grille_batimentsW->hide();
    m_grille_batimentsX->hide();
    m_grille_batimentsC->hide();
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
    m_grille_batimentsA->hide();
    m_grille_batimentsZ->hide();
    m_grille_batimentsE->hide();
    m_grille_batimentsQ->hide();
    m_grille_batimentsS->hide();
    m_grille_batimentsD->hide();
    m_grille_batimentsW->hide();
    m_grille_batimentsX->hide();
    m_grille_batimentsC->hide();
    m_position_map->hide();
    m_infos_unite->hide();
}

void LayoutRTS::enter()
{
    m_visible = true;
    m_info_ressources->show();
    m_grille_batiments->show();
    m_grille_batimentsA->show();
    m_grille_batimentsZ->show();
    m_grille_batimentsE->show();
    m_grille_batimentsQ->show();
    m_grille_batimentsS->show();
    m_grille_batimentsD->show();
    m_grille_batimentsW->show();
    m_grille_batimentsX->show();
    m_grille_batimentsC->show();
    m_position_map->show();
    m_infos_unite->show();
}


bool LayoutRTS::isVisible()
{
    return m_visible;
}

bool LayoutRTS::m_choix_grille(const CEGUI::EventArgs&)
{

    if (m_grille_batimentsA->isPushed())
        m_grille_batimentsA->setEnabled(false);

    if (m_grille_batimentsZ->isPushed())
        m_grille_batimentsZ->setEnabled(false);

    if (m_grille_batimentsE->isPushed())
        m_grille_batimentsE->setEnabled(false);

    if (m_grille_batimentsQ->isPushed())
        m_grille_batimentsQ->setEnabled(false);

    if (m_grille_batimentsS->isPushed())
        m_grille_batimentsS->setEnabled(false);

    if (m_grille_batimentsD->isPushed())
        m_grille_batimentsD->setEnabled(false);

    if (m_grille_batimentsW->isPushed())
        m_grille_batimentsW->setEnabled(false);

    if (m_grille_batimentsX->isPushed())
        m_grille_batimentsX->setEnabled(false);

    if (m_grille_batimentsC->isPushed())
        m_grille_batimentsC->setEnabled(false);


    return true;
}
