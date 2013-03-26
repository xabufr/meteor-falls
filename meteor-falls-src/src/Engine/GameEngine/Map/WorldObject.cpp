#include "WorldObject.h"
#include "WorldObjectType.h"
#include "WorldObjectListener.h"

WorldObject::WorldObject(GameEngine* g, WorldObjectType* type):
    m_type(type)
{
}
WorldObject::~WorldObject()
{
	for(WorldObjectListener* l : m_listeners)
		if(l->autoDelete())
			delete l;
}
void WorldObject::addListener(WorldObjectListener *l)
{
	m_listeners.push_back(l);
}
void WorldObject::setPosition(const Vector3D& vec)
{
    m_position=vec;
	for(WorldObjectListener *l : m_listeners)
		l->positionChanged(vec);

}
void WorldObject::update(float time)
{
	for(WorldObjectListener *listener : m_listeners)
		listener->update(time);
}
const Vector3D& WorldObject::position() const
{
	return m_position;
}
WorldObjectType* WorldObject::type() const
{
	return m_type;
}
void WorldObject::setRotation(const Quaternion& q)
{
	m_rotation = q;
	for(WorldObjectListener *l : m_listeners)
		l->rotationChanged(q);
}
const Quaternion& WorldObject::rotation() const
{
	return m_rotation;
}
