#include "projectivedecalsmanager.h"

#include <OgreFrustum.h>
#include <vector>
#include <Utils/vector2d.h>
#include "MapView.h"
#include "WorldObjectView.h"
#include "WorldObject.h"

#include <Terrain/OgreTerrainGroup.h>

#include <Engine/GraphicEngine/GraphicEngine.h>

class ProjectiveDecalsManager::DecalDefinition: public WorldObjectListener {
public:

    DecalDefinition(MapView *m_mapView, const WorldObjectView* object, Ogre::SceneNode *parentNode, const ProjectiveDecalsManager::DecalProperties &properties);
    void positionChanged(const Vector3D &pos, WorldObject *sender);
    void update();
    ~DecalDefinition();
    void setProperties(const ProjectiveDecalsManager::DecalProperties &properties);

private:
    std::vector<Ogre::Terrain *> findMapParts();
    void createPassFor(Ogre::Terrain* terrain);
    void removePassFor(Ogre::Terrain* terrain);

private:
    const WorldObjectView *m_object;
    MapView *m_mapView;
    Ogre::Frustum *m_frustum;
    Ogre::SceneNode *m_node;
    std::map<Ogre::Terrain*, Ogre::Pass*> m_passes;
    ProjectiveDecalsManager::DecalProperties m_properties;
};


ProjectiveDecalsManager::ProjectiveDecalsManager(GraphicEngine *graphic, MapView *mapView) : m_mapView(mapView)
{
    m_sceneNode = graphic->getSceneManager()->getRootSceneNode()->createChildSceneNode("projective_decals");
}

void ProjectiveDecalsManager::add(const WorldObjectView *object, const ProjectiveDecalsManager::DecalProperties &properties)
{
    m_decalsObjects[object] = new DecalDefinition(m_mapView, object, m_sceneNode, properties);
}

void ProjectiveDecalsManager::remove(const WorldObjectView *object)
{
    delete m_decalsObjects[object];
    m_decalsObjects.erase(object);
}

ProjectiveDecalsManager::DecalDefinition::DecalDefinition(MapView *m_mapView, const WorldObjectView *object, Ogre::SceneNode *parentNode, const DecalProperties &properties) : m_mapView(m_mapView), m_object(object), m_properties(properties) {
    m_node = parentNode->createChildSceneNode();
    m_frustum = new Ogre::Frustum();
    m_frustum->setProjectionType(Ogre::PT_ORTHOGRAPHIC);
    m_frustum->setAspectRatio(1.f);
    m_frustum->setOrthoWindowHeight(10);
    m_frustum->setFOVy(Ogre::Degree(45));
    m_frustum->setNearClipDistance(0.1);
    m_node->attachObject(m_frustum);
    m_node->setOrientation(Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3::UNIT_X));

    update();
}

void ProjectiveDecalsManager::DecalDefinition::positionChanged(const Vector3D &pos, WorldObject *sender)
{
    update();
}

void ProjectiveDecalsManager::DecalDefinition::update()
{
    std::vector<Ogre::Terrain *> newParts = findMapParts();

    std::vector<Ogre::Terrain*> unsusedParts;

    std::for_each(m_passes.begin(), m_passes.end(), [this, &unsusedParts](std::pair<Ogre::Terrain*, Ogre::Pass*> entry) {
        unsusedParts.push_back(entry.first);
    });

    std::for_each(newParts.begin(), newParts.end(), [&](Ogre::Terrain* terrain) {
        std::remove(unsusedParts.begin(), unsusedParts.end(), terrain);
        if(m_passes.find(terrain) == m_passes.end()) {
            this->createPassFor(terrain);
        }
    });

    std::for_each(unsusedParts.begin(), unsusedParts.end(), [this] (Ogre::Terrain* terrain) {
        m_passes.erase(terrain);
        delete terrain;
    });

    m_node->setPosition(m_object->model()->position() + Ogre::Vector3(0,10,0));

    const Ogre::AxisAlignedBox boundingBox = m_object->getBoundingBox();
    m_frustum->setAspectRatio(boundingBox.getSize().x / boundingBox.getSize().z);
    m_frustum->setOrthoWindowHeight(boundingBox.getSize().z + m_properties.additionnalSize);
}

ProjectiveDecalsManager::DecalDefinition::~DecalDefinition()
{
    std::for_each(m_passes.begin(), m_passes.end(), [this](std::pair<Ogre::Terrain*, Ogre::Pass*> entry) {
        Ogre::Pass *pass = entry.second;
        pass->getParent()->removePass(pass->getIndex());
    });
    m_node->detachAllObjects();
    delete m_frustum;
    m_node->getParent()->removeChild(m_node);
}

void ProjectiveDecalsManager::DecalDefinition::setProperties(const ProjectiveDecalsManager::DecalProperties &properties)
{
    m_properties = properties;
    std::for_each(m_passes.begin(), m_passes.end(), [this](std::pair<Ogre::Terrain*, Ogre::Pass*> entry) {
        Ogre::Pass *pass = entry.second;
        pass->setAmbient(m_properties.color);
    });
}

std::vector<Ogre::Terrain *> ProjectiveDecalsManager::DecalDefinition::findMapParts()
{
    std::vector<Ogre::Terrain*> parts;

    Ogre::TerrainGroup *terrain = m_mapView->terrain();
    Ogre::TerrainGroup::TerrainIterator it = terrain->getTerrainIterator();

    std::for_each(it.begin(), it.end(), [this, &parts] (std::pair<const unsigned int, Ogre::TerrainGroup::TerrainSlot *> slot_pair) {
        Ogre::TerrainGroup::TerrainSlot *slot = slot_pair.second;
        if(slot->instance->getWorldAABB().intersects(m_object->getBoundingBox())) {
            parts.push_back(slot->instance);
        }
    });

    return parts;
}

void ProjectiveDecalsManager::DecalDefinition::createPassFor(Ogre::Terrain *terrain)
{
    Ogre::Pass *pass = terrain->getMaterial()->getTechnique(0)->createPass();
    pass->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
    pass->setDepthBias(1);
    pass->setLightingEnabled(true);
    pass->setAmbient(m_properties.color);
    Ogre::TextureUnitState *texState = pass->createTextureUnitState(m_properties.texture);
    texState->setProjectiveTexturing(true, this->m_frustum);
    texState->setTextureAddressingMode(Ogre::TextureUnitState::TAM_BORDER);
    texState->setTextureBorderColour(Ogre::ColourValue(0,0,0,0));
    texState->setTextureFiltering(Ogre::FO_POINT, Ogre::FO_LINEAR, Ogre::FO_NONE);

    m_passes[terrain] = pass;
}

void ProjectiveDecalsManager::DecalDefinition::removePassFor(Ogre::Terrain *terrain)
{
    Ogre::Pass *pass = m_passes[terrain];
    pass->getParent()->removePass(pass->getIndex());
    m_passes.erase(terrain);
}


ProjectiveDecalsManager::DecalProperties::DecalProperties()
{
    texture = "decal_circle.png";
    color = Ogre::ColourValue(0,255,0);
    additionnalSize = 2.5;
}

ProjectiveDecalsManager::DecalProperties::DecalProperties(const std::string &p_texture, const Ogre::ColourValue &p_color, float p_additionnalSize): texture(p_texture), color(p_color), additionnalSize(p_additionnalSize)
{
}
