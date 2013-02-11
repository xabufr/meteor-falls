#include "OptionState.h"
#include "Engine/GraphicEngine/Ogre/OgreWindowInputManager.h"
#include "Engine/GraphicEngine/Ogre/ogrecontextmanager.h"
#include "Engine/GraphicEngine/Ogre/OgreApplication.h"
#include "../Option/SoundSetting.h"
#include "../Option/GraphicSetting.h"
#include "../Option/CommandSetting.h"

OptionState::OptionState(StateManager* mgr):State(mgr),
m_visible(true),
m_state_manager(mgr),
m_sous_state(nullptr)
{
    m_keyboard = OgreContextManager::get()->getInputManager()->getKeyboard();

    CEGUI::WindowManager &m_window_manager = CEGUI::WindowManager::getSingleton();
    m_window = (CEGUI::TabButton*)m_window_manager.createWindow("OgreTray/TabButtonPane", "OptionState");
    m_window->setSize(CEGUI::UVector2(CEGUI::UDim(0.30, 0), CEGUI::UDim(0.30, 0)));
    m_window->setPosition(CEGUI::UVector2(CEGUI::UDim(0.50-(m_window->getSize().d_x.d_scale/2), 0),
                                         CEGUI::UDim(0.50-(m_window->getSize().d_y.d_scale
                                                        /2), 0)));
    CEGUI::System::getSingleton().getGUISheet()->addChildWindow(m_window);

    m_graphics = (CEGUI::PushButton*)m_window_manager.createWindow("OgreTray/Button", "ButtonGraphics");
    m_graphics->setSize(CEGUI::UVector2(CEGUI::UDim(0.75, 0), CEGUI::UDim(0.20, 0)));
    m_graphics->setPosition(CEGUI::UVector2(CEGUI::UDim(0.5-(m_graphics->getSize().d_x.d_scale/2), 0),
                                         CEGUI::UDim(0.25-(m_graphics->getSize().d_y.d_scale
                                                        /2), 0)));
    m_graphics->setText("Graphisme");
    m_graphics->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&OptionState::m_choix_option, this));
    m_window->addChildWindow(m_graphics);

    m_sound = (CEGUI::PushButton*)m_window_manager.createWindow("OgreTray/Button", "ButtonSound");
    m_sound->setSize(CEGUI::UVector2(CEGUI::UDim(0.75, 0), CEGUI::UDim(0.20, 0)));
    m_sound->setPosition(CEGUI::UVector2(CEGUI::UDim(0.5-(m_sound->getSize().d_x.d_scale/2), 0),
                                         CEGUI::UDim(0.5-(m_sound->getSize().d_y.d_scale
                                                        /2), 0)));
    m_sound->setText("Son");
    m_sound->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&OptionState::m_choix_option, this));
    m_window->addChildWindow(m_sound);

    m_control = (CEGUI::PushButton*)m_window_manager.createWindow("OgreTray/Button", "ButtonControl");
    m_control->setSize(CEGUI::UVector2(CEGUI::UDim(0.75, 0), CEGUI::UDim(0.20, 0)));
    m_control->setPosition(CEGUI::UVector2(CEGUI::UDim(0.5-(m_control->getSize().d_x.d_scale/2), 0),
                                         CEGUI::UDim(0.75-(m_control->getSize().d_y.d_scale
                                                        /2), 0)));
    m_control->setText("Commandes");
    m_control->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&OptionState::m_choix_option, this));
    m_window->addChildWindow(m_control);

    m_sound_setting = new SoundSetting(m_state_manager);
    m_graphic_setting = new GraphicSetting(m_state_manager);
    m_command_setting = new CommandSetting(m_state_manager);
    m_window->hide();
}
OptionState::~OptionState()
{
    delete m_command_setting;
    delete m_sound_setting;
    delete m_graphic_setting;
}

bool OptionState::isVisible()
{
    return m_visible;
}

void OptionState::enter()
{
    m_window->show();
    m_visible = true;
}

void OptionState::exit()
{
    m_window->hide();
    m_visible = false;
}

ret_code OptionState::work(unsigned int)
{
    if (m_sous_state != nullptr && m_sous_state->isVisible())
        m_sous_state->work(0);
    else if (m_sous_state != nullptr)
    {
        m_sous_state->exit();
        m_sous_state = nullptr;
        m_sound->show();
        m_graphics->show();
        m_control->show();
    }

    return CONTINUE;
}

bool OptionState::m_choix_option(const CEGUI::EventArgs&)
{
    m_sound->hide();
    m_graphics->hide();
    m_control->hide();

    if (m_sound->isPushed())
        m_sous_state = m_sound_setting;
    else if (m_graphics->isPushed())
        m_sous_state = m_graphic_setting;
    else if (m_control->isPushed())
        m_sous_state = m_command_setting;

    m_sous_state->enter();

    return true;
}
