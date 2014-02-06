#include "projectivedecalsmanager.h"

#include <OgreFrustum.h>
#include <vector>
#include <Utils/vector2d.h>
#include "MapView.h"
#include "WorldObjectView.h"
#include "WorldObject.h"

#include <Terrain/OgreTerrainGroup.h>

#include <Engine/GraphicEngine/GraphicEngine.h>

class ProjectiveDecalsManager::ViewDecalDefinition: public WorldObjectListener, public BasicDecalDefinition {
public:

    ViewDecalDefinition(MapView *m_mapView, const WorldObjectView* object, Ogre::SceneNode *parentNode, const ProjectiveDecalsManager::DecalProperties &properties);
    void positionChanged(const Vector3D &pos, WorldObject *sender);
    ~ViewDecalDefinition();

protected:
        virtual Vector2D<float> getSize() const;
        virtual Vector2D<float> getPosition() const;
        virtual Ogre::AxisAlignedBox getBoundingBox() const;

private:
    const WorldObjectView *m_object;
};


ProjectiveDecalsManager::ProjectiveDecalsManager(GraphicEngine *graphic, MapView *mapView) : m_mapView(mapView)
{
    m_sceneNode = graphic->getSceneManager()->getRootSceneNode()->createChildSceneNode("projective_decals");
}

void ProjectiveDecalsManager::add(const WorldObjectView *object, const ProjectiveDecalsManager::DecalProperties &properties)
{
    ProjectiveDecalsManager::BasicDecalDefinition *projection = new ViewDecalDefinition(m_mapView, object, m_sceneNode, properties);
    projection->update();
    m_decalsObjects[(void*)object] = projection;
}

void ProjectiveDecalsManager::remove(const WorldObjectView *object)
{
    delete m_decalsObjects[object];
    m_decalsObjects.erase(object);
}

ProjectiveDecalsManager::BasicDecalDefinition *ProjectiveDecalsManager::addSimple(const ProjectiveDecalsManager::DecalProperties &properties)
{
    ProjectiveDecalsManager::BasicDecalDefinition *projection = new BasicDecalDefinition(m_mapView, m_sceneNode, properties);
    projection->update();
    m_decalsObjects[(void*)projection] = projection;
    return projection;
}

void ProjectiveDecalsManager::remove(ProjectiveDecalsManager::BasicDecalDefinition *definition)
{
    delete definition;
    m_decalsObjects.erase((void*) definition);
}

ProjectiveDecalsManager::ViewDecalDefinition::ViewDecalDefinition(
        MapView *m_mapView, const WorldObjectView *object, Ogre::SceneNode *parentNode, const DecalProperties &properties):
    ProjectiveDecalsManager::BasicDecalDefinition(m_mapView, parentNode, properties),
    m_object(object) {
}

void ProjectiveDecalsManager::ViewDecalDefinition::positionChanged(const Vector3D &pos, WorldObject *sender)
{
    ProjectiveDecalsManager::BasicDecalDefinition::update();
}

ProjectiveDecalsManager::ViewDecalDefinition::~ViewDecalDefinition()
{

}

Vector2D<float> ProjectiveDecalsManager::ViewDecalDefinition::getSize() const
{
    const Ogre::AxisAlignedBox &box = m_object->getBoundingBox();
    return Vector2D<float> (box.getSize().x, box.getSize().z);
}

Vector2D<float> ProjectiveDecalsManager::ViewDecalDefinition::getPosition() const
{
    return Vector2D<float>(m_object->model()->position().x, m_object->model()->position().z);
}

Ogre::AxisAlignedBox ProjectiveDecalsManager::ViewDecalDefinition::getBoundingBox() const
{
    return m_object->getBoundingBox();
}

void ProjectiveDecalsManager::BasicDecalDefinition::update()
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
        removePassFor(terrain);
    });

    m_node->setPosition(Ogre::Vector3(getPosition().x, 10000, getPosition().y));

    m_frustum->setAspectRatio(getSize().x / getSize().y);
    m_frustum->setOrthoWindowHeight(getSize().y + m_properties.additionnalSize);
}

Vector2D<float> ProjectiveDecalsManager::BasicDecalDefinition::getSize() const
{
    return m_properties.size;
}

Vector2D<float> ProjectiveDecalsManager::BasicDecalDefinition::getPosition() const
{
    return m_properties.position;
}

Ogre::AxisAlignedBox ProjectiveDecalsManager::BasicDecalDefinition::getBoundingBox() const
{
    float minX = std::min(getPosition().x, getPosition().x + getSize().x);
    float minY = std::min(getPosition().y, getPosition().x + getSize().y);
    float maxX = std::max(getPosition().x, getPosition().x + getSize().x);
    float maxY = std::max(getPosition().y, getPosition().x + getSize().y);
    Ogre::Vector3 begin(minX, -99999, minY);
    Ogre::Vector3 end (maxX, 999999, maxY);
    Ogre::AxisAlignedBox box(begin, end);
    return box;
}

ProjectiveDecalsManager::BasicDecalDefinition::~BasicDecalDefinition()
{
    std::for_each(m_passes.begin(), m_passes.end(), [this](std::pair<Ogre::Terrain*, Ogre::Pass*> entry) {
        Ogre::Pass *pass = entry.second;
        pass->getParent()->removePass(pass->getIndex());
    });
    m_node->detachAllObjects();
    delete m_frustum;
    m_node->getParent()->removeChild(m_node);
}

void ProjectiveDecalsManager::BasicDecalDefinition::setVisible(bool visible)
{
    m_node->setVisible(visible);
}

std::vector<Ogre::Terrain *> ProjectiveDecalsManager::BasicDecalDefinition::findMapParts()
{
    std::vector<Ogre::Terrain*> parts;

    Ogre::TerrainGroup *terrain = m_mapView->terrain();
    Ogre::TerrainGroup::TerrainIterator it = terrain->getTerrainIterator();

    Ogre::AxisAlignedBox box(getBoundingBox());
    std::for_each(it.begin(), it.end(), [this, &parts, &box] (std::pair<const unsigned int, Ogre::TerrainGroup::TerrainSlot *> slot_pair) {
        Ogre::TerrainGroup::TerrainSlot *slot = slot_pair.second;
        if(slot->instance->getWorldAABB().intersects(box)) {
            parts.push_back(slot->instance);
        }
    });

    return parts;
}

void ProjectiveDecalsManager::BasicDecalDefinition::createPassFor(Ogre::Terrain *terrain)
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

void ProjectiveDecalsManager::BasicDecalDefinition::removePassFor(Ogre::Terrain *terrain)
{
    if(m_passes.find(terrain) != m_passes.end()) {
        Ogre::Pass *pass = m_passes[terrain];
        pass->getParent()->removePass(pass->getIndex());
        m_passes.erase(terrain);
    }
}


ProjectiveDecalsManager::DecalProperties::DecalProperties()
{
    texture = "decal_circle.png";
    color = Ogre::ColourValue(0,255,0);
    additionnalSize = 2.5;
    size = Vector2D<float>(10,10);
}

ProjectiveDecalsManager::DecalProperties::DecalProperties(
        const std::string &p_texture, const Ogre::ColourValue &p_color, float p_additionnalSize):
    texture(p_texture), color(p_color), additionnalSize(p_additionnalSize)
{
}


ProjectiveDecalsManager::BasicDecalDefinition::BasicDecalDefinition(
        MapView *m_mapView, Ogre::SceneNode *parentNode, const ProjectiveDecalsManager::DecalProperties &properties):
    m_mapView(m_mapView), m_properties(properties)
{
    m_node = parentNode->createChildSceneNode();
    m_frustum = new Ogre::Frustum();
    m_frustum->setProjectionType(Ogre::PT_ORTHOGRAPHIC);
    m_frustum->setAspectRatio(1.f);
    m_frustum->setOrthoWindowHeight(10);
    m_frustum->setFOVy(Ogre::Degree(45));
    m_frustum->setNearClipDistance(0.1);
    m_node->attachObject(m_frustum);
    m_node->setOrientation(Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3::UNIT_X));
}

void ProjectiveDecalsManager::BasicDecalDefinition::setProperties(const ProjectiveDecalsManager::DecalProperties &properties)
{
    m_properties = properties;
    std::for_each(m_passes.begin(), m_passes.end(), [this](std::pair<Ogre::Terrain*, Ogre::Pass*> entry) {
        Ogre::Pass *pass = entry.second;
        pass->setAmbient(m_properties.color);
    });
}

ProjectiveDecalsManager::DecalProperties &ProjectiveDecalsManager::BasicDecalDefinition::getProperties()
{
    return m_properties;
}
