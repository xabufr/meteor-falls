#ifndef OBJETTERRAIN_H
#define OBJETTERRAIN_H

#include "../../../Utils/Vector3D.h"
namespace Ogre{
    class SceneNode;
    class SceneManager;
}
class ObjetTerrain
{
    public:
        ObjetTerrain(Ogre::SceneManager*);
        virtual ~ObjetTerrain();
        virtual const Vector3D& getPosition() const;
        virtual void setPosition(const Vector3D&);
        virtual Ogre::SceneNode* getNode();
    protected:
        Vector3D m_position;
        Ogre::SceneNode *m_sceneNode;
};

#endif // OBJETTERRAIN_H
