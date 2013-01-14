#include "TeamState.h"

TeamState::TeamState(StateManager* mgr, GameEngine* engine):State(mgr),
m_visible(true),
m_game_engine(engine)
{
    CEGUI::WindowManager &m_window_manager = CEGUI::WindowManager::getSingleton();
    m_window = (CEGUI::TabButton*)m_window_manager.createWindow("OgreTray/TabButton", "TeamState");
    m_window->setSize(CEGUI::UVector2(CEGUI::UDim(0.50, 0), CEGUI::UDim(0.60, 0)));
    m_window->setPosition(CEGUI::UVector2(CEGUI::UDim(0.50-(m_window->getSize().d_x.d_scale/2), 0),
                                         CEGUI::UDim((m_window->getSize().d_y.d_scale
                                                        /2), 0)));
    CEGUI::System::getSingleton().getGUISheet()->addChildWindow(m_window);

    m_rts = (CEGUI::PushButton*)m_window_manager.createWindow("OgreTray/Button", "ButtonRTS");
    m_rts->setSize(CEGUI::UVector2(CEGUI::UDim(0.20, 0), CEGUI::UDim(0.10, 0)));
    m_rts->setPosition(CEGUI::UVector2(CEGUI::UDim(0.50-(m_rts->getSize().d_x.d_scale/2), 0),
                                         CEGUI::UDim((m_rts->getSize().d_y.d_scale
                                                        /2), 0)));
    m_rts->setText("RTS");
    m_window->addChildWindow(m_rts);
    m_rpg = (CEGUI::PushButton*)m_window_manager.createWindow("OgreTray/Button", "ButtonRPG");
    m_rpg->setSize(CEGUI::UVector2(CEGUI::UDim(0.20, 0), CEGUI::UDim(0.10, 0)));
    m_rpg->setPosition(CEGUI::UVector2(CEGUI::UDim(0.50-(m_rpg->getSize().d_x.d_scale/2), 0),
                                         CEGUI::UDim((m_rpg->getSize().d_y.d_scale
                                                        /2), 0)));
    m_rpg->setText("RPG");
    m_window->addChildWindow(m_rpg);

    /*m_chat = (CEGUI::MultiLineEditbox*)(m_window_manager.createWindow("OgreTray/MultiLineEditbox", "Chat"));
    m_chat->setSize(CEGUI::UVector2(CEGUI::UDim(0.20, 0), CEGUI::UDim(0.40, 0)));
    m_chat->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 0),
                                         CEGUI::UDim((1-m_chat->getSize().d_y.d_scale), 0)));
    CEGUI::System::getSingleton().getGUISheet()->addChildWindow(m_chat);*/
}

TeamState::~TeamState()
{
    delete m_window;
    delete m_rts;
    delete m_rpg;
    //delete m_chat;
    //delete m_edit;
}

bool TeamState::isVisible()
{
    return m_visible;
}

void TeamState::enter()
{
    m_window->show();
    //m_chat->show();
    m_visible = true;
}

void TeamState::exit()
{
    m_window->hide();
    //m_chat->hide();
    m_visible = false;
}

ret_code TeamState::work(unsigned int time)
{
    std::cout << "truc" << std::endl;
    return CONTINUE;
}

