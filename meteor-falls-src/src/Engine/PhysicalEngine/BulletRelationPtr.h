#ifndef H_BULLET_RELATION_PTR_H
#define H_BULLET_RELATION_PTR_H

class btCollisionObject;
struct BulletRelationPtr
{
	btCollisionObject *body;
	void *obj_ptr;
	enum class Type{
		UNITE,
		MAP,
		DEATH_OBJ,
		ARME,
	} type;
	BulletRelationPtr(btCollisionObject* obj, void* ptr, Type type);
};

#endif 
