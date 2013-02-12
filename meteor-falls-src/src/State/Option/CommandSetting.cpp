#include "CommandSetting.h"
#include "../../Utils/Configuration/Config.h"
#include "../../Utils/Configuration/CommandConfig.h"
#include "../../precompiled/lexical_cast.h"


CommandSetting::CommandSetting(StateManager* mgr):State(mgr)
{
    CEGUI::WindowManager &m_window_manager = CEGUI::WindowManager::getSingleton();

    m_pane = (CEGUI::ScrollablePane*)m_window_manager.createWindow("OgreTray/ScrollablePane", "PaneCommand");
    m_pane->setSize(CEGUI::UVector2(CEGUI::UDim(0.9,0), CEGUI::UDim(0.8, 0)));
    m_pane->setPosition(CEGUI::UVector2(CEGUI::UDim(0.05, 0),
                                         CEGUI::UDim(0.05, 0)));
    m_pane->setVerticalScrollPosition(0.1);

    m_cancel = (CEGUI::PushButton*)m_window_manager.createWindow("OgreTray/Button", "ButtonCancel3");
    m_cancel->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.10, 0)));
    m_cancel->setPosition(CEGUI::UVector2(CEGUI::UDim(0.95-m_cancel->getSize().d_x.d_scale, 0),
                                         CEGUI::UDim(0.95-m_cancel->getSize().d_y.d_scale
                                                        , 0)));
    m_cancel->setText("Cancel");
    m_cancel->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CommandSetting::m_button_pushed, this));
    CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->addChildWindow(m_cancel);
    m_cancel->hide();

    m_accept = (CEGUI::PushButton*)m_window_manager.createWindow("OgreTray/Button", "ButtonOk3");
    m_accept->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.10, 0)));
    m_accept->setPosition(CEGUI::UVector2(CEGUI::UDim(0.85-(m_accept->getSize().d_x.d_scale+m_cancel->getSize().d_x.d_scale), 0),
                                         CEGUI::UDim(0.95-m_accept->getSize().d_y.d_scale
                                                        , 0)));
    m_accept->setText("Ok");
    m_accept->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CommandSetting::m_button_pushed, this));
    CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->addChildWindow(m_accept);
    m_accept->hide();

    CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->addChildWindow(m_pane);

    CommandConfig::KeyAction* keys = Config::get()->getCommandConfig()->getKeyRTS();
    for (int i=0; i<CommandConfig::KeyRPG::RPG_COUNT; ++i)
    {
        CEGUI::Window *elem = m_window_manager.createWindow("OgreTray/StaticText", "TextContrôle"+boost::lexical_cast<std::string>(i));
        elem->setSize(CEGUI::UVector2(CEGUI::UDim(0.45, 0), CEGUI::UDim(0.10, 0)));
        elem->setPosition(CEGUI::UVector2(CEGUI::UDim(0.05, 0),
                                         CEGUI::UDim(0.06+(i*(0.10)), 0)));
        elem->setText((CEGUI::utf8*)keys[i].description.c_str());
        elem->setProperty("FrameEnabled", "false");
        elem->setProperty("BackgroundEnabled", "false");
        elem->setProperty("VertFormatting", "TopAligned");
        m_pane->addChildWindow(elem);
    }

    m_pane->hide();
    m_visible = false;
}

CommandSetting::~CommandSetting()
{
    CEGUI::System::getSingleton().getGUISheet()->removeChildWindow(m_accept);
    CEGUI::WindowManager::getSingleton().destroyWindow(m_accept);
    CEGUI::System::getSingleton().getGUISheet()->removeChildWindow(m_cancel);
    CEGUI::WindowManager::getSingleton().destroyWindow(m_cancel);
    CEGUI::System::getSingleton().getGUISheet()->removeChildWindow(m_pane);
    CEGUI::WindowManager::getSingleton().destroyWindow(m_pane);
    for (int i=0; i<CommandConfig::KeyRPG::RPG_COUNT; ++i)
    {
        CEGUI::Window *current = CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->getChild("TextContrôle"+boost::lexical_cast<std::string>(i));
        CEGUI::System::getSingleton().getGUISheet()->removeChildWindow(current);
        CEGUI::WindowManager::getSingleton().destroyWindow(current);
    }
}

bool CommandSetting::isVisible()
{
    return m_visible;
}

void CommandSetting::enter()
{
    m_visible = true;
    m_pane->show();
    m_cancel->show();
    m_accept->show();
    CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->setSize(CEGUI::UVector2(CEGUI::UDim(0.6,0), CEGUI::UDim(0.6, 0)));
    CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->setPosition(CEGUI::UVector2(CEGUI::UDim(0.50-(CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->getSize().d_x.d_scale/2), 0),
                                         CEGUI::UDim(0.50-(CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->getSize().d_y.d_scale
                                                        /2), 0)));
}

void CommandSetting::exit()
{
    m_visible = false;
    m_pane->hide();
    m_cancel->hide();
    m_accept->hide();
    CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->setSize(CEGUI::UVector2(CEGUI::UDim(0.3,0), CEGUI::UDim(0.3, 0)));
    CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->setPosition(CEGUI::UVector2(CEGUI::UDim(0.50-(CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->getSize().d_x.d_scale/2), 0),
                                         CEGUI::UDim(0.50-(CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->getSize().d_y.d_scale
                                                        /2), 0)));
}

ret_code CommandSetting::work(unsigned int)
{
    return CONTINUE;
}

bool CommandSetting::m_button_pushed(const CEGUI::EventArgs&)
{
    if (m_cancel->isPushed())
        m_visible = false;
}
