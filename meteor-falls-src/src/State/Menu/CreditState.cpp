#include "CreditState.h"

CreditState::CreditState(StateManager* mgr) : State(mgr), m_visible(false)
{
    CEGUI::WindowManager &m_window_mgr = CEGUI::WindowManager::getSingleton();

    m_credit = m_window_mgr.createWindow("OgreTray/StaticText", "TextCredit");
    m_credit->setSize(CEGUI::UVector2(CEGUI::UDim(0.50, 0), CEGUI::UDim(0.60, 0)));
    m_credit->setPosition(CEGUI::UVector2(CEGUI::UDim(0.50-(m_credit->getSize().d_x.d_scale/2), 0),
                                         CEGUI::UDim((m_credit->getSize().d_y.d_scale
                                                        /(CEGUI::System::getSingleton().getGUISheet()->getChildCount()+1)), 0)));
    m_credit->setText((CEGUI::utf8*)("Crédit:\nProgrammeur:\nThomas Loubiou\nAlexandre Ramel\nBastien Chevriaut\nFabrice Bats"));
    m_credit->setProperty("HorzFormatting", "WordWrapCentred");
    CEGUI::System::getSingleton().getGUISheet()->addChildWindow(m_credit);
    m_credit->hide();
}

CreditState::~CreditState()
{
    delete m_credit;
}

bool CreditState::isVisible()
{
    return m_visible;
}

void CreditState::enter()
{
    m_credit->show();
    m_visible = true;
}

void CreditState::exit()
{
    m_credit->hide();
    m_visible = false;
}

ret_code CreditState::work(unsigned int time)
{
    return CONTINUE;
}
