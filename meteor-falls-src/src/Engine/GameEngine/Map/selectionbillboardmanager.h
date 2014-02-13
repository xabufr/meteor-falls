#ifndef SELECTIONBILLBOARDMANAGER_H
#define SELECTIONBILLBOARDMANAGER_H

#include <map>
#include <vector>
#include <string>
#include <OgreColourValue.h>

namespace Ogre {
    class BillboardSet;
    class SceneManager;
    class SceneNode;
}
class WorldObjectView;
class MapView;
class SelectionBillboardManager
{
public:
    SelectionBillboardManager(Ogre::SceneManager *sm, MapView *mapView);
    ~SelectionBillboardManager();
    void add(WorldObjectView *view, const Ogre::ColourValue &colour = Ogre::ColourValue::White);
    void remove(WorldObjectView *view);
    void update();

private:
    Ogre::BillboardSet * getSet(const std::string &materialName);

    class InternalObjectRepresentation;
    friend class InternalObjectRepresentation;
    std::map<std::string, Ogre::BillboardSet*> m_sets;
    std::map<Ogre::BillboardSet*, std::vector<InternalObjectRepresentation*>> m_representation;

    Ogre::SceneManager *m_sm;
    MapView *m_mapView;
    Ogre::SceneNode *m_node;
};

#endif // SELECTIONBILLBOARDMANAGER_H
