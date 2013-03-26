#include "Map.h"
#include "MapListener.h"
#include "../../ScriptEngine/XmlDocumentManager.h"

#include "WorldObject.h"
#include "WorldObjectManager.h"
#include "../Factions/Equipe.h"
#include "../Unites/UniteFactory.h"
#include "../Unites/Unite.h"
#include "../../../Utils/Xml.h"
#include "../../../precompiled/lexical_cast.h"
#include "../../../Utils/Exception/FileNotFound.h"
#include "WorldObjectType.h"
#include "../GameEngine.h"

#include <cstring>


using namespace rapidxml;

Map::Map(GameEngine *game, btDynamicsWorld* world): m_game(game), m_world(world)
{
	m_loaded = false;
}
Map::~Map()
{
	unload();
	for(MapListener *l : m_listeners)
		if(l->autoDelete())
			delete l;
}
rapidxml::xml_document<>* Map::getXmlMap() const
{
	return XmlDocumentManager::get()->getDocument(mapRootPath()+ m_name + ".scene");
}
std::string Map::mapRootPath() const
{
	return "data/maps/"+m_name+"/";
}
void Map::load(const std::string& p_name)
{
	if(m_loaded)
		unload();
	m_loaded = true;
	bool server = m_game->getTypeServerClient() == GameEngine::SERVER;
	m_name = p_name;
	rapidxml::xml_document<> *map_params = getXmlMap();
	rapidxml::xml_node<>* rootNode  = map_params->first_node("scene");
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

		bool first=true;
		int minx, miny, maxx, maxy;
		minx = miny = maxx = maxy = 0;
		for(nodePage=nodePages->first_node("terrainPage");nodePage;nodePage=nodePage->next_sibling("terrainPage"))
		{
			int px,py;
			px = boost::lexical_cast<int>(nodePage->first_attribute("pageX")->value());
			py = boost::lexical_cast<int>(nodePage->first_attribute("pageY")->value());
			minx = (first)?px:(px<minx)?px:minx;
			miny = (first)?py:(py<miny)?py:miny;
			maxx = (first)?px:(px>maxx)?px:maxx;
			maxy = (first)?py:(py>maxy)?py:maxy;
			first = false;
		}
		for (int x=minx; x<=maxx; ++x)
		{
			for (int y=miny; y<=maxy; ++y)
			{
				std::ifstream file;
				std::string nom = "X"+boost::lexical_cast<std::string>(x)+"Y"+boost::lexical_cast<std::string>(y);
				int taille = mapSize;
				float posx, posz;
				float maxHeight=-1000, minHeight=1000;
				float *data = new float[int(taille*taille)];
				std::string path = mapRootPath();
				file.open(path+"heightmap/Page"+nom+".f32");
				if (!file)
					throw FileNotFound(path+"heightmap/Page"+nom+".f32");

				file.read((char *)(data), sizeof(float)*taille*taille);
				file.close();
				for (int i=0; i < (taille*taille); ++i)
				{
					maxHeight = (data[i]>maxHeight)?data[i]:maxHeight;
					minHeight = (data[i]<minHeight)?data[i]:minHeight;
				}
				float *dataReverse = new float[taille*taille]; //On renverse le terrain en Z
				for(int i=0;i<taille;++i)
					memcpy(dataReverse+i*taille,
							data+taille*(taille-1-i),
							sizeof(float)*taille);
				m_terrainData.push_back(dataReverse);
				delete[] data;

				btHeightfieldTerrainShape *shape = new btHeightfieldTerrainShape(taille, taille, dataReverse, btScalar(maxHeight), 1, true, false);
				shape->setLocalScaling(btVector3(worldSize/(taille-1),1,worldSize/(taille-1))); // On le met à la bonne dimention

				btRigidBody::btRigidBodyConstructionInfo BodyCI(0, nullptr, shape);
				btRigidBody *body = new btRigidBody(BodyCI);

				posx = worldSize*(float(x));
				posz = -(worldSize*(float(y)));
				btTransform tr;
				tr.setIdentity();
				tr.setOrigin(btVector3(0, (maxHeight-minHeight)/2, 0));// On centre l'origine au milieu, en bas

				body->setCenterOfMassTransform(tr);
				body->translate(btVector3(posx,0, posz)); // On position le terrain dans le monde
				m_world->addCollisionObject(body);
			}
		}
	}
	rapidxml::xml_node<>* nodes = rootNode->first_node("nodes");
	if(nodes)
	{
		rapidxml::xml_node<>* node = nodes->first_node("node");
		while(node)
		{
			processNode(node);
			node = node->next_sibling("node");
		}
	}
	for(MapListener *listener: m_listeners)
		listener->mapLoaded(p_name);
}
const std::string& Map::getName() const
{
	return m_name;
}
void Map::update()
{
	for(MapListener *listener: m_listeners)
		listener->update();
}
bool Map::getLoaded() const
{
	return m_loaded;
}
float Map::getHeightAt(float x, float z) const
{
	//return m_terrainGroup->getHeightAtWorldPosition(x,0.f,z);
	return 0.f;
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
void Map::processNode(rapidxml::xml_node<>* n)
{
	Vector3D position = XmlUtils::getPosition(n->first_node("position"));
	rapidxml::xml_node<> *userData = n->first_node("userData");
	if(userData&&m_game->getTypeServerClient()==GameEngine::SERVER)
	{
		char teamId;
		std::string type;
		rapidxml::xml_node<> *property;
		for(property = userData->first_node("property");property!=0;property=property->next_sibling("property"))
		{
			std::string name = property->first_attribute("name")->value();
			if(name=="type")
			{
				type = property->first_attribute("data")->value();
			}
			else if (name=="team_id")
			{
				teamId = boost::lexical_cast<int>(property->first_attribute("data")->value());
			}
		}
		if(!type.empty())
		{
			if(type=="team_base")
			{
				Equipe *equipe = m_game->getEquipe(teamId);
				if(equipe != nullptr)
				{
					Unite *u = equipe->factory()->create(UnitId(0));
					u->setPosition(position);
				}
			}
		}
	}
}
GameEngine* Map::game() const
{
	return m_game;
}
void Map::addListener(MapListener* li)
{
	m_listeners.push_back(li);
}
void Map::delListener(MapListener* li)
{
	for(std::list<MapListener*>::iterator it = m_listeners.begin();it!=m_listeners.end();++it)
	{
		if(*it==li)
		{
			m_listeners.erase(it);
			return;
		}
	}
}
void Map::unload()
{
	m_loaded = false;
	m_name="";
	for(WorldObject* o : m_worldObjects)
		delete o;
	for(float *data : m_terrainData)
		delete[] data;
	m_worldObjects.clear();
	m_terrainData.clear();
	for(MapListener *l : m_listeners)
		l->mapUnloaded();
}
