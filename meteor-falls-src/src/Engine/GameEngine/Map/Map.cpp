#include "Map.h"
#include "Engine/ScriptEngine/XmlDocumentManager.h"
#include "precompiled/lexical_cast.h"

#include <OgreSceneManager.h>

#include <OgreCamera.h>
#include <Terrain/OgreTerrainLayerBlendMap.h>

#include <OIS/OIS.h>
#include "Engine/GraphicEngine/Ogre/ogrecontextmanager.h"
#include "Engine/GraphicEngine/Ogre/OgreApplication.h"
#include "Engine/GraphicEngine/Ogre/OgreWindowInputManager.h"

#include <Noise/Perlin/Perlin.h>
#include <Modules/ProjectedGrid/ProjectedGrid.h>

using namespace rapidxml;

Map::Map(Ogre::SceneManager *p_scene_mgr)
{
    m_scene_mgr = p_scene_mgr;
    m_loaded = false;
    m_controller = new SkyX::BasicController();
    m_skyx = new SkyX::SkyX(p_scene_mgr, m_controller);
    m_skyx->create();


    OgreContextManager::get()->getOgreApplication()->getRoot()->addFrameListener(m_skyx);
    OgreContextManager::get()->getOgreApplication()->getWindow()->addListener(m_skyx);

    m_skyx->getCloudsManager()->add(SkyX::CloudLayer::Options(/* Default options */));

    m_timer.reset();

}

Map::~Map()
{
    //dtor
}

void Map::load(std::string p_name){
    m_loaded = true;
    m_name = p_name;
    rapidxml::xml_document<> *map_params = XmlDocumentManager::get()->getDocument("data/maps/" + p_name + "/" + p_name + ".xml");
    xml_node<> *size = map_params->first_node("map")->first_node("size");
    xml_attribute<> *size_x = size->first_attribute("x");
    m_size_x = boost::lexical_cast<int>(std::string(size_x->value()));
    xml_attribute<> *size_y = size_x->next_attribute("y");
    m_size_y = boost::lexical_cast<int>(std::string(size_y->value()));
    xml_node<> *cycle = size->next_sibling("cycle");
    xml_attribute<> *cycle_enable = cycle->first_attribute("enable");
    m_cycle_enable = cycle_enable->value();
    if(std::string(cycle_enable->value()) == "true"){
        xml_node<> *cycle_duration = cycle->first_node("duration");
        m_cycle_coef = boost::lexical_cast<float>(std::string(cycle_duration->value()));

        m_skyx->setTimeMultiplier(m_cycle_coef);
    }
    else
    {
        m_cycle_coef = 0;
    }
    xml_node<> *cycle_hour = cycle->first_node("hour");
    m_cycle_hour = boost::lexical_cast<int>(std::string(cycle_hour->value()));
    m_controller->setTime(Ogre::Vector3(m_cycle_hour/100.f,6,22));


    //chargement du terrain ogre
    Ogre::Terrain *m_terrain;

    m_terrain = OGRE_NEW Ogre::Terrain(m_scene_mgr);

    m_scene_mgr->setAmbientLight(Ogre::ColourValue(0, 0, 0));

    // options globales
    m_globals = OGRE_NEW Ogre::TerrainGlobalOptions();
    m_globals->setMaxPixelError(10);
    m_globals->setCompositeMapDistance(8000);

    light = m_scene_mgr->createLight("soleil");
    light->setDiffuseColour(1.0, 1.0, 1.0);
    light->setSpecularColour(1.0, 1.0, 1.0);
    light->setType(Ogre::Light::LightTypes::LT_DIRECTIONAL);
    light->setDirection(Ogre::Vector3(0,-1,0));

    m_globals->setLightMapDirection(light->getDerivedDirection());
    m_globals->setCompositeMapAmbient(Ogre::ColourValue(0, 0, 0));
    m_globals->setCompositeMapDiffuse(light->getDiffuseColour());

    m_camera = m_scene_mgr->createCamera("FreeCam");
    Ogre::Viewport *vp = OgreContextManager::get()->getOgreApplication()->getWindow()->addViewport(m_camera);
    vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
    m_camera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

    m_camera->setPosition(Ogre::Vector3(0, 100, 0));
    m_camera->lookAt(Ogre::Vector3(-100, 100, -100));
    m_camera->setNearClipDistance(0.1);
    m_camera->setFarClipDistance(100000);

    m_camera_test = new CameraLibre();
    m_camera_test->setCamera(m_camera);

 /*   m_hydrax = new Hydrax::Hydrax(m_scene_mgr, m_camera, m_camera->getViewport());
    Hydrax::Module::ProjectedGrid *mModule
			= new Hydrax::Module::ProjectedGrid(// Hydrax parent pointer
			                                    m_hydrax,
												// Noise module
			                                    new Hydrax::Noise::Perlin(/*Generic one*//*),
											/*	// Base plane
			                                    Ogre::Plane(Ogre::Vector3(0,1,0), Ogre::Vector3(0,0,0)),
												// Normal mode
												Hydrax::MaterialManager::NM_VERTEX,
												// Projected grid options
										      /*  Hydrax::Module::ProjectedGrid::Options(/*264 /*Generic one*//*));
   /* m_hydrax->setModule(static_cast<Hydrax::Module::Module*>(mModule));*/

    // Load all parameters from config file
    // Remarks: The config file must be in Hydrax resource group.
    // All parameters can be set/updated directly by code(Like previous versions),
    // but due to the high number of customizable parameters, since 0.4 version, Hydrax allows save/load config files.
   /* m_hydrax->loadCfg("Tropical.hdx");
    m_hydrax->create();*/

    Ogre::Image img;
    img.load(p_name + "/" + p_name + ".png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

    // informations géométriques
    Ogre::Terrain::ImportData imp;
    imp.inputImage = &img;
    imp.terrainSize = img.getWidth();
    imp.worldSize = m_size_x;
    imp.inputScale = m_size_y;
    imp.minBatchSize = 33;
    imp.maxBatchSize = 65;

    // textures
    imp.layerList.resize(3);
    imp.layerList[0].worldSize = 100;
    imp.layerList[0].textureNames.push_back("grass_green-01_diffusespecular.dds");
    imp.layerList[0].textureNames.push_back("grass_green-01_normalheight.dds");
    imp.layerList[1].worldSize = 30;
    imp.layerList[1].textureNames.push_back("growth_weirdfungus-03_diffusespecular.dds");
    imp.layerList[1].textureNames.push_back("growth_weirdfungus-03_normalheight.dds");
    imp.layerList[2].worldSize = 200;
    imp.layerList[2].textureNames.push_back("dirt_grayrocky_diffusespecular.dds");
    imp.layerList[2].textureNames.push_back("dirt_grayrocky_normalheight.dds");
    m_terrain->prepare(imp);
    m_terrain->load();

    // plaquage de texture
    Ogre::TerrainLayerBlendMap* blendMap1 = m_terrain->getLayerBlendMap(1);
    float* pBlend1 = blendMap1->getBlendPointer();

    for (Ogre::uint16 y = 0; y < m_terrain->getLayerBlendMapSize(); ++y)
    {
        for (Ogre::uint16 x = 0; x < m_terrain->getLayerBlendMapSize(); ++x)
        {
            *pBlend1++ = 150;
        }
    }

    blendMap1->dirty();
    blendMap1->update();


    //Hero MonHero("ninja","ninja.mesh",m_scene_mgr);
    Ogre::Light *light = m_scene_mgr->createLight("lumiere1");

    light->setDiffuseColour(1.0, 0.7, 1.0);
    light->setSpecularColour(1.0, 0.7, 1.0);
    light->setPosition(0, 200, 0);
    m_Eninja = m_scene_mgr->createEntity("ninja", "ninja.mesh");
    m_node = m_scene_mgr->getRootSceneNode()->createChildSceneNode("nodeninja", Ogre::Vector3::ZERO, Ogre::Quaternion::IDENTITY);
    m_node->attachObject(m_Eninja);
    m_posx_hero = 0;
    m_posy_hero = 110;
    m_posz_hero = 0;
    Ogre::Vector3 myVector(m_posx_hero,m_posy_hero,m_posz_hero);
    m_node->setPosition(myVector);
    m_node->attachObject(light);

    m_terrain->freeTemporaryResources();
}

std::string Map::getName(){
    return m_name;
}

void Map::update(){

    OIS::Mouse* mouse;
    mouse = OgreContextManager::get()->getInputManager()->getMouse();
    OIS::Keyboard* keyboard;
    keyboard = OgreContextManager::get()->getInputManager()->getKeyboard();
    Ogre::RenderWindow* window = OgreContextManager::get()->getOgreApplication()->getWindow();
    CEGUI::Point mouse_pos = CEGUI::MouseCursor::getSingleton().getPosition();


    /* ############### Test Camera Libre et Camera RTS ############## */
    m_camera_test->forward(keyboard->isKeyDown(OIS::KC_Z) );
    m_camera_test->back(keyboard->isKeyDown(OIS::KC_S));
    m_camera_test->right(keyboard->isKeyDown(OIS::KC_D));
    m_camera_test->left(keyboard->isKeyDown(OIS::KC_Q));
    m_camera_test->lookRightLeft(Ogre::Degree(-mouse->getMouseState().X.rel*0.1));
    m_camera_test->lookUpDown(Ogre::Degree(-mouse->getMouseState().Y.rel*0.1));


    /* ############### Test Mouvement Heros ############## */
    bool animation_is_finished = false;
    bool no_key = true;
   // do
   // {
        if(keyboard->isKeyDown(OIS::KC_P) )
        {
            m_posy_hero += 5;
            mAnimationState = m_Eninja->getAnimationState("Climb");
            mAnimationState->setLoop(true);
            mAnimationState->setEnabled(true);
            mAnimationState->addTime((m_timer.getMilliseconds())/1500.f);
            m_timer.reset();
            no_key = false;
        }
        else if(keyboard->isKeyDown(OIS::KC_M) )
        {
            m_posy_hero -= 5;
            mAnimationState = m_Eninja->getAnimationState("Climb");
            mAnimationState->setLoop(true);
            mAnimationState->setEnabled(true);
            mAnimationState->addTime((m_timer.getMilliseconds())/1500.f);
            m_timer.reset();
            no_key = false;
        }
        else if(keyboard->isKeyDown(OIS::KC_UP) )
        {
            m_posz_hero -= 5;
            mAnimationState = m_Eninja->getAnimationState("Walk");
            mAnimationState->setLoop(true);
            mAnimationState->setEnabled(true);
            mAnimationState->addTime((m_timer.getMilliseconds())/1500.f);
            m_timer.reset();
            no_key = false;
        }
        else if(keyboard->isKeyDown(OIS::KC_DOWN))
        {
            m_posz_hero += 5;
            mAnimationState = m_Eninja->getAnimationState("Walk");
            mAnimationState->setLoop(true);
            mAnimationState->setEnabled(true);
            mAnimationState->addTime((m_timer.getMilliseconds())/1500.f);
            m_timer.reset();
            no_key = false;
        }
        else if(keyboard->isKeyDown(OIS::KC_RIGHT))
        {
            m_posx_hero += 5;
            mAnimationState = m_Eninja->getAnimationState("Walk");
            mAnimationState->setLoop(true);
            mAnimationState->setEnabled(true);
            mAnimationState->addTime((m_timer.getMilliseconds())/1500.f);
            m_timer.reset();
            no_key = false;
        }
        else if(keyboard->isKeyDown(OIS::KC_LEFT))
        {
            m_posx_hero -= 5;
            mAnimationState = m_Eninja->getAnimationState("Walk");
            mAnimationState->setLoop(true);
            mAnimationState->setEnabled(true);
            mAnimationState->addTime((m_timer.getMilliseconds())/1500.f);
            m_timer.reset();
            no_key = false;
        }
        /* ###############  Heros Attaque / backflip  ############## */
        else if(keyboard->isKeyDown(OIS::KC_E))
        {
            mAnimationState = m_Eninja->getAnimationState("Attack3");
            mAnimationState->setLoop(true);
            mAnimationState->setEnabled(true);
            mAnimationState->addTime((m_timer.getMilliseconds())/1500.f);
            m_timer.reset();
            no_key = false;
        }
        else if(keyboard->isKeyDown(OIS::KC_R))
        {
            mAnimationState = m_Eninja->getAnimationState("Death1");
            mAnimationState->setLoop(true);
            mAnimationState->setEnabled(true);
            mAnimationState->addTime((m_timer.getMilliseconds())/1500.f);
            m_timer.reset();
            no_key = false;
        }

        // if (no_key == false)
        /*    if (static_cast <float> (m_timer.getMilliseconds()) >= mAnimationState->getLength())
                animation_is_finished = true;

    }while(animation_is_finished == false);*/

    // update position
    Ogre::Vector3 myVector(m_posx_hero,m_posy_hero,m_posz_hero);
    m_node->setPosition(myVector);


    light->setDirection(-m_controller->getSunDirection());
    m_camera_test->update(1000/60);

   // m_hydrax->update(1.f/60.f);

    if(m_cycle_coef<=0.0001)
    {
        m_controller->setTime(Ogre::Vector3(m_cycle_hour/100.f,6,22));
    }
}

bool Map::getLoaded(){
    return m_loaded;
}
