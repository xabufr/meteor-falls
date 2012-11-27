#include "../../meteor-falls-src/src/Engine/GameEngine/Map.h"
#include "../../meteor-falls-src/src/Engine/ScriptEngine/XmlDocumentManager.h"
#include <boost/lexical_cast.hpp>
#include <Ogre.h>
#include <Terrain/OgreTerrain.h>

using namespace rapidxml;

Map::Map()
{
    //ctor
}

Map::~Map()
{
    //dtor
}

void Map::load(std::string p_name){
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
    /*Ogre::Terrain *mTerrain;
    Ogre::TerrainGlobalOptions *mGlobals;
    mTerrain = OGRE_NEW Ogre::Terrain(mSceneMgr);

    // options globales
    mGlobals = OGRE_NEW Ogre::TerrainGlobalOptions();
    mGlobals->setMaxPixelError(10);
    mGlobals->setCompositeMapDistance(8000);
    mGlobals->setLightMapDirection(mLight->getDerivedDirection());
    mGlobals->setCompositeMapAmbient(mSceneMgr->getAmbientLight());
    mGlobals->setCompositeMapDiffuse(mLight->getDiffuseColour());

    Ogre::Image img;
    img.load("data/maps/" + p_name + "/" + p_name + ".png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

    // informations géométriques
    Ogre::Terrain::ImportData imp;
    imp.inputImage = &img;
    imp.terrainSize = img.getWidth();
    imp.worldSize = 8000;
    imp.inputScale = 600;
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
    mTerrain->prepare(imp);
    mTerrain->load();

    // plaquage de texture
    Ogre::TerrainLayerBlendMap* blendMap1 = mTerrain->getLayerBlendMap(1);
    float* pBlend1 = blendMap1->getBlendPointer();

    for (Ogre::uint16 y = 0; y < mTerrain->getLayerBlendMapSize(); ++y)
    {
        for (Ogre::uint16 x = 0; x < mTerrain->getLayerBlendMapSize(); ++x)
        {
            *pBlend1++ = 150;
        }
    }

    blendMap1->dirty();
    blendMap1->update();

    mTerrain->freeTemporaryResources();*/
}

std::string Map::getName(){
    return m_name;
}

void Map::update(){

}
