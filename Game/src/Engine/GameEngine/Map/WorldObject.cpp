#include "WorldObject.h"
#include "WorldObjectType.h"
#include "WorldObjectListener.h"
#include "../../PhysicalEngine/BulletRelationPtr.h"
#include "../GameEngine.h"
#include "WorldObjectView.h"

WorldObject::WorldObject(GameEngine* g, WorldObjectType* type, int id):
    m_type(type), m_body(nullptr), m_id(id)
{
    m_relationPtr = nullptr;
}
WorldObject::~WorldObject()
{
    for(WorldObjectListener* l : m_listeners) {
        if(l->autoDelete())
            delete l;
        else
            l->notifyObjectDelete(this);
    }
    delete m_relationPtr;
    if(m_body)
    {
        m_game->bulletWorld()->removeRigidBody(m_body);
        delete m_body;
    }
}
void WorldObject::addListener(WorldObjectListener *l)
{
    m_listeners.push_back(l);
}

void WorldObject::removeListener(const WorldObjectListener *listener)
{
    m_listeners.erase(std::remove(m_listeners.begin(), m_listeners.end(), listener));
}

WorldObjectView *WorldObject::view() const
{
    for(WorldObjectListener* listener : m_listeners) {
        WorldObjectView *view = dynamic_cast<WorldObjectView*>(listener);
        if(view)
            return view;
    }
    return nullptr;
}
void WorldObject::setPosition(const Vector3D& vec)
{
    m_position=vec;
    if (m_body!=nullptr)
        m_body->translate(btVector3(vec.x, vec.y, vec.z));
    for(WorldObjectListener *l : m_listeners)
        l->positionChanged(vec, this);

}
void WorldObject::update(const TimeDuration &duration)
{
    for(WorldObjectListener *listener : m_listeners)
        listener->update(duration, this);
}
const Vector3D& WorldObject::position() const
{
    return m_position;
}
const WorldObjectType* WorldObject::type() const
{
    return m_type;
}

int WorldObject::id() const
{
    return m_id;
}
void WorldObject::setRotation(const Quaternion& q)
{
    m_rotation = q;
    for(WorldObjectListener *l : m_listeners)
        l->rotationChanged(q, this);
}
const Quaternion& WorldObject::rotation() const
{
    return m_rotation;
}
bool WorldObject::destroyNeeded() const
{
    return false;
}
