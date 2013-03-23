#ifndef H_QUATERNION_H
#define H_QUATERNION_H
#include <OgreQuaternion.h>
#include "Vector3D.h"

class btQuaternion;
class Quaternion: public Ogre::Quaternion
{
public:
	Quaternion();
	Quaternion(double w, double x, double y, double z);
	Quaternion(const Ogre::Quaternion&);
	Quaternion(const btQuaternion&);
	operator btQuaternion() const;
	static Quaternion fromAngleAxis(double x, double y, double z, double angle);
	static Quaternion fromAngleAxis(const Vector3D& vec, double angle);
};

#endif 
