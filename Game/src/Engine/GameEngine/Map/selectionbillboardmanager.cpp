#include "selectionbillboardmanager.h"

#include <OgreBillboardSet.h>
#include <OgreSceneManager.h>
#include "WorldObjectView.h"
#include "WorldObject.h"
#include "MapView.h"

#include <OgreBillboard.h>
#include <OgreSceneNode.h>
#include "Map.h"
#include "WorldObjectType.h"

class SelectionBillboardManager::InternalObjectRepresentation : public WorldObjectListener{
public:
    InternalObjectRepresentation(SelectionBillboardManager *manager, Ogre::BillboardSet *set, WorldObjectView *view, const Ogre::ColourValue &colour);
    ~InternalObjectRepresentation();
    void positionChanged(const Vector3D &pos, WorldObject *sender);
    WorldObjectView *view();


private:
    Ogre::Vector3 getPositionOnMap();
    void setDirection();

private:
    Ogre::Billboard *m_billboard;
    WorldObjectView *m_view;
    SelectionBillboardManager *m_manager;
};

SelectionBillboardManager::SelectionBillboardManager(Ogre::SceneManager *sm, MapView *mapView):
    m_sm(sm), m_mapView(mapView)
{
    m_node = m_sm->getRootSceneNode()->createChildSceneNode();
}

SelectionBillboardManager::~SelectionBillboardManager()
{
    m_node->detachAllObjects();
    for(auto it = m_sets.begin(); it != m_sets.end();++it)
        m_sm->destroyBillboardSet(it->second);
    m_node->getParentSceneNode()->removeChild(m_node);
    OGRE_DELETE m_node;
}

Ogre::BillboardSet * SelectionBillboardManager::getSet(const std::string &materialName)
{
    auto it = m_sets.find(materialName);
    if(it != m_sets.end()) {
        return it->second;
    }
    Ogre::BillboardSet *newSet = m_sm->createBillboardSet();
    newSet->setBillboardType(Ogre::BBT_PERPENDICULAR_SELF);
    newSet->setCommonUpVector(Ogre::Vector3(0,0,1));
    newSet->setCommonDirection(Ogre::Vector3(0,1,0));
    newSet->setBillboardsInWorldSpace(true);
    newSet->setBillboardOrigin(Ogre::BBO_CENTER);
    newSet->setMaterialName(materialName);
    m_sets[materialName] = newSet;
    m_node->attachObject(newSet);
    return newSet;
}

void SelectionBillboardManager::add(WorldObjectView *view, const Ogre::ColourValue &colour)
{
    Ogre::BillboardSet *set = getSet(view->model()->type()->selectedMaterialName());
    m_representation[set].push_back(new SelectionBillboardManager::InternalObjectRepresentation(this, set, view, colour));
}

void SelectionBillboardManager::remove(WorldObjectView *view)
{
    for(auto it = m_representation.begin(); it != m_representation.end(); ++it) {
        it->second.erase(std::remove_if(it->second.begin(), it->second.end(), [view](SelectionBillboardManager::InternalObjectRepresentation* repr) -> bool {
                             if(repr->view() == view) {
                                 delete repr;
                                 return true;
                             }
                             return false;
                         }));
    }
}

void SelectionBillboardManager::update()
{
    std::for_each(m_sets.begin(), m_sets.end(), [](std::pair<std::string, Ogre::BillboardSet*> entry) {
        entry.second->_updateBounds();
    });
}

void SelectionBillboardManager::reset()
{
    std::for_each(m_sets.begin(), m_sets.end(), [this](std::pair<std::string, Ogre::BillboardSet*> entry) {
        Ogre::BillboardSet *set = entry.second;
        set->clear();
        m_representation[set].clear();
    });
}

Ogre::Vector3 SelectionBillboardManager::InternalObjectRepresentation::getPositionOnMap()
{
    Ogre::Vector3 position = m_view->model()->position();
    position.y = m_manager->m_mapView->getHeightAt(position.x, position.z);

    return position;
}

void SelectionBillboardManager::InternalObjectRepresentation::setDirection()
{
    Map *map = m_manager->m_mapView->map();
    Vector3D normal = map->getNormalAt(m_billboard->getPosition().x, m_billboard->getPosition().z);
    m_billboard->mDirection = -normal.convert<Ogre::Vector3>().normalisedCopy();
}

SelectionBillboardManager::InternalObjectRepresentation::InternalObjectRepresentation(SelectionBillboardManager *manager, Ogre::BillboardSet *set, WorldObjectView *view, const Ogre::ColourValue& colour):
    m_manager(manager), m_view(view)
{
    Ogre::Vector3 position = getPositionOnMap();
    m_billboard = set->createBillboard(position + Ogre::Vector3(0,0.01,0));
    m_billboard->setDimensions(m_view->getBoundingBox().getSize().x + 2, m_view->getBoundingBox().getSize().z + 2);
    m_billboard->setColour(colour);
    setDirection();
    view->model()->addListener(this);
}

SelectionBillboardManager::InternalObjectRepresentation::~InternalObjectRepresentation()
{
    Ogre::BillboardSet *set = m_billboard->mParentSet;
    set->removeBillboard(m_billboard);
    m_view->model()->removeListener(this);
}

void SelectionBillboardManager::InternalObjectRepresentation::positionChanged(const Vector3D &pos, WorldObject *sender)
{
    m_billboard->setPosition(getPositionOnMap() + Ogre::Vector3(0,0.01,0));
    setDirection();
}

WorldObjectView *SelectionBillboardManager::InternalObjectRepresentation::view()
{
    return m_view;
}
