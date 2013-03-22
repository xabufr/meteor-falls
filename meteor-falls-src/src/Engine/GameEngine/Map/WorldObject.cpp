#include "WorldObject.h"
#include "WorldObjectType.h"
#include "WorldObjectListener.h"

WorldObject::WorldObject(GameEngine* g, WorldObjectType* type):
    m_type(type)
{
}
WorldObject::~WorldObject()
{
}
void WorldObject::setPosition(const Vector3D& vec)
{
    m_position=vec;
}
void WorldObject::notify()
{
	for(WorldObjectListener *listener : m_listeners)
		listener->update();
}
const Vector3D& WorldObject::position() const
{
	return m_position;
}
