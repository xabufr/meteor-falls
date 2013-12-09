#include "BulletRelationPtr.h"
#include <BulletCollision/CollisionDispatch/btCollisionObject.h>

BulletRelationPtr::BulletRelationPtr(btCollisionObject* obj, void *data, BulletRelationPtr::Type t):
	body(obj),
	obj_ptr(data),
	type(t)
{
 	body->setUserPointer(this);
}
