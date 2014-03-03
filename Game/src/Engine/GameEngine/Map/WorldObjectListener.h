#ifndef H_WORLD_OBJECT_LISTENER_H
#define H_WORLD_OBJECT_LISTENER_H

class Vector3D;
class Quaternion;
class WorldObject;
class TimeDuration;
class WorldObjectListener
{
public:
    virtual void positionChanged(const Vector3D& pos, WorldObject* sender) { }
    virtual void rotationChanged(const Quaternion& q, WorldObject *sender) { }
    virtual void update(const TimeDuration &time, WorldObject *sender) { }
    virtual bool autoDelete()
    {
        return true;
    }
    virtual void notifyObjectDelete(WorldObject *sender) {}
    virtual ~WorldObjectListener(){}
};

#endif
