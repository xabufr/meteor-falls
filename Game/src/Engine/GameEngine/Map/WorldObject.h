#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H
#include <list>
#include "../../../Utils/Vector3D.h"
#include "../../../Utils/Quaternion.h"
#include <bullet/LinearMath/btMotionState.h>

class GameEngine;
class WorldObjectListener;
class WorldObjectView;
class WorldObjectType;
class TimeDuration;
struct BulletRelationPtr;
class WorldObject: public btMotionState
{
    public:
        WorldObject(GameEngine*, WorldObjectType*, int id);
        virtual ~WorldObject();

        virtual void teleport(const Vector3D&);
        void setPosition(const Vector3D &position);
        const Vector3D& position() const;
        void setRotation(const Quaternion&);
        const Quaternion& rotation() const;
        const WorldObjectType* type() const;
        int id() const;

        virtual void update(const TimeDuration &duration);

        void addListener(WorldObjectListener*);
        void removeListener(const WorldObjectListener *listener);
        WorldObjectView* view() const;
        virtual bool destroyNeeded() const;
    protected:
        void notify();
        GameEngine *m_game;
        Vector3D m_position;
        Quaternion m_rotation;
        BulletRelationPtr *m_relationPtr;
        btRigidBody *m_body;
        std::list<WorldObjectListener*> m_listeners;
        int m_id;

    private:
        WorldObjectType *m_type;

        // btMotionState interface
public:
        virtual void getWorldTransform(btTransform &worldTrans) const override;
        virtual void setWorldTransform(const btTransform &worldTrans) override;
};

#endif // WORLDOBJECT_H
