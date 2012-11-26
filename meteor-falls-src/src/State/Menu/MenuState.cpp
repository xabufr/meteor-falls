#include <string>
#include "MenuState.h"
#include "Engine/GraphicEngine/Ogre/ogrecontextmanager.h"
#include "Engine/GraphicEngine/Ogre/OgreApplication.h"
#include "Engine/GraphicEngine/Ogre/OgreWindowInputManager.h"
#include "../Game/GameState.h"
#include "Engine/GraphicEngine/Ogre/GetMeshInformation.h"
#include <boost/bind.hpp>

MenuState::MenuState(StateManager* mng):
    State(mng)
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

    CEGUI::SchemeManager::getSingleton().create("Interface.scheme");
    CEGUI::SchemeManager::getSingleton().create("OgreTray.scheme");
    CEGUI::System::getSingleton().setDefaultMouseCursor("Interface", "MouseArrow");
    CEGUI::MouseCursor::getSingleton().setImage( CEGUI::System::getSingleton().getDefaultMouseCursor());

    m_scene_mgr->getRootSceneNode()->setVisible(false);
    m_sceneQuery = m_scene_mgr->createRayQuery(Ogre::Ray());
}

MenuState::~MenuState()
{
    delete m_background;
}

bool MenuState::quit(const CEGUI::EventArgs &)
{
    OgreContextManager::get()->getOgreApplication()->getWindow()->destroy();
    return true;
}
bool MenuState::startGame()
{
    m_state_manager->addState(new GameState(m_state_manager));
    return true;
}

void MenuState::enter()
{
    m_scene_mgr->getRootSceneNode()->setVisible(true);
}

void MenuState::exit()
{
    m_scene_mgr->getRootSceneNode()->setVisible(false);
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

    m_nodeTerre->yaw(Ogre::Degree(6*time*0.001));
    m_nodeLune->yaw(Ogre::Degree(6*time*0.001));

    /*Piking*/
    CEGUI::Point mousePos = CEGUI::MouseCursor::getSingleton().getPosition();
    unsigned int width = OgreContextManager::get()->getOgreApplication()->getWindow()->getWidth(),
                height = OgreContextManager::get()->getOgreApplication()->getWindow()->getHeight();
    Ogre::Ray pickingRay = m_camera->getCameraToViewportRay(mousePos.d_x/float(width), mousePos.d_y/float(height));

    Ogre::Entity *selected = findFirstPicking(pickingRay, m_sceneQuery);

    bool click = m_mouse->getMouseState().buttonDown(OIS::MouseButtonID::MB_Left);
    if(!m_transitionning)
    {
        if(selected==m_eTerre||selected==m_eAtmoTerre)
        {
            if(click)
            {
                m_transitionning=true;
                m_timerTranslation.restart();
                m_transitionParams.from=m_camera->getPosition();
                m_transitionParams.to = m_nodeTerre->getPosition() + Ogre::Vector3(-7,1,7);
                m_transitionParams.duration=2.5;
                m_transitionParams.function = boost::bind(&MenuState::startGame, this);
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
                m_transitionParams.duration=2.5;
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
                m_transitionParams.duration=2.5;
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
                m_transitionParams.duration=2.5;
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
    if (m_keyboard->isKeyDown(OIS::KC_ESCAPE))
        return ret_code::EXIT_PROGRAM;
    return CONTINUE;
}
