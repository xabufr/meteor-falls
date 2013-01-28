#include "TeamState.h"
#include "Engine/GraphicEngine/Ogre/OgreWindowInputManager.h"
#include "Engine/GraphicEngine/Ogre/ogrecontextmanager.h"
#include "Engine/GraphicEngine/Ogre/OgreApplication.h"
#include "Engine/NetworkEngine/clientnetworkengine.h"
#include "Engine/GameEngine/Factions/Equipe.h"
#include <string>

TeamState::TeamState(StateManager* mgr, GameEngine* engine):State(mgr),
m_visible(true),
m_game_engine(engine)
{
    m_keyboard = OgreContextManager::get()->getInputManager()->getKeyboard();

    CEGUI::WindowManager &m_window_manager = CEGUI::WindowManager::getSingleton();
    m_window = (CEGUI::TabButton*)m_window_manager.createWindow("OgreTray/TabButtonPane", "TeamState");
    m_window->setSize(CEGUI::UVector2(CEGUI::UDim(0.30, 0), CEGUI::UDim(0.20, 0)));
    m_window->setPosition(CEGUI::UVector2(CEGUI::UDim(0.50-(m_window->getSize().d_x.d_scale/2), 0),
                                         CEGUI::UDim(0.50-(m_window->getSize().d_y.d_scale
                                                        /2), 0)));
    CEGUI::System::getSingleton().getGUISheet()->addChildWindow(m_window);

    m_rts = (CEGUI::PushButton*)m_window_manager.createWindow("OgreTray/Button", "ButtonRTS");
    m_rts->setSize(CEGUI::UVector2(CEGUI::UDim(0.20, 0), CEGUI::UDim(0.20, 0)));
    m_rts->setPosition(CEGUI::UVector2(CEGUI::UDim(0.25-(m_rts->getSize().d_x.d_scale/2), 0),
                                         CEGUI::UDim(0.50-(m_rts->getSize().d_y.d_scale
                                                        /2), 0)));
    m_rts->setText("RTS");
    m_rts->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&TeamState::m_choix_mode, this));
    m_window->addChildWindow(m_rts);
    m_rpg = (CEGUI::PushButton*)m_window_manager.createWindow("OgreTray/Button", "ButtonRPG");
    m_rpg->setSize(CEGUI::UVector2(CEGUI::UDim(0.20, 0), CEGUI::UDim(0.20, 0)));
    m_rpg->setPosition(CEGUI::UVector2(CEGUI::UDim(0.75-(m_rpg->getSize().d_x.d_scale/2), 0),
                                         CEGUI::UDim(0.50-(m_rpg->getSize().d_y.d_scale
                                                        /2), 0)));
    m_rpg->setText("RPG");
    m_rpg->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&TeamState::m_choix_mode, this));
    m_window->addChildWindow(m_rpg);

    m_chat = (CEGUI::Listbox*)(m_window_manager.createWindow("OgreTray/Listbox", "Chat"));
    m_chat->setSize(CEGUI::UVector2(CEGUI::UDim(0.25, 0), CEGUI::UDim(0.30, 0)));

    CEGUI::System::getSingleton().getGUISheet()->addChildWindow(m_chat);

    m_edit = (CEGUI::Editbox*)m_window_manager.createWindow("OgreTray/Editbox", "Champ");
    m_edit->setSize(CEGUI::UVector2(CEGUI::UDim(0.25, 0), CEGUI::UDim(0.05, 0)));
    m_edit->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 0),
                                         CEGUI::UDim((1-m_edit->getSize().d_y.d_scale), 0)));
    m_edit->activate();
    m_chat->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 0),
                                         CEGUI::UDim((1-m_chat->getSize().d_y.d_scale-m_edit->getSize().d_y.d_scale), 0)));
    m_edit->subscribeEvent(CEGUI::Editbox::EventKeyDown, CEGUI::Event::Subscriber(&TeamState::m_send_message, this));
    CEGUI::System::getSingleton().getGUISheet()->addChildWindow(m_edit);
    m_window->hide();
}
bool TeamState::m_send_message(const CEGUI::EventArgs&)
{
    if (m_keyboard->isKeyDown(OIS::KeyCode::KC_RETURN))
    {
        ClientNetworkEngine *net = (ClientNetworkEngine*)m_game_engine->getManager()->getNetwork();
        net->sendChatMessage(std::string(m_edit->getText().c_str()), EngineMessageKey::TEAM_RANGE);
        m_edit->setText("");
    }
    return true;
}
void TeamState::setMessage(const CEGUI::String message)
{
    CEGUI::ListboxTextItem *item = new CEGUI::ListboxTextItem(message);
    m_chat->addItem(item);
}
bool TeamState::m_choix_mode(const CEGUI::EventArgs&)
{
    ClientNetworkEngine *net = (ClientNetworkEngine*)m_game_engine->getManager()->getNetwork();
    net->trySelectGameplay((m_rts->isPushed())?EngineMessageKey::RTS_GAMEPLAY:EngineMessageKey::RPG_GAMEPLAY);
    m_game_engine->getCurrentJoueur()->setTypeGamplay((m_rts->isPushed())?Joueur::TypeGameplay::RTS:Joueur::TypeGameplay::RPG);
    return true;
}
TeamState::~TeamState()
{
    delete m_window;
    delete m_rts;
    delete m_rpg;
    delete m_chat;
    delete m_edit;
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
    if (m_game_engine->getCurrentJoueur()->equipe->getRTS() != nullptr)
            m_rts->disable();
    return CONTINUE;
}
