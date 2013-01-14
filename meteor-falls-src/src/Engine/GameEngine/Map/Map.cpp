#include "Map.h"
#include "../../ScriptEngine/XmlDocumentManager.h"
#include "precompiled/lexical_cast.h"

#include <OgreSceneManager.h>
#include <OgreCamera.h>
#include <OgreQuaternion.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <Terrain/OgreTerrainMaterialGeneratorA.h>

#include <Terrain/OgreTerrainLayerBlendMap.h>

#include <OIS/OIS.h>
#include "../../GraphicEngine/Ogre/ogrecontextmanager.h"
#include "../../GraphicEngine/Ogre/OgreApplication.h"
#include "../../GraphicEngine/Ogre/OgreWindowInputManager.h"

#include <Hydrax/Noise/Perlin/Perlin.h>
#include <Hydrax/Modules/ProjectedGrid/ProjectedGrid.h>

#include "WorldObject.h"
#include "WorldObjectManager.h"
#include "../../../Utils/Random.h"
#include "../../../precompiled/lexical_cast.h"
#include "WorldObjectType.h"

using namespace rapidxml;

Map::Map(Ogre::SceneManager *p_scene_mgr)
{
    m_scene_mgr = p_scene_mgr;
    m_loaded = false;
	m_hydrax = nullptr;
	m_skyx   = nullptr;
}
Map::~Map()
{
	if(m_hydrax != nullptr)
		delete m_hydrax;
	if(m_skyx != nullptr)
	{
		OgreContextManager::get()->getOgreApplication()->getRoot()->removeFrameListener(m_skyx);
		OgreContextManager::get()->getOgreApplication()->getWindow()->removeListener(m_skyx);
		delete m_skyx;
	}
}
void Map::load(std::string p_name)
{
    m_loaded = true;
    m_name = p_name;
    rapidxml::xml_document<> *map_params = XmlDocumentManager::get()->getDocument("data/maps/" + p_name + "/" + p_name + ".scene");
    rapidxml::xml_node<>* rootNode  = map_params->first_node("scene");
    rapidxml::xml_node<>* environment = rootNode->first_node("environment");
    if(environment)
    {
        if(environment->first_node("colourAmbient"))
        {
            m_scene_mgr->setAmbientLight(getRGBA(environment->first_node("colourAmbient")));
        }
        if(environment->first_node("fog"))
        {
            rapidxml::xml_node<>* fog = environment->first_node("fog");
            Ogre::FogMode fogm;
            std::string fogstr(fog->first_attribute("mode")->value());
            if(fogstr=="none")
                fogm = Ogre::FogMode::FOG_NONE;
            else
                fogm = Ogre::FogMode::FOG_LINEAR;
            float start, end, density;
            start = boost::lexical_cast<float>(fog->first_attribute("start")->value());
            end = boost::lexical_cast<float>(fog->first_attribute("end")->value());
            density = boost::lexical_cast<float>(fog->first_attribute("density")->value());
            Ogre::ColourValue color;
            color = getRGBA(fog->first_node("colour"));
            m_scene_mgr->setFog(fogm, color, density, start, end);
        }
		if(environment->first_node("camera"))
		{
			rapidxml::xml_node<>* camNode = environment->first_node("camera");
			float far, near;
			Vector3D pos = getPosition(camNode->first_node("position"));
			far = boost::lexical_cast<float>(camNode->first_node("clipping")->first_attribute("far")->value());
			near = boost::lexical_cast<float>(camNode->first_node("clipping")->first_attribute("near")->value());
			Ogre::Quaternion rotation = getRotation(camNode->first_node("rotation"));
			std::string camName(camNode->first_attribute("name")->value());
			m_camera = m_scene_mgr->createCamera(camName);
			OgreContextManager::get()->getOgreApplication()->getWindow()->removeViewport(1);
			Ogre::Viewport *vp = OgreContextManager::get()->getOgreApplication()->getWindow()->addViewport(m_camera, 1);

			m_camera->setPosition(pos.convert<Ogre::Vector3>());
			m_camera->setNearClipDistance(near);
			m_camera->setFarClipDistance(far);

			m_camera_test = new CameraLibre();
			m_camera_test->setCamera(m_camera);
		}
    }
	rapidxml::xml_node<>* resources = rootNode->first_node("resourceLocations");
	if(resources)
	{
		rapidxml::xml_node<>* resource;
		std::vector<std::pair<std::string, std::string>> locationsVec;
		for(resource=resources->first_node("resourceLocation");resource;resource=resource->next_sibling())
		{
			std::string path = "data/maps/"+p_name +"/"+ std::string(resource->first_attribute("name")->value()).substr(3);
			locationsVec.push_back(std::make_pair<std::string, std::string>(std::string(path), std::string(resource->first_attribute("type")->value())));
		}
		OgreContextManager::get()->getOgreApplication()->AddResourceLocation(locationsVec);
		OgreContextManager::get()->getOgreApplication()->getRoot()->addResourceLocation("data/maps/"+p_name+"/"+"Hydrax/", "FileSystem", "Hydrax");
		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	}
    rapidxml::xml_node<>* terrain = rootNode->first_node("terrain");
    if(terrain)
    {
		float worldSize, mapSize, compositeDistance;
		int maxPixelError, maxBatch, minBatch;
		worldSize = boost::lexical_cast<float>(terrain->first_attribute("worldSize")->value());
		mapSize = boost::lexical_cast<float>(terrain->first_attribute("mapSize")->value());
		maxPixelError = boost::lexical_cast<int>(terrain->first_attribute("tuningMaxPixelError")->value());
		maxBatch = boost::lexical_cast<int>(terrain->first_attribute("tuningMaxBatchSize")->value());
		minBatch = boost::lexical_cast<int>(terrain->first_attribute("tuningMinBatchSize")->value());
		compositeDistance = boost::lexical_cast<int>(terrain->first_attribute("tuningCompositeMapDistance")->value());

		rapidxml::xml_node<>* nodePages = terrain->first_node("terrainPages");
		rapidxml::xml_node<>* nodePage;

		m_globals = OGRE_NEW Ogre::TerrainGlobalOptions();

		m_globals->setMaxPixelError(maxPixelError);
		m_globals->setCompositeMapDistance(compositeDistance);
		m_globals->setCompositeMapAmbient(m_scene_mgr->getAmbientLight());

		m_terrainGroup = OGRE_NEW Ogre::TerrainGroup(m_scene_mgr, Ogre::Terrain::ALIGN_X_Z, mapSize, worldSize);
		//m_terrainGroup->setResourceGroup("Maps");

		for(nodePage=nodePages->first_node("terrainPage");nodePage;nodePage=nodePage->next_sibling("terrainPage"))
		{
				std::string fileName = nodePage->first_attribute("name")->value();
				int px,py;
				px = boost::lexical_cast<int>(nodePage->first_attribute("pageX")->value());
				py = boost::lexical_cast<int>(nodePage->first_attribute("pageY")->value());
				m_terrainGroup->defineTerrain(px,py,fileName);
		}
		m_terrainGroup->loadAllTerrains(true);
    }
	rapidxml::xml_node<>* hydraxNode = rootNode->first_node("hydrax");
	if(hydraxNode)
	{
		std::string path = hydraxNode->first_attribute("configFile")->value();
		m_hydrax = new Hydrax::Hydrax(m_scene_mgr, m_camera, m_camera->getViewport());
		Hydrax::Module::ProjectedGrid *module = new Hydrax::Module::ProjectedGrid(m_hydrax, new Hydrax::Noise::Perlin(),
						Ogre::Plane(Ogre::Vector3(0,1,0), Ogre::Vector3(0,0,0)),
						Hydrax::MaterialManager::NM_VERTEX, Hydrax::Module::ProjectedGrid::Options());
		m_hydrax->setModule(static_cast<Hydrax::Module::Module*>(module));
		m_hydrax->loadCfg(path);
		m_hydrax->create();
	}
	rapidxml::xml_node<>* skyxNode = rootNode->first_node("skyx");
	if(skyxNode)
	{
		m_controller = new SkyX::BasicController();
		m_skyx = new SkyX::SkyX(m_scene_mgr, m_controller);

		SkyX::AtmosphereManager::Options options;

		options.RayleighMultiplier = boost::lexical_cast<float>(skyxNode->first_attribute("rayleighMultiplier")->value());
		options.MieMultiplier      = boost::lexical_cast<float>(skyxNode->first_attribute("mieMultiplier")->value());
		options.Exposure    = boost::lexical_cast<float>(skyxNode->first_attribute("exposure")->value());
		options.InnerRadius = boost::lexical_cast<float>(skyxNode->first_attribute("innerRadius")->value());
		options.OuterRadius = boost::lexical_cast<float>(skyxNode->first_attribute("outerRadius")->value());
		options.NumberOfSamples = boost::lexical_cast<int>(skyxNode->first_attribute("sampleCount")->value());
		options.HeightPosition = boost::lexical_cast<float>(skyxNode->first_attribute("height")->value());
		options.SunIntensity = boost::lexical_cast<float>(skyxNode->first_attribute("sunIntensity")->value());
		options.G      = boost::lexical_cast<float>(skyxNode->first_attribute("G")->value());

		rapidxml::xml_node<>* timeNode = skyxNode->first_node("time");
		if(timeNode)
		{
			float mult, curr, sunRise, sunSet;
			mult    = boost::lexical_cast<float>(timeNode->first_attribute("multiplier")->value());
			curr    = boost::lexical_cast<float>(timeNode->first_attribute("current")->value());
			sunRise = boost::lexical_cast<float>(timeNode->first_attribute("sunRise")->value());
			sunSet  = boost::lexical_cast<float>(timeNode->first_attribute("sunSet")->value());
			m_skyx->setTimeMultiplier(mult);
			m_controller->setTime(Ogre::Vector3(curr, sunRise, sunSet));
		}
		rapidxml::xml_node<>* eastNode = skyxNode->first_node("eastPosition");
		if(eastNode)
		{
			float X, Y;
			X = boost::lexical_cast<float>(eastNode->first_attribute("X")->value());
			Y = boost::lexical_cast<float>(eastNode->first_attribute("Y")->value());
			m_controller->setEastDirection(Ogre::Vector2(X,Y));
		}
		rapidxml::xml_node<>* waveN = skyxNode->first_node("waveLength");
		if(waveN)
		{
			Ogre::Vector3 length;
			length.x = boost::lexical_cast<float>(waveN->first_attribute("R")->value());
			length.y = boost::lexical_cast<float>(waveN->first_attribute("G")->value());
			length.z = boost::lexical_cast<float>(waveN->first_attribute("B")->value());
			options.WaveLength = length;
		}
		rapidxml::xml_node<>* cloudNode = skyxNode->first_node("vClouds");
		if(cloudNode)
		{
			float windDir, noiseScale;
			int windSpeed;
			windSpeed = boost::lexical_cast<int>(cloudNode->first_attribute("windSpeed")->value());
			windDir    = boost::lexical_cast<float>(cloudNode->first_attribute("windDirection")->value());
			noiseScale = boost::lexical_cast<float>(cloudNode->first_attribute("noiseScale")->value());
			m_skyx->getVCloudsManager()->getVClouds()->setWindSpeed(windSpeed);
			m_skyx->getVCloudsManager()->getVClouds()->setWindDirection(Ogre::Radian(windDir));
			m_skyx->getVCloudsManager()->setAutoupdate(true);
			m_skyx->getVCloudsManager()->getVClouds()->setNoiseScale(noiseScale);
			m_skyx->getVCloudsManager()->getVClouds()->setWheater(0.3, 1, false);
			m_skyx->getVCloudsManager()->setHeight(Ogre::Vector2(500,400));
			m_skyx->getVCloudsManager()->create(m_skyx->getMeshManager()->getSkydomeRadius(m_camera));
		}
		m_skyx->getAtmosphereManager()->setOptions(options);
		m_skyx->create();
		OgreContextManager::get()->getOgreApplication()->getRoot()->addFrameListener(m_skyx);
		OgreContextManager::get()->getOgreApplication()->getWindow()->addListener(m_skyx);
	}
	rapidxml::xml_node<>* nodes = rootNode->first_node("nodes");
	if(nodes)
	{
		rapidxml::xml_node<>* node = nodes->first_node("node");
		while(node)
		{
			processNode(node, m_scene_mgr->getRootSceneNode());
			node = node->first_node("node");
		}
	}
}
std::string Map::getName()
{
    return m_name;
}
void Map::update()
{
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
//    light->setDirection(-m_controller->getSunDirection());

    m_camera_test->update(1000/60);
    /* ############################################################## */

	m_hydrax->update(1.f/60.f);

    if(m_cycle_coef<=0.0001)
    {
        //m_controller->setTime(Ogre::Vector3(m_cycle_hour/100.f,6,22));
    }
}
bool Map::getLoaded()
{
    return m_loaded;
}
float Map::getHeightAt(float x, float z)
{
	return m_terrainGroup->getHeightAtWorldPosition(x,0.f,z);
}
Vector3D Map::getNormalAt(float x, float z)
{
    //On prend un triangle très proche
    Vector3D pts[3];

    for(int i=0; i<3; ++i)
    {
        pts[i].x = x;
        pts[i].z = z;
    }
    pts[0].x-=0.1;
    pts[2].z-=0.1;
    for(int i=0; i<3; ++i)
    {
        pts[i].y = getHeightAt(pts[i].x, pts[i].z);
    }
    // 2 vecteurs du triangle
    Vector3D vec[2];
    vec[0] = pts[1]-pts[0];
    vec[1] = pts[1]-pts[2];

    return Vector3D::produit_vectoriel(vec[0],vec[1]);
}
Ogre::ColourValue Map::getRGBA(rapidxml::xml_node<>* color)
{
    Ogre::ColourValue c;
    c.r = boost::lexical_cast<float>(color->first_attribute("r")->value());
    c.b = boost::lexical_cast<float>(color->first_attribute("g")->value());
    c.b = boost::lexical_cast<float>(color->first_attribute("b")->value());
    c.a = boost::lexical_cast<float>(color->first_attribute("a")->value());
    return c;
}
Vector3D Map::getPosition(rapidxml::xml_node<>* n, const std::string& prefix)
{
	Vector3D pos;
	pos.x = boost::lexical_cast<float>(n->first_attribute(std::string(prefix+"x").c_str())->value());
	pos.y = boost::lexical_cast<float>(n->first_attribute(std::string(prefix+"y").c_str())->value());
	pos.z = boost::lexical_cast<float>(n->first_attribute(std::string(prefix+"z").c_str())->value());
	return pos;
}
Ogre::Quaternion Map::getRotation(rapidxml::xml_node<>* n)
{
	Vector3D p = getPosition(n, "q");
	float w    = boost::lexical_cast<float>(n->first_attribute("qw")->value());
}
void Map::processNode(rapidxml::xml_node<>* n, Ogre::SceneNode* parent)
{
	Ogre::SceneNode *currentNode = parent->createChildSceneNode(n->first_attribute("name")->value());
	Vector3D position = getPosition(n->first_node("position"));
	Ogre::Quaternion rotation = getRotation(n->first_node("rotation"));
	Vector3D scale = getPosition(n->first_node("scale"));
	currentNode->setPosition(position.convert<Ogre::Vector3>());
	currentNode->setOrientation(rotation);
	currentNode->setScale(scale.convert<Ogre::Vector3>());
	/*
	 * Ajout des entités
	 * */
	rapidxml::xml_node<>* entite = n->first_node("entity");
	while(entite)
	{
		std::string cast_shadow = entite->first_attribute("castShadows")->value();
		std::string meshName = entite->first_attribute("meshFile")->value();
		Ogre::Entity *ent = m_scene_mgr->createEntity(meshName);
		ent->setCastShadows(cast_shadow=="true");
		currentNode->attachObject(ent);
		rapidxml::xml_node<>* subEntity = entite->first_node("subentity");
		while(subEntity)
		{
			int index = boost::lexical_cast<int>(subEntity->first_attribute("index")->value());
			ent->getSubEntity(index)->setMaterialName(subEntity->first_attribute("materialName")->value());
			subEntity = subEntity->first_node("subentity");
		}
		entite = entite->next_sibling("entity");
	}
	rapidxml::xml_node<>* nodes = n->first_node("node");
	while(nodes)
	{
		processNode(nodes, currentNode);
		nodes=nodes->next_sibling("node");
	}
}
