#include <string>
#include "MenuState.h"
#include "Engine/GraphicEngine/Ogre/ogrecontextmanager.h"
#include "Engine/GraphicEngine/Ogre/OgreApplication.h"
#include "Engine/GraphicEngine/Ogre/OgreWindowInputManager.h"
#include "../Game/GameState.h"

MenuState::MenuState(StateManager* mng):
    State(mng)
{
    m_mouse = OgreContextManager::get()->getInputManager()->getMouse();
    m_keyboard = OgreContextManager::get()->getInputManager()->getKeyboard();

    OgreContextManager::get()->getOgreApplication()->LoadRessources("resources.cfg");

    m_scene_mgr = OgreContextManager::get()->getOgreApplication()->getRoot()->createSceneManager("DefaultSceneManager", "Menu");
    m_scene_mgr->setAmbientLight(Ogre::ColourValue(1.0, 1.0, 1.0));

    m_camera = m_scene_mgr->createCamera("MenuCam");
    m_camera->lookAt(Ogre::Vector3(0, 0, 0));
    m_camera->setNearClipDistance(5);

    Ogre::Viewport *vp = OgreContextManager::get()->getOgreApplication()->getWindow()->addViewport(m_camera);
    vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
    m_camera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

    m_background = new Ogre::Rectangle2D(true);
    m_background->setCorners(-1.0, 1.0, 1.0, -1.0);
    m_background->setMaterial("background");
    m_background->setRenderQueueGroup(Ogre::RENDER_QUEUE_BACKGROUND);

    Ogre::AxisAlignedBox aabInf;
    aabInf.setInfinite();
    m_background->setBoundingBox(aabInf);

    Ogre::SceneNode *node = m_scene_mgr->getRootSceneNode()->createChildSceneNode("NodeBackground", Ogre::Vector3::ZERO, Ogre::Quaternion::IDENTITY);
    node->attachObject(m_background);

    Ogre::Entity *m_sphere = m_scene_mgr->createEntity("Sphere", "Sphere.mesh");
    node = m_scene_mgr->getRootSceneNode()->createChildSceneNode("NodeSphere", Ogre::Vector3(0, 0, -10), Ogre::Quaternion::IDENTITY);
    m_sphere->setMaterialName("terre");
    node->attachObject(m_sphere);

    //./bootstrap + ./configure + make -j3 + sudo make install

    //A commenter
    //OgreContextManager::get()->getInputManager()->injectMouseEventToCEGUI(false);
    //OgreContextManager::get()->getInputManager()->injectKeyboardEventToCEGUI(false);

    m_renderer = &CEGUI::OgreRenderer::bootstrapSystem();

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

    m_sheet = m_window_mgr.createWindow("OgreTray/TabButtonPane", "FenetreMenu");
    m_sheet->setSize(CEGUI::UVector2(CEGUI::UDim(0.30, 0), CEGUI::UDim(0.50, 0)));
    m_sheet->setPosition(CEGUI::UVector2(CEGUI::UDim(0.50-(m_sheet->getSize().d_x.d_scale/2), 0), CEGUI::UDim(0.30, 0)));

    CEGUI::Window *m_play = m_window_mgr.createWindow("OgreTray/Button", "BoutonJouer");
    m_play->setText("Jouer");
    m_play->setSize(CEGUI::UVector2(CEGUI::UDim(0.80, 0), CEGUI::UDim(0.10, 0)));
    m_play->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MenuState::startGame, this));
    m_sheet->addChildWindow(m_play);

    CEGUI::Window *m_option = m_window_mgr.createWindow("OgreTray/Button", "BoutonOption");
    m_option->setText("Options");
    m_option->setSize(CEGUI::UVector2(CEGUI::UDim(0.80, 0), CEGUI::UDim(0.10, 0)));
    m_sheet->addChildWindow(m_option);

    CEGUI::Window *m_credit = m_window_mgr.createWindow("OgreTray/Button", "BoutonCredit");
    m_credit->setText("Credits");
    m_credit->setSize(CEGUI::UVector2(CEGUI::UDim(0.80, 0), CEGUI::UDim(0.10, 0)));
    m_sheet->addChildWindow(m_credit);

    CEGUI::Window *m_quit = m_window_mgr.createWindow("OgreTray/Button", "BoutonQuitter");
    m_quit->setText("Quitter");
    m_quit->setSize(CEGUI::UVector2(CEGUI::UDim(0.80, 0), CEGUI::UDim(0.10, 0)));
    m_quit->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MenuState::quit, this));
    m_sheet->addChildWindow(m_quit);

    m_play->setPosition(CEGUI::UVector2(CEGUI::UDim(0.50-(m_play->getSize().d_x.d_scale/2), 0),
                                         CEGUI::UDim(0+(m_sheet->getSize().d_y.d_scale/m_sheet->getChildCount()), 0)));
    m_option->setPosition(CEGUI::UVector2(CEGUI::UDim(0.50-(m_option->getSize().d_x.d_scale/2), 0),
                                           CEGUI::UDim(0.12+(m_sheet->getSize().d_y.d_scale/m_sheet->getChildCount()), 0)));
    m_credit->setPosition(CEGUI::UVector2(CEGUI::UDim(0.50-(m_credit->getSize().d_x.d_scale/2), 0),
                                           CEGUI::UDim(0.24+(m_sheet->getSize().d_y.d_scale/m_sheet->getChildCount()), 0)));
    m_quit->setPosition(CEGUI::UVector2(CEGUI::UDim(0.50-(m_quit->getSize().d_x.d_scale/2), 0),
                                         CEGUI::UDim(0.36+(m_sheet->getSize().d_y.d_scale/m_sheet->getChildCount()), 0)));

    CEGUI::System::getSingleton().setGUISheet(m_sheet);
    m_sheet->hide();
    m_scene_mgr->getRootSceneNode()->setVisible(false);
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
bool MenuState::startGame(const CEGUI::EventArgs&)
{
    m_state_manager->addState(new GameState(m_state_manager));
    return true;
}

void MenuState::enter()
{
    m_sheet->show();
    CEGUI::System::getSingleton().setGUISheet(m_sheet);
    m_scene_mgr->getRootSceneNode()->setVisible(true);
}

void MenuState::exit()
{
    m_sheet->hide();
    m_scene_mgr->getRootSceneNode()->setVisible(false);
    OgreContextManager::get()->getOgreApplication()->getWindow()->removeAllViewports();
    OgreContextManager::get()->getOgreApplication()->getRoot()->destroySceneManager(m_scene_mgr);
}

ret_code MenuState::work()
{
    if (m_keyboard->isKeyDown(OIS::KC_ESCAPE))
        return ret_code::EXIT_PROGRAM;
    return CONTINUE;
}
