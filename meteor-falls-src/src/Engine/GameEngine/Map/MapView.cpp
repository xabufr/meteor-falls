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
#include <PagedGeometry/BatchPage.h>
#include <PagedGeometry/ImpostorPage.h>
#include <PagedGeometry/GrassLoader.h>
#include <PagedGeometry/TreeLoader3D.h>

#include <OIS/OIS.h>
#include "../../GraphicEngine/Ogre/ogrecontextmanager.h"
#include "../../GraphicEngine/Ogre/OgreApplication.h"
#include "../../GraphicEngine/Ogre/OgreWindowInputManager.h"

#include <Hydrax/Noise/Perlin/Perlin.h>
#include <Hydrax/Modules/ProjectedGrid/ProjectedGrid.h>

#include <OgreSceneManager.h>
#include <OgreCamera.h>
#include "../../../Utils/Quaternion.h"
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <OgreLight.h>
#include <Terrain/OgreTerrainMaterialGeneratorA.h>
#include <Terrain/OgreTerrainLayerBlendMap.h>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

MapView::MapView(Map* map): m_map(map), m_hydrax(nullptr), m_skyx(nullptr), m_pageGrass(nullptr), m_sunLight(nullptr)
{
	m_temp_dir = "data/temp/";
	m_map->addListener(this);
	m_scene_mgr = m_map->game()->getManager()->getGraphic()->getSceneManager();
	m_scene_mgr->setShadowTechnique(Ogre::ShadowTechnique::SHADOWTYPE_TEXTURE_ADDITIVE_INTEGRATED);
}
MapView::~MapView()
{
}
void MapView::mapLoaded(const std::string& mapName)
{
	XmlDocumentManager::Document& map_params = m_map->getXmlMap();

	m_pageGrass = new Forests::PagedGeometry(((ClientGameEngine*)m_map->game())->cameraManager()->camera(), 50);
	m_pageGrass->setTempDir(m_temp_dir);
	m_pageGrass->addDetailLevel<Forests::GrassPage>(100);
	Forests::GrassLoader* grassLoader = new Forests::GrassLoader(m_pageGrass);
	m_pageGrass->setPageLoader(grassLoader);
	grassLoader->setHeightFunction(&MapView::staticGetHeightAt, this);
	m_pageGrass->setVisible(true);
	if(!m_sunLight)
	{
		m_sunLight = m_scene_mgr->createLight("mapSunLight");
		m_sunLight->setType(Ogre::Light::LT_DIRECTIONAL);
		m_sunLight->setDiffuseColour(Ogre::ColourValue::White);
		m_sunLight->setSpecularColour(0.8, 0.8, 0.8);
		m_sunLight->setDirection(Ogre::Vector3(0.55, -0.3, 0.75).normalisedCopy());
		m_sunLight->setVisible(false);
	}
	auto bounds = map_params.get_child("scene.resourceLocations").equal_range("resourceLocation");
	{
		std::vector<std::pair<std::string, std::string>> locationsVec;
		for(auto it=bounds.first;it!=bounds.second;++it)
		{
			std::string path = m_map->mapRootPath()+it->second.get<std::string>("<xmlattr>.name").substr(3);
			locationsVec.push_back(std::make_pair<std::string, std::string>(std::string(path), it->second.get<std::string>("<xmlattr>.type")));
		}
		OgreContextManager::get()->getOgreApplication()->AddResourceLocation(locationsVec);
		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	}
	{
		m_scene_mgr->setAmbientLight(XmlUtils::getRGBA(map_params.get_child("scene.environment.colourAmbient.<xmlattr>")));
		{
			Ogre::FogMode fogm;
			std::string fogstr = map_params.get("scene.environment.fog.<xmlattr>.mode", "none");
			if(fogstr=="none")
				fogm = Ogre::FogMode::FOG_NONE;
			else
				fogm = Ogre::FogMode::FOG_LINEAR;
			float start, end, density;
			start   = map_params.get("scene.environment.fog.<xmlattr>.start", 0.f);
			end     = map_params.get("scene.environment.fog.<xmlattr>.end", 1000.f);
			density = map_params.get("scene.environment.fog.<xmlattr>.density", 0.f);
			Ogre::ColourValue color;
			color   = XmlUtils::getRGBA(map_params.get_child("scene.environment.fog.colour.<xmlattr>"));
			m_scene_mgr->setFog(fogm, color, density, start, end);
		}
		{
			Vector3D pos = XmlUtils::getPosition(map_params.get_child("scene.environment.camera.position.<xmlattr>"));
			Ogre::Quaternion q = XmlUtils::getQuaternion(map_params.get_child("scene.environment.camera.rotation.<xmlattr>"));
			((ClientGameEngine*)m_map->game())->cameraManager()->camera()->setPosition(pos);
			((ClientGameEngine*)m_map->game())->cameraManager()->camera()->lookAt(0,0,0);
		}
	}
	{
		float worldSize, mapSize, compositeDistance;
		int maxPixelError, maxBatch, minBatch;
		worldSize = map_params.get<float>("scene.terrain.<xmlattr>.worldSize");
		mapSize = map_params.get<float>("scene.terrain.<xmlattr>.mapSize");
		maxPixelError = map_params.get<int>("scene.terrain.<xmlattr>.tuningMaxPixelError");
		maxBatch = map_params.get<int>("scene.terrain.<xmlattr>.tuningMaxBatchSize");
		minBatch = map_params.get<int>("scene.terrain.<xmlattr>.tuningMinBatchSize");
		compositeDistance = map_params.get<int>("scene.terrain.<xmlattr>.tuningCompositeMapDistance");

		m_globals = OGRE_NEW Ogre::TerrainGlobalOptions();

		m_globals->setMaxPixelError(maxPixelError);
		m_globals->setCompositeMapDistance(compositeDistance);
		m_globals->setCompositeMapAmbient(m_scene_mgr->getAmbientLight());
		m_globals->setCastsDynamicShadows(false);

		m_terrainGroup = OGRE_NEW Ogre::TerrainGroup(m_scene_mgr, Ogre::Terrain::ALIGN_X_Z, mapSize, worldSize);
		m_terrainGroup->setOrigin(Ogre::Vector3::ZERO);
		//m_terrainGroup->setResourceGroup("Maps");
		std::list<const boost::property_tree::ptree*> nodesGrass;
		bounds = map_params.get_child("scene.terrain.terrainPages").equal_range("terrainPage");
		for(boost::property_tree::ptree::const_assoc_iterator it = bounds.first;it!=bounds.second;++it)
		{
			std::string fileName = it->second.get<std::string>("<xmlattr>.name");
			int px,py;
			px = it->second.get<int>("<xmlattr>.pageX");
			py = it->second.get<int>("<xmlattr>.pageY");
			m_terrainGroup->defineTerrain(px,py,fileName);
			if(it->second.count("grassLayers") > 0)
			{
				nodesGrass.push_back(&it->second);
			}
		}
		m_terrainGroup->loadAllTerrains(true);
		static_cast<Ogre::TerrainMaterialGeneratorA::SM2Profile*>(m_globals->getDefaultMaterialGenerator()->getActiveProfile())->setLightmapEnabled(true);
		//Chargement de l'herbe
		for(const boost::property_tree::ptree* nodePage : nodesGrass)
		{
			std::string densityMapName = nodePage->get<std::string>("grassLayers.<xmlattr>.densityMap");

			int px,py;
			px = nodePage->get<int>("<xmlattr>.pageX");
			py = nodePage->get<int>("<xmlattr>.pageY");

			auto boundsLayers = nodePage->get_child("grassLayers").equal_range("grassLayer");
			for(boost::property_tree::ptree::const_assoc_iterator it=boundsLayers.first;it!=boundsLayers.second;++it)
			{
				float top = it->second.get<float>("mapBounds.<xmlattr>.top");
				float bottom = it->second.get<float>("mapBounds.<xmlattr>.bottom");
				float left = it->second.get<float>("mapBounds.<xmlattr>.left");
				float right = it->second.get<float>("mapBounds.<xmlattr>.right");

				std::string material = it->second.get<std::string>("<xmlattr>.material");
				Forests::GrassLayer* layer = grassLoader->addLayer(material);
				layer->setMapBounds(Forests::TBounds(left, top, right, bottom));
				layer->setDensity(it->second.get<float>("densityMapProps.<xmlattr>.density"));
				layer->setMaxSlope(it->second.get<float>("<xmlattr>.maxSlope"));
				layer->setRenderTechnique(Forests::GrassTechnique::GRASSTECH_CROSSQUADS);
				layer->setMinimumSize(
						it->second.get<float>("grassSizes.<xmlattr>.minWidth"),
						it->second.get<float>("grassSizes.<xmlattr>.minHeight"));
				layer->setMaximumSize(
						it->second.get<float>("grassSizes.<xmlattr>.maxWidth"),
						it->second.get<float>("grassSizes.<xmlattr>.maxHeight"));
				layer->setFadeTechnique(Forests::FADETECH_GROW);
				layer->setAnimationEnabled(true);
				layer->setSwayLength( it->second.get<float>("animation.<xmlattr>.swayLength"));
				layer->setSwaySpeed( it->second.get<float>("animation.<xmlattr>.swaySpeed"));
				layer->setSwayDistribution( it->second.get<float>("animation.<xmlattr>.swayDistribution"));

				std::string sChannel=it->second.get<std::string>("densityMapProps.<xmlattr>.channel");
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
	}
	try
	{
		map_params.get_value("scene.hydrax");
		int qualite = Config::get()->getGraphicConfig()->getQualityWater();
		if(qualite == 1)
		{
			std::string path = map_params.get<std::string>("scene.hydrax.<xmlattr>.configFile");
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
			float alt = map_params.get<float>("scene.hydrax.<xmlattr>.alt", -0.1f);
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
	catch(...){
	}
	try
	{
		map_params.get_child("scene.skyx");
		m_controller = new SkyX::BasicController();
		m_skyx = new SkyX::SkyX(m_scene_mgr, m_controller);

		SkyX::AtmosphereManager::Options options;

		options.RayleighMultiplier = map_params.get<float>("scene.skyx.<xmlattr>.rayleighMultiplier");
		options.MieMultiplier      = map_params.get<float>("scene.skyx.<xmlattr>.mieMultiplier");
		options.Exposure    = map_params.get<float>("scene.skyx.<xmlattr>.exposure");
		options.InnerRadius = map_params.get<float>("scene.skyx.<xmlattr>.innerRadius");
		options.OuterRadius = map_params.get<float>("scene.skyx.<xmlattr>.outerRadius");
		options.NumberOfSamples = map_params.get<int>("scene.skyx.<xmlattr>.sampleCount");
		options.HeightPosition = map_params.get<float>("scene.skyx.<xmlattr>.height");
		options.SunIntensity = map_params.get<float>("scene.skyx.<xmlattr>.sunIntensity");
		options.G      = map_params.get<float>("scene.skyx.<xmlattr>.G");

		try {
			float mult, curr, sunRise, sunSet;
			mult    = map_params.get<float>("scene.skyx.time.<xmlattr>.multiplier");
			curr    = map_params.get<float>("scene.skyx.time.<xmlattr>.current");
			sunRise    = map_params.get<float>("scene.skyx.time.<xmlattr>.sunRise");
			sunSet    = map_params.get<float>("scene.skyx.time.<xmlattr>.sunSet");
			m_skyx->setTimeMultiplier(mult);
			m_controller->setTime(Ogre::Vector3(curr, sunRise, sunSet));
		} catch (...) {
		}
		try {
			float X, Y;
			X = map_params.get<float>("scene.skyx.eastPosition.<xmlattr>.X");
			Y = map_params.get<float>("scene.skyx.eastPosition.<xmlattr>.Y");
			m_controller->setEastDirection(Ogre::Vector2(X,Y));
		} catch (...) {
		}
		try {
			Ogre::Vector3 length;
			length.x = map_params.get<float>("scene.skyx.waveLength.<xmlattr>.R");
			length.y = map_params.get<float>("scene.skyx.waveLength.<xmlattr>.G");
			length.z = map_params.get<float>("scene.skyx.waveLength.<xmlattr>.B");
			options.WaveLength = length;
		} catch (...) {
		}
		try {
			float windDir, noiseScale;
			int windSpeed;
			windSpeed = map_params.get<int>("scene.skyx.vClouds.<xmlattr>.windSpeed");
			windDir    = map_params.get<float>("scene.skyx.vClouds.<xmlattr>.windDirection");
			noiseScale = map_params.get<float>("scene.skyx.vClouds.<xmlattr>.noiseScale");
			m_skyx->getVCloudsManager()->getVClouds()->setWindSpeed(windSpeed);
			m_skyx->getVCloudsManager()->getVClouds()->setWindDirection(Ogre::Radian(windDir));
			m_skyx->getVCloudsManager()->setAutoupdate(true);
			m_skyx->getVCloudsManager()->getVClouds()->setNoiseScale(noiseScale);
			m_skyx->getVCloudsManager()->getVClouds()->setWheater(0.3, 1, false);
			m_skyx->getVCloudsManager()->setHeight(Ogre::Vector2(500,400));
			m_skyx->getVCloudsManager()->create(m_skyx->getMeshManager()->getSkydomeRadius(((ClientGameEngine*)m_map->game())->cameraManager()->camera()));
		} catch (...) {
		}
		m_skyx->getAtmosphereManager()->setOptions(options);
		m_skyx->create();
		OgreContextManager::get()->getOgreApplication()->getRoot()->addFrameListener(m_skyx);
		OgreContextManager::get()->getOgreApplication()->getWindow()->addListener(m_skyx);
	}
	catch(...) {
	}
	bounds = map_params.get_child("scene.nodes").equal_range("node");
	for(boost::property_tree::ptree::const_assoc_iterator it=bounds.first;it!=bounds.second;++it)
	{
		Ogre::SceneNode* sceneNode = m_scene_mgr->getRootSceneNode()->createChildSceneNode();
		processNode(it->second, sceneNode);
	}
}
void MapView::mapUnloaded()
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
	{
		delete m_pageGrass;
	}
	for(Forests::PagedGeometry *g : m_pages)
	{
		delete g;
	}
}
void MapView::update()
{
	if(m_pageGrass)
		m_pageGrass->update();
	for(Forests::PagedGeometry* p : m_pages)
		p->update();
	if(m_skyx)
	{
		if(m_hydrax)
			m_hydrax->setSunPosition(m_controller->getSunDirection());
		if(m_sunLight)
		{
			m_sunLight->setDirection(-m_controller->getSunDirection());
			//m_terrainGroup->update();
			//m_terrainGroup->updateDerivedData(false);
			//m_globals->setLightMapDirection(-m_controller->getSunDirection());
			//m_globals->setCastsDynamicShadows(true);
		}
	}
}
void MapView::processNode(XmlDocumentManager::Document const& n, Ogre::SceneNode* parent)
{
	bool paged = n.count("pagedgeometry")!=0;
	if(!paged)
	{
		Ogre::SceneNode *currentNode = parent->createChildSceneNode(n.get<std::string>("<xmlattr>.name"));
		Vector3D position = XmlUtils::getPosition(n.get_child("position.<xmlattr>"));
		Ogre::Quaternion rotation = XmlUtils::getQuaternion(n.get_child("rotation.<xmlattr>"));
		Vector3D scale = XmlUtils::getPosition(n.get_child("scale.<xmlattr>"));
		currentNode->setPosition(position);
		currentNode->setOrientation(rotation);
		currentNode->setScale(scale.convert<Ogre::Vector3>());
		/*
		 * Ajout des entités
		 * */
		auto bounds = n.equal_range("entity");
		for(boost::property_tree::ptree::const_assoc_iterator it = bounds.first;it!=bounds.second;++it)
		{
			std::string cast_shadow = it->second.get<std::string>("<xmlattr>.castShadows");
			std::string meshName = it->second.get<std::string>("<xmlattr>.meshFile");
			Ogre::Entity *ent = m_scene_mgr->createEntity(meshName);
			ent->setCastShadows(cast_shadow=="true");
			currentNode->attachObject(ent);
			auto boundsSub = it->second.equal_range("subentity");
			for(auto sub=boundsSub.first;sub!=boundsSub.second;++sub)
			{
				int index = boost::lexical_cast<int>(sub->second.get<int>("<xmlattr>.index"));
				ent->getSubEntity(index)->setMaterialName(sub->second.get<std::string>("materialName"));
			}
		}
		bounds = n.equal_range("node");
		for(auto it=bounds.first;it!=bounds.second;++it)
			processNode(it->second, currentNode);
	}
	else
	{
		m_scene_mgr->destroySceneNode(parent);
		std::string fileName = n.get<std::string>("pagedgeometry.<xmlattr>.fileName");
		std::string model    = n.get<std::string>("pagedgeometry.<xmlattr>.model");
		int pageSize         = n.get<int>("pagedgeometry.<xmlattr>.pageSize");
		int batchDistance    = n.get<int>("pagedgeometry.<xmlattr>.batchDistance");
		int impostorDistance = n.get<int>("pagedgeometry.<xmlattr>.impostorDistance");
		std::vector<std::string> boundsStrings;
		std::string strBounds = n.get<std::string>("pagedgeometry.<xmlattr>.bounds");
		boost::split(boundsStrings, strBounds, boost::is_any_of(" "));
		Forests::TBounds bounds(boost::lexical_cast<int>(boundsStrings[0]),
				boost::lexical_cast<int>(boundsStrings[1]),
				boost::lexical_cast<int>(boundsStrings[2]),
				boost::lexical_cast<int>(boundsStrings[3]));
		bool castShadow = n.get<std::string>("pagedgeometry.<xmlattr>.castShadows") == "true";
		Forests::PagedGeometry *pagedGeometry = new Forests::PagedGeometry(((ClientGameEngine*)m_map->game())->cameraManager()->camera(), pageSize);
		pagedGeometry->setTempDir(m_temp_dir);
		m_pages.push_back(pagedGeometry);
		pagedGeometry->addDetailLevel<Forests::BatchPage>(batchDistance);
		pagedGeometry->addDetailLevel<Forests::ImpostorPage>(impostorDistance);
		Forests::TreeLoader3D* loader = new Forests::TreeLoader3D(pagedGeometry, bounds);

		Ogre::Entity *entity = m_scene_mgr->createEntity(model);

		loadPagedFile(m_map->mapRootPath()+fileName, loader, entity);
		pagedGeometry->setPageLoader(loader);
	}
}
Ogre::Real MapView::staticGetHeightAt(Ogre::Real x, Ogre::Real z, void *map)
{
	return static_cast<MapView*>(map)->getHeightAt(x,z);
}
bool MapView::autoDelete() const
{
	return true;
}
void MapView::loadPagedFile(const std::string& path, Forests::TreeLoader3D* loader, Ogre::Entity* ent)
{
	std::ifstream file;
	file.open(path);
	std::string line;
	while(!file.eof())
	{
		std::getline(file, line);
		std::vector<std::string> firstSep;
		boost::split(firstSep, line, boost::is_any_of(";"));
		int id      = boost::lexical_cast<int>(firstSep[0]);
		float scale = boost::lexical_cast<float>(firstSep[2]);
		float yaw   = boost::lexical_cast<float>(firstSep[3]);
		Vector3D pos;
		{
			std::vector<std::string> positions;
			boost::split(positions, firstSep[1], boost::is_any_of(" "));
			pos.x = boost::lexical_cast<float>(positions[0]);
			pos.y = boost::lexical_cast<float>(positions[1]);
			pos.z = boost::lexical_cast<float>(positions[2]);
			std::cout << pos.x << std::endl;
		}
		loader->addTree(ent, pos, Ogre::Radian(yaw), scale);
	}
	file.close();
}
float MapView::getHeightAt(float x, float z) const
{
	return m_terrainGroup->getHeightAtWorldPosition(x,0,z);
}
