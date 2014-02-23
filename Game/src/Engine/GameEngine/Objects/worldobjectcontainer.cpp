#include "worldobjectcontainer.h"
#include "../Map/WorldObject.h"
#include <algorithm>

WorldObjectContainer::WorldObjectContainer()
{
}

WorldObject *WorldObjectContainer::findById(unsigned int id)
{
    for(WorldObject *object : m_objects)
        if(object->id() == id)
            return object;
    return nullptr;
}

void WorldObjectContainer::addObject(WorldObject *object)
{
    m_objects.push_back(object);
    object->addListener(this);
}

void WorldObjectContainer::removeObject(WorldObject *object)
{
    m_objects.remove(object);
}

bool WorldObjectContainer::autoDelete()
{
    return false;
}

void WorldObjectContainer::notifyObjectDelete(WorldObject *sender)
{
    removeObject(sender);
}
