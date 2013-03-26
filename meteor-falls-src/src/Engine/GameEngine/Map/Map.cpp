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
#include "WorldObjectType.h"
#include "../GameEngine.h"


using namespace rapidxml;

Map::Map(GameEngine *game): m_game(game)
{
	m_loaded = false;
}
Map::~Map()
{
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
	m_loaded = true;
	bool server = m_game->getTypeServerClient() == GameEngine::SERVER;
	m_name = p_name;
	rapidxml::xml_document<> *map_params = getXmlMap();
	rapidxml::xml_node<>* rootNode  = map_params->first_node("scene");
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
