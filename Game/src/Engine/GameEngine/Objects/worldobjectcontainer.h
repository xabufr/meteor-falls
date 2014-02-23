#ifndef WORLDOBJECTCONTAINER_H
#define WORLDOBJECTCONTAINER_H

#include <list>
#include "../Map/WorldObjectListener.h"

class WorldObject;
class WorldObjectContainer: public WorldObjectListener
{
public:
    WorldObjectContainer();
    WorldObject *findById(unsigned int id);
    void addObject(WorldObject *object);
    void removeObject(WorldObject *object);
    virtual bool autoDelete();
    virtual void notifyObjectDelete(WorldObject *sender);

private:
    std::list<WorldObject*> m_objects;
};

#endif // WORLDOBJECTCONTAINER_H
