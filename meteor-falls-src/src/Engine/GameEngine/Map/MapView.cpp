#include "MapView.h"
#include "Map.h"
#include <Terrain/OgreTerrainGroup.h>
#include <SkyX/SkyX.h>
#include <OgreSceneManager.h>
#include <Hydrax/Hydrax.h>

#include "../ClientGameEngine.h"
#include "../../EngineManager/EngineManager.h"
#include "../../GraphicEngine/GraphicEngine.h"
#include "../Camera/CameraManager.h"
#include "../../../Utils/Configuration/Config.h"
#include "../../../Utils/Xml.h"

#include <PagedGeometry/PagedGeometry.h>
#include <PagedGeometry/GrassLoader.h>

#include <OIS/OIS.h>
#include "../../GraphicEngine/Ogre/ogrecontextmanager.h"
#include "../../GraphicEngine/Ogre/OgreApplication.h"
#include "../../GraphicEngine/Ogre/OgreWindowInputManager.h"

#include <Hydrax/Noise/Perlin/Perlin.h>
#include <Hydrax/Modules/ProjectedGrid/ProjectedGrid.h>

#include <OgreSceneManager.h>
#include <OgreCamera.h>
#include <OgreQuaternion.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <Terrain/OgreTerrainMaterialGeneratorA.h>
#include <Terrain/OgreTerrainLayerBlendMap.h>

MapView::MapView(Map* map): m_map(map), m_hydrax(nullptr), m_skyx(nullptr), m_pageGrass(nullptr)
{
	m_map->addListener(this);
	m_scene_mgr = m_map->game()->getManager()->getGraphic()->getSceneManager();
}
MapView::~MapView()
{
	if(m_hydrax != nullptr)
	{
		delete m_hydrax;
	}
	if(m_skyx != nullptr)
	{
		OgreContextManager::get()->getOgreApplication()->getRoot()->removeFrameListener(m_skyx);
		OgreContextManager::get()->getOgreApplication()->getWindow()->removeListener(m_skyx);
		delete m_skyx;
	}
	if(m_pageGrass)
		delete m_pageGrass;
}
void MapView::mapLoaded(const std::string& mapName)
{
	rapidxml::xml_document<> *map_params = m_map->getXmlMap();
	rapidxml::xml_node<>* rootNode  = map_params->first_node("scene");
	m_pageGrass = new Forests::PagedGeometry(((ClientGameEngine*)m_map->game())->cameraManager()->camera(), 50);
	m_pageGrass->addDetailLevel<Forests::GrassPage>(100);
	Forests::GrassLoader* grassLoader = new Forests::GrassLoader(m_pageGrass);
	m_pageGrass->setPageLoader(grassLoader);
	grassLoader->setHeightFunction(&MapView::staticGetHeightAt, this);
	m_pageGrass->setVisible(true);

	rapidxml::xml_node<>* resources = rootNode->first_node("resourceLocations");
	if(resources)
	{
		rapidxml::xml_node<>* resource;
		std::vector<std::pair<std::string, std::string>> locationsVec;
		for(resource=resources->first_node("resourceLocation");resource;resource=resource->next_sibling())
		{
			std::string path = m_map->mapRootPath()+std::string(resource->first_attribute("name")->value()).substr(3);
			locationsVec.push_back(std::make_pair<std::string, std::string>(std::string(path), std::string(resource->first_attribute("type")->value())));
		}
		OgreContextManager::get()->getOgreApplication()->AddResourceLocation(locationsVec);
		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	}
	rapidxml::xml_node<>* environment = rootNode->first_node("environment");
	if(environment)
	{
		if(environment->first_node("colourAmbient"))
		{
			m_scene_mgr->setAmbientLight(XmlUtils::getRGBA(environment->first_node("colourAmbient")));
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
			color = XmlUtils::getRGBA(fog->first_node("colour"));
			m_scene_mgr->setFog(fogm, color, density, start, end);
		}
		if(environment->first_node("camera"))
		{
			rapidxml::xml_node<>* camera = environment->first_node("camera");
			Vector3D pos = XmlUtils::getPosition(camera->first_node("position"));
			Ogre::Quaternion q = XmlUtils::getQuaternion(camera->first_node("rotation"));
			((ClientGameEngine*)m_map->game())->cameraManager()->camera()->setPosition(pos);
			((ClientGameEngine*)m_map->game())->cameraManager()->camera()->lookAt(0,0,0);
		}
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

		m_globals = OGRE_NEW Ogre::TerrainGlobalOptions();

		m_globals->setMaxPixelError(maxPixelError);
		m_globals->setCompositeMapDistance(compositeDistance);
		m_globals->setCompositeMapAmbient(m_scene_mgr->getAmbientLight());

		m_terrainGroup = OGRE_NEW Ogre::TerrainGroup(m_scene_mgr, Ogre::Terrain::ALIGN_X_Z, mapSize, worldSize);
		//m_terrainGroup->setResourceGroup("Maps");
		std::list<rapidxml::xml_node<>*> nodesGrass;
		for(rapidxml::xml_node<>* nodePage=nodePages->first_node("terrainPage");
				nodePage;nodePage=nodePage->next_sibling("terrainPage"))
		{
			std::string fileName = nodePage->first_attribute("name")->value();
			int px,py;
			px = boost::lexical_cast<int>(nodePage->first_attribute("pageX")->value());
			py = boost::lexical_cast<int>(nodePage->first_attribute("pageY")->value());
			m_terrainGroup->defineTerrain(px,py,fileName);
			rapidxml::xml_node<>* grassLayers = nodePage->first_node("grassLayers");
			if(grassLayers)
			{
				nodesGrass.push_back(nodePage);
			}
		}
		m_terrainGroup->loadAllTerrains(true);
		for(rapidxml::xml_node<>* nodePage : nodesGrass)
		{
			rapidxml::xml_node<>* grassLayers = nodePage->first_node("grassLayers");
			std::string densityMapName = grassLayers->first_attribute("densityMap")->value();

			int px,py;
			px = boost::lexical_cast<int>(nodePage->first_attribute("pageX")->value());
			py = boost::lexical_cast<int>(nodePage->first_attribute("pageY")->value());


			rapidxml::xml_node<>* grassLayerNode;
			for(grassLayerNode=grassLayers->first_node("grassLayer");grassLayerNode;
					grassLayerNode=grassLayerNode->next_sibling("grassLayer")) 
			{
				float top = boost::lexical_cast<float>(
						grassLayerNode->first_node("mapBounds")->first_attribute("top")->value());
				float bottom = boost::lexical_cast<float>(
						grassLayerNode->first_node("mapBounds")->first_attribute("bottom")->value());
				float left = boost::lexical_cast<float>(
						grassLayerNode->first_node("mapBounds")->first_attribute("left")->value());
				float right = boost::lexical_cast<float>(
						grassLayerNode->first_node("mapBounds")->first_attribute("right")->value());
				std::string material = grassLayerNode->first_attribute("material")->value();
				Forests::GrassLayer* layer = grassLoader->addLayer(material);
				layer->setMapBounds(Forests::TBounds(left, top, right, bottom));
				layer->setDensity(boost::lexical_cast<float>(
							grassLayerNode->first_node("densityMapProps")->first_attribute("density")->value()));
				layer->setMaxSlope(boost::lexical_cast<float>(
							grassLayerNode->first_attribute("maxSlope")->value()));
				layer->setRenderTechnique(Forests::GrassTechnique::GRASSTECH_CROSSQUADS);
				layer->setMinimumSize(
						boost::lexical_cast<float>(
							grassLayerNode->first_node("grassSizes")->first_attribute("minWidth")->value()),
						boost::lexical_cast<float>(
							grassLayerNode->first_node("grassSizes")->first_attribute("minHeight")->value())
						);
				layer->setMaximumSize(
						boost::lexical_cast<float>(
							grassLayerNode->first_node("grassSizes")->first_attribute("maxWidth")->value()),
						boost::lexical_cast<float>(
							grassLayerNode->first_node("grassSizes")->first_attribute("maxHeight")->value())
						);
				layer->setFadeTechnique(Forests::FADETECH_GROW);
				layer->setAnimationEnabled(true);
				layer->setSwayLength(
						boost::lexical_cast<float>(
							grassLayerNode->first_node("animation")->first_attribute("swayLength")->value()));
				layer->setSwaySpeed(
						boost::lexical_cast<float>(
							grassLayerNode->first_node("animation")->first_attribute("swaySpeed")->value()));
				layer->setSwayDistribution(
						boost::lexical_cast<float>(
							grassLayerNode->first_node("animation")->first_attribute("swayDistribution")->value()));

				std::string sChannel=grassLayerNode->first_node("densityMapProps")->first_attribute("channel")->value();
				Forests::MapChannel channel;
				if(sChannel=="RED")
					channel = Forests::MapChannel::CHANNEL_RED;
				else if(sChannel=="GREEN") 
					channel = Forests::MapChannel::CHANNEL_GREEN;
				else if(sChannel=="BLUE") 
					channel = Forests::MapChannel::CHANNEL_BLUE;
				layer->setDensityMap(densityMapName, channel);
			}
		}
		//Chargement de l'herbe
	}
	rapidxml::xml_node<>* hydraxNode = rootNode->first_node("hydrax");
	if(hydraxNode)
	{
		int qualite = Config::get()->getGraphicConfig()->getQualityWater();
		if(qualite == 1)
		{
			std::string path = hydraxNode->first_attribute("configFile")->value();
			m_hydrax = new Hydrax::Hydrax(m_scene_mgr, ((ClientGameEngine*)m_map->game())->cameraManager()->camera(), ((ClientGameEngine*)m_map->game())->cameraManager()->camera()->getViewport());
			Hydrax::Module::ProjectedGrid *module = new Hydrax::Module::ProjectedGrid(m_hydrax, new Hydrax::Noise::Perlin(),
					Ogre::Plane(Ogre::Vector3(0,1,0), Ogre::Vector3(0,0,0)),
					Hydrax::MaterialManager::NM_VERTEX, Hydrax::Module::ProjectedGrid::Options());
			m_hydrax->setModule(static_cast<Hydrax::Module::Module*>(module));
			m_hydrax->loadCfg(path);
			m_hydrax->create();
		}
		else
		{
			Ogre::Plane plan(Ogre::Vector3::UNIT_Y, 0);
			Ogre::MeshManager::getSingleton().createPlane("ocean", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plan, 10000, 10000, 10, 10, true, 1, 100, 100, Ogre::Vector3::UNIT_Z);
			Ogre::Entity *ocean = m_scene_mgr->createEntity("entiteOcean", "ocean");
			Ogre::SceneNode *nodeOcean = m_scene_mgr->getRootSceneNode()->createChildSceneNode();
			nodeOcean->attachObject(ocean);
			float alt = -0.1;
			if(hydraxNode->first_attribute("alt"))
				alt = boost::lexical_cast<float>(hydraxNode->first_attribute("alt")->value());
			nodeOcean->setPosition(Ogre::Vector3(0.f, alt, 0.f));
			if (qualite==3)
			{
				ocean->setMaterialName("OceanLow");
			}
			else
			{
				ocean->setMaterialName("OceanMedium");
			}
		}
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
			m_skyx->getVCloudsManager()->create(m_skyx->getMeshManager()->getSkydomeRadius(((ClientGameEngine*)m_map->game())->cameraManager()->camera()));
		}
		m_skyx->getAtmosphereManager()->setOptions(options);
		m_skyx->create();
		OgreContextManager::get()->getOgreApplication()->getRoot()->addFrameListener(m_skyx);
		OgreContextManager::get()->getOgreApplication()->getWindow()->addListener(m_skyx);
	}
}
void MapView::mapUnloaded()
{

}
void MapView::update()
{
	if(m_pageGrass)
		m_pageGrass->update();
}
void MapView::processNode(rapidxml::xml_node<>* n, Ogre::SceneNode* parent)
{
	Ogre::SceneNode *currentNode = parent->createChildSceneNode(n->first_attribute("name")->value());
	Vector3D position = XmlUtils::getPosition(n->first_node("position"));
	Ogre::Quaternion rotation = XmlUtils::getQuaternion(n->first_node("rotation"));
	Vector3D scale = XmlUtils::getPosition(n->first_node("scale"));
	currentNode->setPosition(position);
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
Ogre::Real MapView::staticGetHeightAt(Ogre::Real x, Ogre::Real z, void *map)
{
	return static_cast<MapView*>(map)->m_map->getHeightAt(x,z);
}
bool MapView::autoDelete() const
{
	return true;
}
