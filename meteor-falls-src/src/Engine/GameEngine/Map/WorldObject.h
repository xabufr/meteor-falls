#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H
#include <list>
#include "../../../Utils/Vector3D.h"
#include "../../../Utils/Quaternion.h"
#include <bullet/btBulletCollisionCommon.h>

class GameEngine;
class WorldObjectListener;
class WorldObjectView;
class WorldObjectType;
struct BulletRelationPtr;
class WorldObject
{
    public:
        WorldObject(GameEngine*, WorldObjectType*);
        virtual ~WorldObject();

        virtual void setPosition(const Vector3D&);
        const Vector3D& position() const;
        void setRotation(const Quaternion&);
        const Quaternion& rotation() const;
        const WorldObjectType* type() const;

        virtual void update(float time);

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
    private:
        WorldObjectType *m_type;
};

#endif // WORLDOBJECT_H
