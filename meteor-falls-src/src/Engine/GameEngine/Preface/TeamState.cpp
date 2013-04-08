#include "TeamState.h"
#include "Engine/GraphicEngine/Ogre/OgreWindowInputManager.h"
#include "Engine/GraphicEngine/Ogre/ogrecontextmanager.h"
#include "Engine/GraphicEngine/Ogre/OgreApplication.h"
#include "Engine/NetworkEngine/clientnetworkengine.h"
#include "Engine/GameEngine/Factions/Equipe.h"
#include "../ClientGameEngine.h"
#include "../Interface/Chat.h"
#include "../../EngineManager/EngineManager.h"
#include "../../EngineMessage/EngineMessage.h"
#include <string>
#include <CEGUI.h>

TeamState::TeamState(StateManager* mgr, ClientGameEngine* engine):State(mgr),
m_visible(true),
m_game_engine(engine)
{
    m_keyboard = OgreContextManager::get()->getInputManager()->getKeyboard();

    CEGUI::WindowManager &m_window_manager = CEGUI::WindowManager::getSingleton();
    m_window = (CEGUI::TabButton*)m_window_manager.createWindow("TaharezLook/FrameWindow", "TeamState");
    m_window->setSize(CEGUI::UVector2(CEGUI::UDim(0.30, 0), CEGUI::UDim(0.20, 0)));
    m_window->setPosition(CEGUI::UVector2(CEGUI::UDim(0.50-(m_window->getSize().d_x.d_scale/2), 0),
                                         CEGUI::UDim(0.50-(m_window->getSize().d_y.d_scale
                                                        /2), 0)));
	CEGUI::FrameWindow* frame = (CEGUI::FrameWindow*)m_window;
	frame->setSizingEnabled(false);
	frame->setCloseButtonEnabled(false);
	frame->setDragMovingEnabled(false);
    CEGUI::System::getSingleton().getGUISheet()->addChildWindow(m_window);

    m_rts = (CEGUI::PushButton*)m_window_manager.createWindow("TaharezLook/Button", "ButtonRTS");
    m_rts->setSize(CEGUI::UVector2(CEGUI::UDim(0.20, 0), CEGUI::UDim(0.20, 0)));
    m_rts->setPosition(CEGUI::UVector2(CEGUI::UDim(0.25-(m_rts->getSize().d_x.d_scale/2), 0),
                                         CEGUI::UDim(0.50-(m_rts->getSize().d_y.d_scale
                                                        /2), 0)));
    m_rts->setText("RTS");
    m_rts->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&TeamState::m_choix_mode, this));
    m_window->addChildWindow(m_rts);
    m_rpg = (CEGUI::PushButton*)m_window_manager.createWindow("TaharezLook/Button", "ButtonRPG");
    m_rpg->setSize(CEGUI::UVector2(CEGUI::UDim(0.20, 0), CEGUI::UDim(0.20, 0)));
    m_rpg->setPosition(CEGUI::UVector2(CEGUI::UDim(0.75-(m_rpg->getSize().d_x.d_scale/2), 0),
                                         CEGUI::UDim(0.50-(m_rpg->getSize().d_y.d_scale
                                                        /2), 0)));
    m_rpg->setText("RPG");
    m_rpg->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&TeamState::m_choix_mode, this));
    m_window->addChildWindow(m_rpg);

    m_window->hide();
}
bool TeamState::m_choix_mode(const CEGUI::EventArgs&)
{
    ClientNetworkEngine *net = (ClientNetworkEngine*)m_game_engine->getManager()->getNetwork();
    net->trySelectGameplay((m_rts->isPushed())?EngineMessageKey::RTS_GAMEPLAY:EngineMessageKey::RPG_GAMEPLAY);
    return true;
}
TeamState::~TeamState()
{
	CEGUI::System::getSingleton().getGUISheet()->removeChildWindow(m_window);
	CEGUI::System::getSingleton().getGUISheet()->removeChildWindow(m_rts);
	CEGUI::System::getSingleton().getGUISheet()->removeChildWindow(m_rpg);
	CEGUI::WindowManager::getSingleton().destroyWindow(m_window);
	CEGUI::WindowManager::getSingleton().destroyWindow(m_rts);
	CEGUI::WindowManager::getSingleton().destroyWindow(m_rpg);
}
bool TeamState::isVisible()
{
    return m_visible;
}
void TeamState::enter()
{
    m_game_engine->getChat()->show();
    m_window->show();
    m_visible = true;
}
void TeamState::exit()
{
    m_game_engine->getChat()->hide();
    m_window->hide();
    m_visible = false;
}
ret_code TeamState::work(unsigned int time)
{
    if (m_game_engine->getCurrentJoueur()->equipe()->getRTS() != nullptr)
		m_rts->disable();
	else
		m_rts->enable();
    return CONTINUE;
}
