#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H
#include <list>
#include "../../../Utils/Vector3D.h"

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
    protected:
		void notify();
		GameEngine *m_game;
		Vector3D m_position;
	private:
		std::list<WorldObjectListener*> m_listeners;
		WorldObjectType *m_type;
};

#endif // WORLDOBJECT_H
