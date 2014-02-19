#include "Map.h"
#include "MapListener.h"
#include "../../ScriptEngine/XmlDocumentManager.h"

#include "WorldObject.h"
#include "WorldObjectManager.h"
#include "ObjetTerrain.h"
#include "ObjetTerrainType.h"
#include "ObjetTerrainTypeManager.h"
#include "../Factions/Equipe.h"
#include "../Unites/UniteFactory.h"
#include "../Unites/Unite.h"
#include "../../../Utils/Xml.h"
#include "../../../precompiled/lexical_cast.h"
#include "../../../Utils/Exception/FileNotFound.h"
#include "WorldObjectType.h"
#include "../GameEngine.h"

#include <bullet/btBulletDynamicsCommon.h>
#include <Bullet-C-Api.h>
#include <bullet/btBulletCollisionCommon.h>
#include <bullet/BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h>

#include "../../PhysicalEngine/BulletRelationPtr.h"

#include <cstring>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>


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
XmlDocumentManager::Document& Map::getXmlMap() const
{
    return XmlDocumentManager::get()->getDocument(mapRootPath()+ m_name + ".scene");
}
std::string Map::mapRootPath() const
{
    return "data/maps/"+m_name+"/";
}

const Rectangle<float> &Map::bounds() const
{
    return m_bounds;
}
void Map::load(const std::string& p_name)
{
    if(m_loaded)
        unload();
    m_loaded = true;
    m_name = p_name;
    XmlDocumentManager::Document &map_params = getXmlMap();
    {
        float worldSize, mapSize, compositeDistance;
        int maxPixelError, maxBatch, minBatch;
        worldSize         = map_params.get<int>("scene.terrain.<xmlattr>.worldSize");
        mapSize           = map_params.get<int>("scene.terrain.<xmlattr>.mapSize");
        maxPixelError     = map_params.get<int>("scene.terrain.<xmlattr>.tuningMaxPixelError");
        maxBatch          = map_params.get<int>("scene.terrain.<xmlattr>.tuningMaxBatchSize");
        minBatch          = map_params.get<int>("scene.terrain.<xmlattr>.tuningMinBatchSize");
        compositeDistance = map_params.get<int>("scene.terrain.<xmlattr>.tuningCompositeMapDistance");


        bool first=true;
        int minx, miny, maxx, maxy;
        minx = miny = maxx = maxy = 0;
        auto bounds = map_params.get_child("scene.terrain.terrainPages").equal_range("terrainPage");
        for(auto it=bounds.first;it!=bounds.second;++it)
        {
            int px,py;
            px = it->second.get<int>("<xmlattr>.pageX");
            py = it->second.get<int>("<xmlattr>.pageY");
            minx = (first)?px:(px<minx)?px:minx;
            miny = (first)?py:(py<miny)?py:miny;
            maxx = (first)?px:(px>maxx)?px:maxx;
            maxy = (first)?py:(py>maxy)?py:maxy;
            first = false;
        }

        int totalX = maxx - minx + 1;
        int totalY = maxy - miny + 1;

        m_bounds.width = totalX * worldSize;
        m_bounds.height = totalY * worldSize;
        m_bounds.setCenter(Vector2D<float>(0,0));

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
                m_shapes.push_back(shape);

                btRigidBody::btRigidBodyConstructionInfo BodyCI(0, nullptr, shape);
                btRigidBody *body = new btRigidBody(BodyCI);
                m_bodies.push_back(body);

                posx = worldSize*(float(x));
                posz = -(worldSize*(float(y)));
                btTransform tr;
                tr.setIdentity();
                tr.setOrigin(btVector3(0, (maxHeight-minHeight)/2, 0));// On centre l'origine au milieu, en bas

                body->setCenterOfMassTransform(tr);
                body->translate(btVector3(posx,0, posz)); // On position le terrain dans le monde
                m_world->addCollisionObject(body);

                BulletRelationPtr *lien = new BulletRelationPtr(body, this, BulletRelationPtr::Type::MAP);
                m_liensPhysique.push_back(lien);
            }
        }
    }
    {
        btStaticPlaneShape* plan = new btStaticPlaneShape(btVector3(0,1,0), 1);
        m_shapes.push_back(plan);
        btRigidBody::btRigidBodyConstructionInfo info(0, nullptr, plan);
        btRigidBody *body = new btRigidBody(info);
        body->translate(btVector3(0, -100, 0));
        m_bodies.push_back(body);
        m_world->addRigidBody(body);
        m_liensPhysique.push_back(new BulletRelationPtr(body, this, BulletRelationPtr::Type::DEATH_OBJ));
    }
    auto bounds = map_params.get_child("scene.nodes").equal_range("node");
    for(auto it = bounds.first;it!=bounds.second;++it)
        processNode(it->second);
    for(MapListener *listener: m_listeners)
    {
        listener->mapLoaded(p_name);
        for(ObjetTerrain *obj: m_objectsTerrain)
            listener->objetAdded(obj);
    }
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
    btVector3 from(x, 100000, z), to(x, -10000, z);
    btDynamicsWorld::AllHitsRayResultCallback rayTest(from, to);
    m_world->rayTest(from, to, rayTest);
    if(rayTest.hasHit())
    {
        size_t nb = rayTest.m_collisionObjects.size();
        for(size_t i=0;i<nb;++i)
        {
            if(rayTest.m_collisionObjects[i]->getUserPointer())
            {
                BulletRelationPtr *ptr = static_cast<BulletRelationPtr*>(rayTest.m_collisionObjects[i]->getUserPointer());
                if(ptr->type == BulletRelationPtr::Type::MAP)
                {
                    return rayTest.m_hitPointWorld[i].y();
                }
            }
        }
    }
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
void Map::processNode(XmlDocumentManager::Document const & node)
{
    Vector3D position = XmlUtils::getPosition(node.get_child("position.<xmlattr>"));
    bool userData = node.count("userData") > 0;
    int id = node.get<int>("<xmlattr>.id");
    bool server = m_game->getTypeServerClient()==GameEngine::SERVER;
    if(userData&&server)
    {
        char teamId;
        std::string type;
        auto bounds = node.get_child("userData").equal_range("property");
        for(auto it=bounds.first;it!=bounds.second;++it)
        {
            std::string name = it->second.get<std::string>("<xmlattr>.name");
            if(name=="type")
            {
                type = it->second.get<std::string>("<xmlattr>.data");
            }
            else if (name=="team_id")
            {
                teamId = it->second.get<int>("<xmlattr>.data");
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
                    u->setPosition(Vector3D(position.x, getHeightAt(position.x, position.z), position.z));
                }
            }
        }
    }
    else if(server)
    {
        if(node.count("pagedgeometry") != 0)
        {
            ObjetTerrainType *type = m_game->objetTerrainTypeManager()->get(node.get<std::string>("pagedgeometry.<xmlattr>.model"));
            if(type)
            {
                ObjetTerrain* obj;
                std::ifstream file;
                file.open(mapRootPath()+"/"+node.get<std::string>("pagedgeometry.<xmlattr>.fileName"));
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
                    }
                    ObjetTerrain *obj = new ObjetTerrain(m_game, type);
                    obj->nodeId = node.get<int>("<xmlattr>.id");
                    obj->paged  = true;
                    obj->setPosition(pos);
                    obj->setRotation(Quaternion::fromAngleAxis(0,1,0,yaw));
                    m_objectsTerrain.push_back(obj);
                }
                file.close();
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
    for(btRigidBody *b : m_bodies)
    {
        m_world->removeRigidBody(b);
        delete b;
    }
    for(btCollisionShape* shape : m_shapes)
        delete shape;
    m_bodies.clear();
    m_shapes.clear();
    for(MapListener *l : m_listeners)
        l->mapUnloaded();
    for(BulletRelationPtr *l : m_liensPhysique)
        delete l;
    m_liensPhysique.clear();
}
