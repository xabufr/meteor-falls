#include "GraphicSetting.h"
#include "../../Utils/Configuration/Config.h"
#include "../../precompiled/lexical_cast.h"
#include <OgreRoot.h>
#include <OgreRenderSystem.h>
#include <string>
#include <iostream>

GraphicSetting::GraphicSetting(StateManager* mgr):State(mgr),
m_state_manager(mgr)
{
    Config::get()->getGraphicConfig()->loadConfig();
    CEGUI::WindowManager &m_window_manager = CEGUI::WindowManager::getSingleton();
    int nb = 0;
    for (Ogre::ConfigOption m : Config::get()->getGraphicConfig()->getConfig())
    {
        CEGUI::Window *elem = m_window_manager.createWindow("OgreTray/StaticText", "TextGraphic"+boost::lexical_cast<std::string>(nb));
        elem->setSize(CEGUI::UVector2(CEGUI::UDim(0.45, 0), CEGUI::UDim(0.10, 0)));
        elem->setPosition(CEGUI::UVector2(CEGUI::UDim(0.05, 0),
                                         CEGUI::UDim(0.06+(nb*(0.10)), 0)));
        elem->setText(m.name);
        elem->setProperty("FrameEnabled", "false");
        elem->setProperty("BackgroundEnabled", "false");
        elem->setProperty("VertFormatting", "TopAligned");
        elem->hide();
        CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->addChildWindow(elem);

        CEGUI::Combobox *comb = (CEGUI::Combobox*)m_window_manager.createWindow("OgreTray/Combobox", "ComboBoxGraphic"+boost::lexical_cast<std::string>(nb));
        for (std::string s : m.possibleValues)
        {
            CEGUI::ListboxTextItem *item = new CEGUI::ListboxTextItem(s);
            comb->addItem(item);
            comb->setReadOnly(true);
            if (s == m.currentValue)
                comb->setItemSelectState(item, true);
        }

        comb->setSize(CEGUI::UVector2(CEGUI::UDim(0.40, 0), CEGUI::UDim(0.30, 0)));
        comb->setPosition(CEGUI::UVector2(CEGUI::UDim(elem->getSize().d_x.d_scale, 0),
                                         CEGUI::UDim(0.05+(nb*(0.10)), 0)));
        comb->hide();
        CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->addChildWindow(comb);
        ++nb;
    }

    m_cancel = (CEGUI::PushButton*)m_window_manager.createWindow("OgreTray/Button", "ButtonCancel2");
    m_cancel->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.10, 0)));
    m_cancel->setPosition(CEGUI::UVector2(CEGUI::UDim(0.95-m_cancel->getSize().d_x.d_scale, 0),
                                         CEGUI::UDim(0.95-m_cancel->getSize().d_y.d_scale
                                                        , 0)));
    m_cancel->setText("Cancel");
    m_cancel->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GraphicSetting::m_button_pushed, this));
    CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->addChildWindow(m_cancel);
    m_cancel->hide();

    m_accept = (CEGUI::PushButton*)m_window_manager.createWindow("OgreTray/Button", "ButtonOk2");
    m_accept->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.10, 0)));
    m_accept->setPosition(CEGUI::UVector2(CEGUI::UDim(0.85-(m_accept->getSize().d_x.d_scale+m_cancel->getSize().d_x.d_scale), 0),
                                         CEGUI::UDim(0.95-m_accept->getSize().d_y.d_scale
                                                        , 0)));
    m_accept->setText("Ok");
    m_accept->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GraphicSetting::m_button_pushed, this));
    CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->addChildWindow(m_accept);
    m_accept->hide();

    m_visible = false;
}
GraphicSetting::~GraphicSetting()
{
    for (int i=0; i<Ogre::Root::getSingleton().getRenderSystem()->getConfigOptions().size(); ++i)
    {
        CEGUI::Window *current = CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->getChild("TextGraphic"+boost::lexical_cast<std::string>(i));
        CEGUI::System::getSingleton().getGUISheet()->removeChildWindow(current);
        CEGUI::WindowManager::getSingleton().destroyWindow(current);

        current = CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->getChild("ComboBoxGraphic"+boost::lexical_cast<std::string>(i));
        CEGUI::System::getSingleton().getGUISheet()->removeChildWindow(current);
        CEGUI::WindowManager::getSingleton().destroyWindow(current);
    }
    CEGUI::System::getSingleton().getGUISheet()->removeChildWindow(m_accept);
    CEGUI::WindowManager::getSingleton().destroyWindow(m_accept);
    CEGUI::System::getSingleton().getGUISheet()->removeChildWindow(m_cancel);
    CEGUI::WindowManager::getSingleton().destroyWindow(m_cancel);
}

bool GraphicSetting::isVisible()
{
    return m_visible;
}

void GraphicSetting::enter()
{
    m_visible = true;
    for (int i=0; i<Ogre::Root::getSingleton().getRenderSystem()->getConfigOptions().size(); ++i)
    {
        CEGUI::Window *current = CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->getChild("TextGraphic"+boost::lexical_cast<std::string>(i));
        CEGUI::Window *currentComb = CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->getChild("ComboBoxGraphic"+boost::lexical_cast<std::string>(i));
        current->show();
        currentComb->show();
    }
    m_cancel->show();
    m_accept->show();

    CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->setSize(CEGUI::UVector2(CEGUI::UDim(0.6,0), CEGUI::UDim(0.6, 0)));
    CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->setPosition(CEGUI::UVector2(CEGUI::UDim(0.50-(CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->getSize().d_x.d_scale/2), 0),
                                         CEGUI::UDim(0.50-(CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->getSize().d_y.d_scale
                                                        /2), 0)));
}

void GraphicSetting::exit()
{
    m_visible = false;
    for (int i=0; i<Ogre::Root::getSingleton().getRenderSystem()->getConfigOptions().size(); ++i)
    {
        CEGUI::Window *current = CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->getChild("TextGraphic"+boost::lexical_cast<std::string>(i));
        CEGUI::Window *currentComb = CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->getChild("ComboBoxGraphic"+boost::lexical_cast<std::string>(i));
        current->hide();
        currentComb->hide();
    }
    m_cancel->hide();
    m_accept->hide();

    CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->setSize(CEGUI::UVector2(CEGUI::UDim(0.3,0), CEGUI::UDim(0.3, 0)));
    CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->setPosition(CEGUI::UVector2(CEGUI::UDim(0.50-(CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->getSize().d_x.d_scale/2), 0),
                                         CEGUI::UDim(0.50-(CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->getSize().d_y.d_scale
                                                        /2), 0)));
}

ret_code GraphicSetting::work(unsigned int)
{
    return CONTINUE;
}

bool GraphicSetting::m_button_pushed(const CEGUI::EventArgs&)
{
    if (m_cancel->isPushed())
        m_visible = false;
    else if(m_accept->isPushed())
    {
        Config::get()->getGraphicConfig()->saveConfig();
        m_visible = false;
    }

    return true;
}
