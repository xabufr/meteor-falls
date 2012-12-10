#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include "ObjetTerrain.h"

class WorldObjectType;
namespace Ogre{
    class Entity;
}
class WorldObject : public ObjetTerrain
{
    public:
        WorldObject(Ogre::SceneManager*, WorldObjectType*);
        virtual ~WorldObject();
        virtual WorldObjectType* getType() const;

        virtual void setPosition(const Vector3D&);
    protected:
    private:
        WorldObjectType *m_type;
        Ogre::Entity *m_entity;
};

#endif // WORLDOBJECT_H
