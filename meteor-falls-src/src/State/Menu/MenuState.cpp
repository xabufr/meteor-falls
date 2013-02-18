#include <string>
#include "MenuState.h"
#include "State/Console.h"
#include "State/Command/Connect.h"
#include "State/Command/MenuState/ExitMenuState.h"
#include "State/Command/MenuState/LoginMenuState.h"
#include "Engine/GraphicEngine/Ogre/ogrecontextmanager.h"
#include "Engine/GraphicEngine/Ogre/OgreApplication.h"
#include "Engine/GraphicEngine/Ogre/OgreWindowInputManager.h"
#include "../Game/GameState.h"
#include "Engine/GraphicEngine/Ogre/GetMeshInformation.h"
#include "precompiled/bind.h"
#include "../../Engine/SoundEngine/Playlist.h"

MenuState::MenuState(StateManager* mng):
    State(mng), m_visible(false), m_escape(true)
{
    m_transitionning=false;
    m_currentSelected = 0;
    m_mouse = OgreContextManager::get()->getInputManager()->getMouse();
    m_keyboard = OgreContextManager::get()->getInputManager()->getKeyboard();

    OgreContextManager::get()->getOgreApplication()->LoadRessources("resources.cfg");

    m_scene_mgr = OgreContextManager::get()->getOgreApplication()->getRoot()->createSceneManager("DefaultSceneManager", "Menu");

    m_scene_mgr->setAmbientLight(Ogre::ColourValue(0.0, 0.0, 0.0));
    m_scene_mgr->setSkyBox(true, "Space/Skybox", 100, true);

    m_camera = m_scene_mgr->createCamera("MenuCam");

    m_camera->setNearClipDistance(0.1);
    m_camera->setPosition(0, 0, 10);
    m_camera->lookAt(Ogre::Vector3(0, 0, 0));

    Ogre::Viewport *vp = OgreContextManager::get()->getOgreApplication()->getWindow()->addViewport(m_camera);
    vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
    m_camera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

    m_scene_mgr->setShadowTechnique(Ogre::ShadowTechnique::SHADOWTYPE_TEXTURE_MODULATIVE);

    Ogre::Light* light = m_scene_mgr->createLight();
    light->setType(Ogre::Light::LightTypes::LT_POINT);
    light->setDiffuseColour(1,1,1);
    light->setSpecularColour(1,1,1);
    light->setAttenuation(3000, 1, 0.0007, 0);

    m_eTerre = m_scene_mgr->createEntity("Terre", "Sphere.mesh");
    m_nodeTerre = m_scene_mgr->getRootSceneNode()->createChildSceneNode("NodeTerre", Ogre::Vector3(2.5, 0, -15), Ogre::Quaternion::IDENTITY);
    m_nodeTerre->attachObject(m_eTerre);
    m_nodeTerre->roll(Ogre::Degree(-23.4388));
    m_eTerre->setCastShadows(true);
    m_eTerre->setMaterialName("Terre");
    m_nodeTerre->scale(4,4,4);
    m_camera->setAutoTracking(true, m_nodeTerre, Ogre::Vector3(-1.0,0,0));

    terreAtmosphere = m_scene_mgr->getRootSceneNode()->createChildSceneNode("atmosphere",  Ogre::Vector3(2.5, 0, -15), Ogre::Quaternion::IDENTITY);
    m_eAtmoTerre = m_scene_mgr->createEntity("Terre_atmosphere", "Circle.mesh");
    m_eAtmoTerre->setMaterialName("Terre/Atmosphere");
    terreAtmosphere->attachObject(m_eAtmoTerre);
    terreAtmosphere->scale(4.05, 4.05, 4.05);
    terreAtmosphere->pitch(Ogre::Degree(180+90));
    terreAtmosphere->yaw(Ogre::Degree(180+90));
    terreAtmosphere->roll(Ogre::Degree(180+90));

    m_eLune = m_scene_mgr->createEntity("Lune", "Sphere.mesh");
    m_nodeLune = m_scene_mgr->getRootSceneNode()->createChildSceneNode("NodeLune", Ogre::Vector3(-5.f, 2.f, -14.5), Ogre::Quaternion::IDENTITY);
    m_nodeLune->attachObject(m_eLune);
    m_eLune->setCastShadows(true);
    m_eLune->setMaterialName("lune");

    m_eSoleil = m_scene_mgr->createEntity("Soleil", "Sphere.mesh");
    m_nodeSoleil = m_scene_mgr->getRootSceneNode()->createChildSceneNode("NodeSoleil", Ogre::Vector3(-12, 5, -17), Ogre::Quaternion::IDENTITY);
    m_nodeSoleil->attachObject(m_eSoleil);
    m_eSoleil->setCastShadows(true);
    m_eSoleil->setMaterialName("soleil");
    m_nodeSoleil->attachObject(light);

    CEGUI::Imageset::setDefaultResourceGroup("Imagesets");
    CEGUI::Font::setDefaultResourceGroup("Fonts");
    CEGUI::Scheme::setDefaultResourceGroup("Schemes");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
    CEGUI::WindowManager::setDefaultResourceGroup("Layouts");

    CEGUI::SchemeManager::getSingleton().create("Interface.scheme");
    CEGUI::SchemeManager::getSingleton().create("OgreTray.scheme");
    CEGUI::System::getSingleton().setDefaultMouseCursor("Interface", "MouseArrow");
    CEGUI::MouseCursor::getSingleton().setImage( CEGUI::System::getSingleton().getDefaultMouseCursor());

    CEGUI::WindowManager &m_window_mgr = CEGUI::WindowManager::getSingleton();

    m_sheet = m_window_mgr.createWindow("DefaultWindow", "Fenetre");

    m_state = m_window_mgr.createWindow("OgreTray/StaticText", "TextState");
    m_state->setSize(CEGUI::UVector2(CEGUI::UDim(0.10, 0), CEGUI::UDim(0.10, 0)));
    m_state->setPosition(CEGUI::UVector2(CEGUI::UDim(0.50-(m_state->getSize().d_x.d_scale/2), 0), CEGUI::UDim(0, 0)));
    m_state->setProperty("HorzFormatting", "WordWrapCentred");
    m_sheet->addChildWindow(m_state);
    m_state->hide();

    CEGUI::System::getSingleton().setGUISheet(m_sheet);

    m_scene_mgr->getRootSceneNode()->setVisible(false);
    m_sceneQuery = m_scene_mgr->createRayQuery(Ogre::Ray());

    m_player = new Joueur();

    m_server_list = new ServerList(ServerList::Type::LAN, m_state_manager, &m_player);
    m_layout_state = new LayoutRTS(m_state_manager);
    m_credit_state = new CreditState(m_state_manager);
    m_login_state = new LoginState(m_state_manager, &m_player);
    m_option_state = new OptionState(m_state_manager, this);

    m_sousState = m_login_state;


    Playlist::loadFile("data/playlist.xml");
}
MenuState::~MenuState()
{
    delete m_background;
    delete m_sousState;
    delete m_credit_state;
    delete m_layout_state;
    delete m_server_list;
    delete m_login_state;
    delete m_player;
    delete m_state;
    delete m_option_state;
}
bool MenuState::quit(const CEGUI::EventArgs &)
{
    OgreContextManager::get()->getOgreApplication()->getWindow()->destroy();
    return true;
}
bool MenuState::startGame()
{
    m_state_manager->addState(new GameState(m_state_manager, EngineManager::Type::CLIENT_LAN, "", "", m_player));
    return true;
}
bool MenuState::showLanServer()
{
    m_state->show();
    m_sousState = m_server_list;
    m_sousState->enter();

    return true;
}
bool MenuState::showCredit()
{
    m_state->hide();
    m_sousState = m_layout_state;
    m_sousState->enter();

    return true;
}
bool MenuState::showOption()
{
    m_state->hide();
    m_sousState = m_option_state;
    m_sousState->enter();
}
bool MenuState::m_hide_sous_state()
{
	if(m_sousState!=0)
	    m_sousState->exit();
    return true;
}
void MenuState::enter()
{
    OgreContextManager::get()->getInputManager()->addKeyboardListener(Console::get());
    OgreContextManager::get()->getInputManager()->addMouseListener(Console::get());

    //initialisation des commandes
    Console::get()->clearCommands();
    Console::get()->addCommand(new ExitMenuState());
    Console::get()->addCommand(new LoginMenuState(m_sousState, m_state_manager));
    Console::get()->addCommand(new Connect());

    if(m_sousState)
        m_sousState->enter();
    m_scene_mgr->getRootSceneNode()->setVisible(true);
    Playlist::get()->select_group("menu");
    m_visible = true;

}
void MenuState::exit()
{
    if(m_sousState)
        m_sousState->exit();
    if(m_state)
        m_state->hide();
    m_scene_mgr->getRootSceneNode()->setVisible(false);
//    OgreContextManager::get()->getOgreApplication()->getWindow()->removeAllViewports();
//    OgreContextManager::get()->getOgreApplication()->getRoot()->destroySceneManager(m_scene_mgr);
    m_visible = false;
}
ret_code MenuState::work(unsigned int time)
{
    Ogre::Vector3      cam_to_obj = terreAtmosphere->getPosition() - m_camera->getPosition();
    Ogre::Quaternion   quaternion_yaw = Ogre::Vector3( cam_to_obj.x, 0.0, cam_to_obj.z ).getRotationTo( cam_to_obj );
    Ogre::Quaternion   quaternion_pitch = Ogre::Vector3( 0.0, 0.0, 1.0 ).getRotationTo( Ogre::Vector3( cam_to_obj.x, 0.0, cam_to_obj.z ));
    Ogre::Vector3      newOrientation = m_camera->getDerivedUp( ).crossProduct( cam_to_obj );
    Ogre::Quaternion   rollRotation = ( Ogre::Vector3( 1.0, 0.0, 0.0 ) ).getRotationTo( ( quaternion_yaw * quaternion_pitch ).Inverse( ) * newOrientation );
    terreAtmosphere->setOrientation( quaternion_yaw * quaternion_pitch * rollRotation );
    terreAtmosphere->pitch(Ogre::Degree(180+90));
    terreAtmosphere->yaw(Ogre::Degree(90));
    terreAtmosphere->roll(Ogre::Degree(90));

    m_nodeTerre->yaw(Ogre::Degree(6.f*float(time)*0.001));
    m_nodeLune->yaw(Ogre::Degree(6.f*float(time)*0.001));

    if (m_sousState==0 || !m_sousState->isVisible())
    {
        /*Piking*/
        if (!m_player->getNom().empty())
        {
            m_state->setText(m_player->getNom());
            m_state->setSize(CEGUI::UVector2(CEGUI::UDim((m_state->getText().size()*0.05), 0), CEGUI::UDim(0.10, 0)));
            m_state->setPosition(CEGUI::UVector2(CEGUI::UDim(0.50-(m_state->getSize().d_x.d_scale/2), 0), CEGUI::UDim(0, 0)));
        }
        m_state->show();
        CEGUI::Point mousePos = CEGUI::MouseCursor::getSingleton().getPosition();
        unsigned int width = OgreContextManager::get()->getOgreApplication()->getWindow()->getWidth(),
                     height = OgreContextManager::get()->getOgreApplication()->getWindow()->getHeight();
        Ogre::Ray pickingRay = m_camera->getCameraToViewportRay(mousePos.d_x/float(width), mousePos.d_y/float(height));

        Ogre::Entity *selected = findFirstPicking(pickingRay, m_sceneQuery);

        bool click = m_mouse->getMouseState().buttonDown(OIS::MouseButtonID::MB_Left);
        if(!m_transitionning)
        {
			if(m_keyboard->isKeyDown(OIS::KC_ESCAPE))
				return ret_code::EXIT_PROGRAM;
            if(selected==m_eTerre||selected==m_eAtmoTerre)
            {
                if(click)
                {
                    m_transitionning=true;
                    m_timerTranslation.restart();
                    m_transitionParams.from=m_camera->getPosition();
                    m_transitionParams.to = m_nodeTerre->getPosition() + Ogre::Vector3(-7,1,7);
                    m_transitionParams.duration=1.0;
                    m_transitionParams.function = boost::bind(&MenuState::showLanServer, this);
                }
            }
            else if(selected==m_eSoleil)
            {
                if(click)
                {
                    m_transitionning=true;
                    m_timerTranslation.restart();
                    m_transitionParams.from=m_camera->getPosition();
                    m_transitionParams.to = m_nodeSoleil->getPosition()+Ogre::Vector3(-0.1, 1.5, -0.1);
                    m_transitionParams.duration=1.0;
                    m_transitionParams.function = boost::bind(&MenuState::showCredit, this);
                }
            }
            else if(selected==m_eLune)
            {
                if(click)
                {
                    m_transitionning=true;
                    m_timerTranslation.restart();
                    m_transitionParams.from=m_camera->getPosition();
                    m_transitionParams.to = m_nodeLune->getPosition()+Ogre::Vector3(-0.1, 1.5, -0.1);
                    m_transitionParams.duration=1.0;
                    m_transitionParams.function = boost::bind(&MenuState::showOption, this);
                }
            }
            else
            {
                if(click)
                {
                    m_transitionning=true;
                    m_timerTranslation.restart();
                    m_transitionParams.from=m_camera->getPosition();
                    m_transitionParams.to = Ogre::Vector3(0,0,10);
                    m_transitionParams.duration=1.0;
                    m_transitionParams.function = boost::bind(&MenuState::m_hide_sous_state, this);
                }
            }
        }
        else
        {
            Ogre::Vector3 pos = m_transitionParams.to*
                                (m_timerTranslation.getElapsedTime().asSeconds()/
                                 m_transitionParams.duration) +
                                 m_transitionParams.from*(1.f-(m_timerTranslation.getElapsedTime().asSeconds()/
                                 m_transitionParams.duration));

            m_camera->setPosition(pos);
            if(m_timerTranslation.getElapsedTime().asSeconds()>m_transitionParams.duration)
            {
                m_camera->setPosition(m_transitionParams.to);
                m_transitionning=false;
                m_transitionParams.function();
            }
        }
    }
    else
    {
        m_sousState->work(time);
		if(m_keyboard->isKeyDown(OIS::KC_ESCAPE) && m_escape)
		{
			m_sousState->exit();
			m_sousState=0;
			m_transitionning=true;
            m_timerTranslation.restart();
            m_transitionParams.from=m_camera->getPosition();
            m_transitionParams.to = Ogre::Vector3(0,0,10);
            m_transitionParams.duration=1.0;
            m_transitionParams.function = boost::bind(&MenuState::m_hide_sous_state, this);
		}
    }

    return CONTINUE;
}
bool MenuState::isVisible()
{
    return m_visible;
}
