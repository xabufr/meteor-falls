#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H
#include <list>
#include "../../../Utils/Vector3D.h"
#include "../../../Utils/Quaternion.h"

class GameEngine;
class WorldObjectListener;
class WorldObjectType;
class WorldObject
{
    public:
        WorldObject(GameEngine*, WorldObjectType*);
        virtual ~WorldObject();

        void setPosition(const Vector3D&);
		const Vector3D& position() const;
		void setRotation(const Quaternion&);
		const Quaternion& rotation() const;
		WorldObjectType* type() const;

		virtual void update(float time);

		void addListener(WorldObjectListener*);
    protected:
		void notify();
		GameEngine *m_game;
		Vector3D m_position;
		Quaternion m_rotation;
	private:
		std::list<WorldObjectListener*> m_listeners;
		WorldObjectType *m_type;
};

#endif // WORLDOBJECT_H
