#include "LoginState.h"
#include "State/Console.h"
#include "Engine/GraphicEngine/Ogre/OgreWindowInputManager.h"
#include "Engine/GraphicEngine/Ogre/ogrecontextmanager.h"
#include "Engine/GraphicEngine/Ogre/OgreApplication.h"
#include "Engine/NetworkEngine/ClientLogin.h"
#include "State/Game/GameState.h"

 LoginState::~LoginState()
{

}

 LoginState::LoginState(StateManager *mgr, Joueur **j) : State(mgr),
 m_visible(false),
 m_player(j)
{
    m_mouse = OgreContextManager::get()->getInputManager()->getMouse();
    m_keyboard = OgreContextManager::get()->getInputManager()->getKeyboard();

    CEGUI::WindowManager &m_window_mgr = CEGUI::WindowManager::getSingleton();

    m_sheet = m_window_mgr.createWindow("OgreTray/TabButtonPane", "FenetreMenu");
    m_sheet->setSize(CEGUI::UVector2(CEGUI::UDim(0.30, 0), CEGUI::UDim(0.50, 0)));
    m_sheet->setPosition(CEGUI::UVector2(CEGUI::UDim(0.50-(m_sheet->getSize().d_x.d_scale/2), 0), CEGUI::UDim(0.30, 0)));

    m_playLan = m_window_mgr.createWindow("OgreTray/Button", "BoutonJouerLAN");
    m_playLan->setText("Jouer (LAN)");
    m_playLan->setSize(CEGUI::UVector2(CEGUI::UDim(0.80, 0), CEGUI::UDim(0.10, 0)));
    m_playLan->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&LoginState::m_connection_lan, this));
    m_sheet->addChildWindow(m_playLan);

    m_playOnline = m_window_mgr.createWindow("OgreTray/Button", "BoutonJouer");
    m_playOnline->setText("Jouer (Online)");
    m_playOnline->setSize(CEGUI::UVector2(CEGUI::UDim(0.80, 0), CEGUI::UDim(0.10, 0)));
    m_playOnline->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&LoginState::m_connection, this));
    m_sheet->addChildWindow(m_playOnline);

    m_playLan->setPosition(CEGUI::UVector2(CEGUI::UDim(0.50-(m_playLan->getSize().d_x.d_scale/2), 0),
                                         CEGUI::UDim(0+(m_sheet->getSize().d_y.d_scale/m_sheet->getChildCount()), 0)));
    m_playOnline->setPosition(CEGUI::UVector2(CEGUI::UDim(0.50-(m_playOnline->getSize().d_x.d_scale/2), 0),
                                           CEGUI::UDim(0.12+(m_sheet->getSize().d_y.d_scale/m_sheet->getChildCount()), 0)));

    CEGUI::System::getSingleton().getGUISheet()->addChildWindow(m_sheet);
    m_sheet->hide();
}
bool LoginState::m_connection(const CEGUI::EventArgs &)
{
    CEGUI::WindowManager &m_window_mgr = CEGUI::WindowManager::getSingleton();

    m_sheet->removeChildWindow("BoutonJouerLAN");
    m_sheet->removeChildWindow("BoutonJouer");

    m_loginText = m_window_mgr.createWindow("OgreTray/StaticText", "StaticTextLogin");
    m_loginText->setText("Login:");
    m_loginText->setSize(CEGUI::UVector2(CEGUI::UDim(0.80, 0), CEGUI::UDim(0.10, 0)));
    m_loginText->setProperty("FrameEnabled", "false");
    m_loginText->setProperty("BackgroundEnabled", "false");
    m_loginText->setProperty("VertFormatting", "TopAligned");
    m_sheet->addChildWindow(m_loginText);

    m_login = m_window_mgr.createWindow("OgreTray/Editbox", "EditBoxLogin");
    m_login->setSize(CEGUI::UVector2(CEGUI::UDim(0.80, 0), CEGUI::UDim(0.10, 0)));
    m_sheet->addChildWindow(m_login);

    m_passwdText = m_window_mgr.createWindow("OgreTray/StaticText", "StaticTextPassword");
    m_passwdText->setText("Password:");
    m_passwdText->setSize(CEGUI::UVector2(CEGUI::UDim(0.80, 0), CEGUI::UDim(0.10, 0)));
    m_passwdText->setProperty("FrameEnabled", "false");
    m_passwdText->setProperty("BackgroundEnabled", "false");
    m_passwdText->setProperty("VertFormatting", "TopAligned");
    m_sheet->addChildWindow(m_passwdText);

    m_passwd = m_window_mgr.createWindow("OgreTray/Editbox", "EditBoxPassword");
    m_passwd->setSize(CEGUI::UVector2(CEGUI::UDim(0.80, 0), CEGUI::UDim(0.10, 0)));
    m_passwd->setProperty("MaskText", "True");
    m_sheet->addChildWindow(m_passwd);

    m_connect = m_window_mgr.createWindow("OgreTray/Button", "BoutonConnect");
    m_connect->setText("Connexion");
    m_connect->setSize(CEGUI::UVector2(CEGUI::UDim(0.80, 0), CEGUI::UDim(0.10, 0)));
    m_connect->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&LoginState::send, this));
    m_sheet->addChildWindow(m_connect);

    m_message = m_window_mgr.createWindow("OgreTray/StaticText", "StaticText");

    m_loginText->setPosition(CEGUI::UVector2(CEGUI::UDim(0.50-(m_loginText->getSize().d_x.d_scale/2), 0),
                                         CEGUI::UDim(0+(m_sheet->getSize().d_y.d_scale/m_sheet->getChildCount()), 0)));
    m_login->setPosition(CEGUI::UVector2(CEGUI::UDim(0.50-(m_login->getSize().d_x.d_scale/2), 0),
                                         CEGUI::UDim(m_loginText->getPosition().d_y.d_scale+(m_sheet->getSize().d_y.d_scale/m_sheet->getChildCount()), 0)));
    m_passwdText->setPosition(CEGUI::UVector2(CEGUI::UDim(0.50-(m_passwdText->getSize().d_x.d_scale/2), 0),
                                         CEGUI::UDim(m_login->getPosition().d_y.d_scale+(m_sheet->getSize().d_y.d_scale/m_sheet->getChildCount()), 0)));
    m_passwd->setPosition(CEGUI::UVector2(CEGUI::UDim(0.50-(m_passwd->getSize().d_x.d_scale/2), 0),
                                         CEGUI::UDim(m_passwdText->getPosition().d_y.d_scale+(m_sheet->getSize().d_y.d_scale/m_sheet->getChildCount()), 0)));
    m_connect->setPosition(CEGUI::UVector2(CEGUI::UDim(0.50-(m_connect->getSize().d_x.d_scale/2), 0),
                                         CEGUI::UDim(m_passwd->getPosition().d_y.d_scale+(m_sheet->getSize().d_y.d_scale/m_sheet->getChildCount()), 0)));

    return true;
}
bool LoginState::m_connection_lan(const CEGUI::EventArgs&)
{
	delete *m_player;
    *m_player = new JoueurLan();
    (*m_player)->setNom("Test");
    this->exit();
    return true;
}
ret_code LoginState::work(unsigned int time)
{
    if (m_keyboard->isKeyDown(OIS::KC_ESCAPE))
        return EXIT_PROGRAM;
    else if (m_keyboard->isKeyDown(OIS::KC_J))
        m_state_manager->addState(new GameState(m_state_manager, EngineManager::Type::CLIENT_LAN));
    return CONTINUE;
}
void LoginState::m_state_element(const bool actif)
{
    m_login->setEnabled(actif);
    m_passwd->setEnabled(actif);
    m_connect->setEnabled(actif);
}
bool LoginState::send(const CEGUI::EventArgs &)
{
    m_state_element(false);

    m_message->setSize(CEGUI::UVector2(CEGUI::UDim(0.80, 0), CEGUI::UDim(0.10, 0)));
    m_message->setProperty("FrameEnabled", "false");
    m_message->setProperty("BackgroundEnabled", "false");
    m_message->setProperty("VertFormatting", "TopAligned");
    m_sheet->addChildWindow(m_message);

    m_message->setPosition(CEGUI::UVector2(CEGUI::UDim(0.50-(m_message->getSize().d_x.d_scale/2), 0),
                                         CEGUI::UDim(m_connect->getPosition().d_y.d_scale+(m_sheet->getSize().d_y.d_scale/m_sheet->getChildCount()), 0)));

    if (std::string(m_login->getText().c_str()) == "" || std::string(m_passwd->getText().c_str()) == "")
    {
       m_message->setText("Veuillez saisir un login et un password.");
       return false;
    }

    m_message->setText("Connexion en cours...");
    ClientLogin *log = new ClientLogin(6050, std::string(m_login->getText().c_str()), std::string(m_passwd->getText().c_str()));

    if (log->isLogin())
    {
        m_message->setText((CEGUI::utf8*)("Connection établie."));
        *m_player = new JoueurWan();
        (*m_player)->setNom(std::string(m_login->getText().c_str()));
        (*m_player)->setNom(log->getPlayer()->num_session);
        this->exit();
    }
    else
        m_message->setText((CEGUI::utf8*)("Login ou mot de passe erroné."));

    delete log;

    m_state_element(true);

    return true;
}
bool LoginState::isVisible()
{
    return m_visible;
}
void LoginState::exit()
{
    m_sheet->hide();
    m_visible = false;
}
void LoginState::enter()
{
    m_sheet->show();
    m_visible = true;
}
