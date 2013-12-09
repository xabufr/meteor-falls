#include "Quaternion.h"
#include <bullet/LinearMath/btQuaternion.h>
#include <OgreQuaternion.h>

Quaternion::Quaternion()
{
}
Quaternion::Quaternion(double w, double x, double y, double z): Ogre::Quaternion(x,y,z,w)
{
}
Quaternion::Quaternion(const Ogre::Quaternion& q): Ogre::Quaternion(q)
{
}
Quaternion::Quaternion(const btQuaternion& q): Ogre::Quaternion(q.w(), q.x(), q.y(), q.z())
{
}
Quaternion::operator btQuaternion() const
{
	return btQuaternion(x,y,z,w);
}
Quaternion Quaternion::fromAngleAxis(double x, double y, double z, double angle)
{
	return fromAngleAxis(Vector3D(x,y,z), angle);
}
Quaternion Quaternion::fromAngleAxis(const Vector3D& vec, double angle)
{
	return Ogre::Quaternion(Ogre::Radian(angle), vec);
}
