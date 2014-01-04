#include "CommandSetting.h"
#include "Engine/GraphicEngine/Ogre/ogrecontextmanager.h"
#include "Engine/GraphicEngine/Ogre/OgreWindowInputManager.h"
#include "../../Utils/Configuration/Config.h"
#include "../../Utils/Configuration/CommandConfig.h"
#include "../../precompiled/lexical_cast.h"


CommandSetting::CommandSetting(StateManager* mgr):State(mgr),
m_box_selected(nullptr)
{
    CEGUI::WindowManager &m_window_manager = CEGUI::WindowManager::getSingleton();
    m_keyboard = OgreContextManager::get()->getInputManager()->getKeyboard();
    m_mouse = OgreContextManager::get()->getInputManager()->getMouse();

    m_pane = (CEGUI::TabControl*)m_window_manager.createWindow("TaharezLook/TabControl", "PaneCommand");
    m_pane->setSize(CEGUI::USize(CEGUI::UDim(0.9,0), CEGUI::UDim(0.8, 0)));
    m_pane->setPosition(CEGUI::UVector2(CEGUI::UDim(0.05, 0),
                                         CEGUI::UDim(0.05, 0)));

    m_cancel = (CEGUI::PushButton*)m_window_manager.createWindow("TaharezLook/Button", "ButtonCancel3");
    m_cancel->setSize(CEGUI::USize(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.10, 0)));
    m_cancel->setPosition(CEGUI::UVector2(CEGUI::UDim(0.95-m_cancel->getSize().d_width.d_scale, 0),
                                         CEGUI::UDim(0.95-m_cancel->getSize().d_height.d_scale
                                                        , 0)));
    m_cancel->setText("Cancel");
    m_cancel->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CommandSetting::m_button_pushed, this));
    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChild("OptionState")->addChild(m_cancel);
    m_cancel->hide();

    m_accept = (CEGUI::PushButton*)m_window_manager.createWindow("TaharezLook/Button", "ButtonOk3");
    m_accept->setSize(CEGUI::USize(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.10, 0)));
    m_accept->setPosition(CEGUI::UVector2(CEGUI::UDim(0.85-(m_accept->getSize().d_width.d_scale+m_cancel->getSize().d_width.d_scale), 0),
                                         CEGUI::UDim(0.95-m_accept->getSize().d_height.d_scale
                                                        , 0)));
    m_accept->setText("Ok");
    m_accept->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CommandSetting::m_button_pushed, this));
    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChild("OptionState")->addChild(m_accept);
    m_accept->hide();

    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChild("OptionState")->addChild(m_pane);

    int maxi;
    std::string t;
    int nb = 0;
    //for (int i=0; i<3; ++i)
    int i = 0;
    for(;false;)
    {
        nb = 0;
        CommandConfig::KeyAction* keys = Config::get()->getCommandConfig()->getKeyMap()[i];
        if (i==0)
        {
            maxi = CommandConfig::KeyGlobal::GLOBAL_COUNT;
            t = "Global";
        }
        else if (i==1)
        {
            maxi = CommandConfig::KeyRPG::RPG_COUNT;
            t = "RPG";
        }
        else
        {
            maxi = CommandConfig::KeyRTS::RTS_COUNT;
            t = "RTS";
        }

        CEGUI::ScrollablePane *text = (CEGUI::ScrollablePane*)m_window_manager.createWindow("TaharezLook/ScrollablePane", "Controle"+boost::lexical_cast<std::string>(i));
        text->setSize(CEGUI::USize(CEGUI::UDim(1,0), CEGUI::UDim(1, 0)));
        text->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 0),
                                         CEGUI::UDim(0, 0)));
        text->setText(t.c_str());

        m_pane->addChild(text);

        for (int j=0; j<maxi; ++j)
        {
            CEGUI::Window *elem = text->createChild("TaharezLook/StaticText", "TextControle"+boost::lexical_cast<std::string>(i)+boost::lexical_cast<std::string>(j));
            elem->setSize(CEGUI::USize(CEGUI::UDim(0.30, 0), CEGUI::UDim(0.10, 0)));
            elem->setPosition(CEGUI::UVector2(CEGUI::UDim(0.05, 0),
                                             CEGUI::UDim(0.06+(nb*(0.10)), 0)));
            elem->setText((CEGUI::utf8*)keys[j].description.c_str());
            elem->setProperty("FrameEnabled", "false");
            elem->setProperty("BackgroundEnabled", "false");
            elem->setProperty("VertFormatting", "TopAligned");

            CEGUI::Editbox *box = (CEGUI::Editbox*)m_window_manager.createWindow("TaharezLook/Editbox", "BoxControle"+boost::lexical_cast<std::string>(i)+boost::lexical_cast<std::string>(j));
            box->setSize(CEGUI::USize(CEGUI::UDim(0.30, 0), CEGUI::UDim(0.10, 0)));
            box->setPosition(CEGUI::UVector2(CEGUI::UDim(0.35, 0),
                                             CEGUI::UDim(0.05+(nb*(0.10)), 0)));
            box->setReadOnly(true);
            box->subscribeEvent(CEGUI::Editbox::EventMouseClick, CEGUI::Event::Subscriber(&CommandSetting::m_box_pushed, this));
            OIS::Keyboard *keyboard = OgreContextManager::get()->getInputManager()->getKeyboard();
            if (keys[j].action[0].type == CommandConfig::KeyAction::Key::Type::KEYBOARD)
                box->setText(keyboard->getAsString(keys[j].action[0].keyboard));
            else
                box->setText(Config::get()->getCommandConfig()->toString(keys[j].action[0].mouse));
            box->setUserData(&keys[j].action[0]);
            text->addChild(box);

            box = (CEGUI::Editbox*)m_window_manager.createWindow("TaharezLook/Editbox", "BoxControle2"+boost::lexical_cast<std::string>(i)+boost::lexical_cast<std::string>(j));
            box->setSize(CEGUI::USize(CEGUI::UDim(0.30, 0), CEGUI::UDim(0.10, 0)));
            box->setPosition(CEGUI::UVector2(CEGUI::UDim(0.66, 0),
                                             CEGUI::UDim(0.05+(nb*(0.10)), 0)));
            box->setReadOnly(true);
            box->subscribeEvent(CEGUI::Editbox::EventMouseClick, CEGUI::Event::Subscriber(&CommandSetting::m_box_pushed, this));
            if (keys[j].action[1].type == CommandConfig::KeyAction::Key::Type::KEYBOARD)
                box->setText(keyboard->getAsString(keys[j].action[1].keyboard));
            else
                box->setText(Config::get()->getCommandConfig()->toString(keys[j].action[1].mouse));
            box->setUserData(&keys[j].action[1]);
            text->addChild(box);

            ++nb;
        }

        if (i==0)
        {
            CEGUI::Window *elem = m_window_manager.createWindow("TaharezLook/StaticText", "TextControle"+boost::lexical_cast<std::string>(i)+boost::lexical_cast<std::string>(maxi));
            elem->setSize(CEGUI::USize(CEGUI::UDim(0.30, 0), CEGUI::UDim(0.10, 0)));
            elem->setPosition(CEGUI::UVector2(CEGUI::UDim(0.05, 0),
                                             CEGUI::UDim(0.06+(3*(0.10)), 0)));
            elem->setText((CEGUI::utf8*)"Axe inversé");
            elem->setProperty("FrameEnabled", "false");
            elem->setProperty("BackgroundEnabled", "false");
            elem->setProperty("VertFormatting", "TopAligned");
            text->addChild(elem);

            CEGUI::ToggleButton *box = (CEGUI::ToggleButton*)m_window_manager.createWindow("TaharezLook/Checkbox", "CheckBox");
            box->setSize(CEGUI::USize(CEGUI::UDim(0.30, 0), CEGUI::UDim(0.10, 0)));
            box->setPosition(CEGUI::UVector2(CEGUI::UDim(0.35, 0),
                                             CEGUI::UDim(0.05+(3*(0.10)), 0)));
            box->subscribeEvent(CEGUI::ToggleButton::EventSelectStateChanged, CEGUI::Event::Subscriber(&CommandSetting::m_checkbox_pushed, this));
            box->setSelected(Config::get()->getCommandConfig()->axesInvers());
            text->addChild(box);

            elem = m_window_manager.createWindow("TaharezLook/StaticText", "TextControle"+boost::lexical_cast<std::string>(i)+boost::lexical_cast<std::string>(maxi+1));
            elem->setSize(CEGUI::USize(CEGUI::UDim(0.30, 0), CEGUI::UDim(0.10, 0)));
            elem->setPosition(CEGUI::UVector2(CEGUI::UDim(0.05, 0),
                                             CEGUI::UDim(0.06+(4*(0.10)), 0)));
            elem->setText((CEGUI::utf8*)"Sensibilité");
            elem->setProperty("FrameEnabled", "false");
            elem->setProperty("BackgroundEnabled", "false");
            elem->setProperty("VertFormatting", "TopAligned");
            text->addChild(elem);

            CEGUI::Slider* slide = (CEGUI::Slider*)m_window_manager.createWindow("TaharezLook/Slider", "Slider");
            slide->setSize(CEGUI::USize(CEGUI::UDim(0.30, 0), CEGUI::UDim(0.10, 0)));
            slide->setPosition(CEGUI::UVector2(CEGUI::UDim(0.35, 0),
                                             CEGUI::UDim(0.05+(4*(0.10)), 0)));
            slide->subscribeEvent(CEGUI::Slider::EventValueChanged, CEGUI::Event::Subscriber(&CommandSetting::m_slider_pushed, this));
            slide->setMaxValue(1);
            slide->setCurrentValue(Config::get()->getCommandConfig()->getMouseSensibility());
            text->addChild(slide);
        }
    }

    m_pane->hide();
    m_visible = false;
}
CommandSetting::~CommandSetting()
{
    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->removeChild(m_accept);
    CEGUI::WindowManager::getSingleton().destroyWindow(m_accept);
    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->removeChild(m_cancel);
    CEGUI::WindowManager::getSingleton().destroyWindow(m_cancel);
    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->removeChild(m_pane);
    CEGUI::WindowManager::getSingleton().destroyWindow(m_pane);
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
    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChild("OptionState")->setSize(CEGUI::USize(CEGUI::UDim(0.6,0), CEGUI::UDim(0.6, 0)));
    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChild("OptionState")->setPosition(CEGUI::UVector2(CEGUI::UDim(0.50-(CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChild("OptionState")->getSize().d_width.d_scale/2), 0),
                                         CEGUI::UDim(0.50-(CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChild("OptionState")->getSize().d_height.d_scale
                                                        /2), 0)));
}
void CommandSetting::exit()
{
    m_visible = false;
    m_pane->hide();
    m_cancel->hide();
    m_accept->hide();
    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChild("OptionState")->setSize(CEGUI::USize(CEGUI::UDim(0.3,0), CEGUI::UDim(0.3, 0)));
    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChild("OptionState")->setPosition(CEGUI::UVector2(CEGUI::UDim(0.50-(CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChild("OptionState")->getSize().d_width.d_scale/2), 0),
                                         CEGUI::UDim(0.50-(CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChild("OptionState")->getSize().d_height.d_scale
                                                        /2), 0)));
}
ret_code CommandSetting::work(const TimeDuration &elapsed)
{
    return CONTINUE;
}
bool CommandSetting::m_button_pushed(const CEGUI::EventArgs&)
{
    if (m_cancel->isPushed())
        m_visible = false;
    else
    {
        Config::get()->getCommandConfig()->saveConfig();
    }
    return true;
}
bool CommandSetting::m_box_pushed(const CEGUI::EventArgs& arg)
{
    OgreContextManager::get()->getInputManager()->addKeyboardListener(this);
    OgreContextManager::get()->getInputManager()->addMouseListener(this);
    m_box_selected = (CEGUI::Editbox*)((CEGUI::WindowEventArgs&)arg).window;
    CommandConfig::KeyAction::Key *key = (CommandConfig::KeyAction::Key*)m_box_selected->getUserData();
    if (key->type == CommandConfig::KeyAction::Key::Type::KEYBOARD)
        m_old_key = key->keyboard;
    else
        m_old_mouse = key->mouse;
    m_box_selected->setText("Appuyer sur une touche.");

    return true;
}
bool CommandSetting::m_checkbox_pushed(const CEGUI::EventArgs& arg)
{
    Config::get()->getCommandConfig()->setAxesInvers(((CEGUI::ToggleButton*)((CEGUI::WindowEventArgs&)arg).window)->isSelected());
    return true;
}

bool CommandSetting::m_slider_pushed(const CEGUI::EventArgs& arg)
{
    Config::get()->getCommandConfig()->setMouseSensibility(((CEGUI::Slider*)((CEGUI::WindowEventArgs&)arg).window)->getCurrentValue());
    return true;
}

bool CommandSetting::mouseMoved(const OIS::MouseEvent& arg)
{
    return true;
}
bool CommandSetting::mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
{
    if (!Config::get()->getCommandConfig()->eventExist(id, m_old_mouse, m_pane->getSelectedTabIndex()))
    {
        ((CommandConfig::KeyAction::Key*)m_box_selected->getUserData())->mouse = id;
        m_box_selected->setText(Config::get()->getCommandConfig()->toString(id));
    }
    else
        m_box_selected->setText(Config::get()->getCommandConfig()->toString(m_old_mouse));

    OgreContextManager::get()->getInputManager()->delMouseListener(this);
    OgreContextManager::get()->getInputManager()->delKeyboardListener(this);
    return true;
}
bool CommandSetting::mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
{
    return true;
}
bool CommandSetting::keyPressed(const OIS::KeyEvent& arg)
{
    std::cout << m_pane->getSelectedTabIndex() << std::endl;
    if (arg.key != OIS::KeyCode::KC_ESCAPE)
    {
        if (!Config::get()->getCommandConfig()->eventExist(arg.key, m_old_key, m_pane->getSelectedTabIndex()))
        {
            ((CommandConfig::KeyAction::Key*)m_box_selected->getUserData())->keyboard = arg.key;
            m_box_selected->setText(m_keyboard->getAsString(arg.key));
        }
        else
            m_box_selected->setText(m_keyboard->getAsString(m_old_key));
    }
    else
        m_box_selected->setText(m_keyboard->getAsString(m_old_key));

    OgreContextManager::get()->getInputManager()->delKeyboardListener(this);
    OgreContextManager::get()->getInputManager()->delMouseListener(this);
    return true;
}
bool CommandSetting::keyReleased(const OIS::KeyEvent& arg)
{
    return true;
}
