#include "Map.h"
#include "Engine/ScriptEngine/XmlDocumentManager.h"
#include <boost/lexical_cast.hpp>
#include <Ogre.h>
#include <OIS/OIS.h>
#include <Terrain/OgreTerrain.h>
#include "Engine/GraphicEngine/Ogre/ogrecontextmanager.h"
#include "Engine/GraphicEngine/Ogre/OgreApplication.h"
#include "Engine/GraphicEngine/Ogre/OgreWindowInputManager.h"

using namespace rapidxml;

Map::Map(Ogre::SceneManager *p_scene_mgr)
{
    m_scene_mgr = p_scene_mgr;
    m_loaded = false;
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
    xml_attribute<> *size_z = size_y->next_attribute("z");
    m_size_z = boost::lexical_cast<int>(std::string(size_z->value()));
    xml_node<> *cycle = size->next_sibling("cycle");
    xml_attribute<> *cycle_enable = cycle->first_attribute("enable");
    m_cycle_enable = cycle_enable->value();
    if(std::string(cycle_enable->value()) == "true"){
        xml_node<> *cycle_duration = cycle->first_node("duration");
        m_cycle_duration = boost::lexical_cast<int>(std::string(cycle_duration->value()));
    }
    else
        m_cycle_duration = 0;
    xml_node<> *cycle_hour = cycle->first_node("hour");
    m_cycle_hour = boost::lexical_cast<int>(std::string(cycle_hour->value()));

    //chargement du terrain ogre
    Ogre::Terrain *m_terrain;
    Ogre::TerrainGlobalOptions *m_globals;
    m_terrain = OGRE_NEW Ogre::Terrain(m_scene_mgr);

    m_scene_mgr->setAmbientLight(Ogre::ColourValue(0.8, 0.8, 0.8));

    // options globales
    m_globals = OGRE_NEW Ogre::TerrainGlobalOptions();
    m_globals->setMaxPixelError(10);
    m_globals->setCompositeMapDistance(8000);

    Ogre::Light *light = m_scene_mgr->createLight("lumiere1");
    light->setDiffuseColour(1.0, 0.7, 1.0);
    light->setSpecularColour(1.0, 0.7, 1.0);
    light->setPosition(-100, 200, 100);
    //m_globals->setLightMapDirection(light->getDerivedDirection());
    m_globals->setCompositeMapAmbient(Ogre::ColourValue(0.8, 0.8, 0.8));
    //m_globals->setCompositeMapDiffuse(light->getDiffuseColour());

    m_camera = m_scene_mgr->createCamera("MapCam");
    Ogre::Viewport *vp = OgreContextManager::get()->getOgreApplication()->getWindow()->addViewport(m_camera);
    vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
    m_camera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

    m_camera->setPosition(Ogre::Vector3(0, 100, 0));
    m_camera->lookAt(Ogre::Vector3(-100, 100, -100));
    m_camera->setNearClipDistance(0.1);
    m_camera->setFarClipDistance(100000);

    Ogre::Image img;
    img.load(p_name + "/" + p_name + ".png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

    // informations géométriques
    Ogre::Terrain::ImportData imp;
    imp.inputImage = &img;
    imp.terrainSize = img.getWidth();
    imp.worldSize = 2000;
    imp.inputScale = 100;
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

    if(keyboard->isKeyDown(OIS::KC_Z))
        m_camera->moveRelative(Ogre::Vector3(0, 0, -10));
    if(keyboard->isKeyDown(OIS::KC_S))
        m_camera->moveRelative(Ogre::Vector3(0, 0, 10));
    if(keyboard->isKeyDown(OIS::KC_D))
        m_camera->moveRelative(Ogre::Vector3(10, 0, 0));
    if(keyboard->isKeyDown(OIS::KC_Q))
        m_camera->moveRelative(Ogre::Vector3(-10, 0, 0));
    m_camera->yaw(Ogre::Degree(-0.03*mouse->getMouseState().X.rel));
    m_camera->pitch(Ogre::Degree(-0.03*mouse->getMouseState().Y.rel));
    std::cout << mouse->getMouseState().Y.rel << std::endl;


}

bool Map::getLoaded(){
    return m_loaded;
}
