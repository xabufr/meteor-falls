#include "SoundSetting.h"

SoundSetting::SoundSetting(StateManager* mgr):State(mgr)
{
    CEGUI::WindowManager &m_window_manager = CEGUI::WindowManager::getSingleton();

    m_activate = (CEGUI::Checkbox*)m_window_manager.createWindow("OgreTray/Checkbox", "CheckBoxActivate");
    m_activate->setPosition(CEGUI::UVector2(CEGUI::UDim(0.05, 0),
                                         CEGUI::UDim(0.05, 0)));
    m_activate->setText("Activer le son");
    CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->addChildWindow(m_activate);

    m_cancel = (CEGUI::PushButton*)m_window_manager.createWindow("OgreTray/Button", "ButtonCancel");
    m_cancel->setSize(CEGUI::UVector2(CEGUI::UDim(0.30, 0), CEGUI::UDim(0.20, 0)));
    m_cancel->setPosition(CEGUI::UVector2(CEGUI::UDim(0.95-m_cancel->getSize().d_x.d_scale, 0),
                                         CEGUI::UDim(0.95-m_cancel->getSize().d_y.d_scale
                                                        , 0)));
    m_cancel->setText("Cancel");
    CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->addChildWindow(m_cancel);

    m_accept = (CEGUI::PushButton*)m_window_manager.createWindow("OgreTray/Button", "ButtonOk");
    m_accept->setSize(CEGUI::UVector2(CEGUI::UDim(0.30, 0), CEGUI::UDim(0.20, 0)));
    m_accept->setPosition(CEGUI::UVector2(CEGUI::UDim(0.85-(m_accept->getSize().d_x.d_scale+m_cancel->getSize().d_x.d_scale), 0),
                                         CEGUI::UDim(0.95-m_accept->getSize().d_y.d_scale
                                                        , 0)));
    m_accept->setText("Ok");
    CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->addChildWindow(m_accept);
}
SoundSetting::~SoundSetting()
{

}
bool SoundSetting::isVisible()
{
    return m_visible;
}

void SoundSetting::enter()
{
    m_visible = true;
}

void SoundSetting::exit()
{
    m_visible = false;
}

ret_code SoundSetting::work(unsigned int)
{
    return CONTINUE;
}
