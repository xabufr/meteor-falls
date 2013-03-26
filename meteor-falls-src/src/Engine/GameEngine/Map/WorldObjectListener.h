#ifndef H_WORLD_OBJECT_LISTENER_H
#define H_WORLD_OBJECT_LISTENER_H

class Vector3D;
class Quaternion;
class WorldObjectListener
{
public:
	virtual void positionChanged(const Vector3D& pos) { }
	virtual void rotationChanged(const Quaternion& q) { }
	virtual void update(float time) { }
	virtual bool autoDelete() 
	{
		return true;
	}
	virtual ~WorldObjectListener(){}
};

#endif 
