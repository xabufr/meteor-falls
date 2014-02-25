#include "Chat.h"
#include "Engine/GraphicEngine/Ogre/OgreWindowInputManager.h"
#include "Engine/GraphicEngine/Ogre/ogrecontextmanager.h"
#include "Engine/GraphicEngine/Ogre/OgreApplication.h"
#include "Engine/NetworkEngine/clientnetworkengine.h"
#include "../../EngineManager/EngineManager.h"
#include "../../EngineMessage/EngineMessage.h"
#include "../GameEngine.h"
#include "../../../Utils/Configuration/Config.h"
#include "../Joueur/Joueur.h"
#include <CEGUI/CEGUI.h>


Chat::Chat(GameEngine* game):m_game_engine(game)
{
    m_keyboard = OgreContextManager::get()->getInputManager()->getKeyboard();

    CEGUI::WindowManager &m_show_message_manager = CEGUI::WindowManager::getSingleton();
    m_show_message = (CEGUI::Listbox*)(m_show_message_manager.createWindow("OgreTray/Listbox", "Chat"));
    m_show_message->setSize(CEGUI::USize(CEGUI::UDim(0.25, 0), CEGUI::UDim(0.30, 0)));
    m_show_message->hide();

    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(m_show_message);

    m_message = (CEGUI::Editbox*)m_show_message_manager.createWindow("OgreTray/Editbox", "Champ");
    m_message->setSize(CEGUI::USize(CEGUI::UDim(0.25, 0), CEGUI::UDim(0.05, 0)));
    m_message->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 0),
                                         CEGUI::UDim((1-m_message->getSize().d_height.d_scale), 0)));
    m_message->activate();
    m_show_message->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 0),
                                         CEGUI::UDim((1-m_show_message->getSize().d_height.d_scale-m_message->getSize().d_height.d_scale), 0)));
    m_message->hide();
    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(m_message);
}

Chat::~Chat()
{
    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->removeChild(m_show_message);
    CEGUI::WindowManager::getSingleton().destroyWindow(m_show_message);
    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->removeChild(m_message);
    CEGUI::WindowManager::getSingleton().destroyWindow(m_message);
}

void Chat::show()
{
    OgreContextManager::get()->getInputManager()->addKeyboardListener(this);
    OgreContextManager::get()->getInputManager()->addMouseListener(this);
    m_show_message->show();
    m_message->show();
}

void Chat::hide()
{
    OgreContextManager::get()->getInputManager()->delKeyboardListener(this);
    OgreContextManager::get()->getInputManager()->delMouseListener(this);
    m_show_message->hide();
    m_message->hide();
}

void Chat::addMessage(std::string message, Joueur* j)
{
    CEGUI::ListboxTextItem *item = new CEGUI::ListboxTextItem((CEGUI::utf8*)message.c_str());
    item->setUserData(j);
    m_show_message->addItem(item);
}

bool Chat::isVisible() const
{
    return m_visible;
}

void Chat::m_send_message(const CEGUI::String& s)
{
    ClientNetworkEngine *net = (ClientNetworkEngine*)m_game_engine->getManager()->getNetwork();
    net->sendChatMessage(std::string(s.c_str()), mf::EngineMessageKey::TEAM_RANGE);
    m_message->setText("");
}

bool Chat::mouseMoved(const OIS::MouseEvent& arg)
{
    return true;
}

bool Chat::mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
{
    return true;
}

bool Chat::mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
{
    return true;
}

bool Chat::keyPressed(const OIS::KeyEvent& arg)
{
    if (m_keyboard->isKeyDown(OIS::KeyCode::KC_RETURN))
        m_send_message(m_message->getText());
    return true;
}

bool Chat::keyReleased(const OIS::KeyEvent& arg)
{
    return true;
}


