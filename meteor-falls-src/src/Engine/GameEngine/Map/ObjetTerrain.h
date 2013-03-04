#ifndef OBJETTERRAIN_H
#define OBJETTERRAIN_H

#include "../../../Utils/Vector3D.h"
namespace Ogre{
    class SceneNode;
    class SceneManager;
}
class GameEngine;
class ObjetTerrain
{
    public:
        ObjetTerrain(GameEngine*, Ogre::SceneManager*);
        virtual ~ObjetTerrain();
        virtual const Vector3D& getPosition() const;
        virtual void setPosition(const Vector3D&);
        virtual Ogre::SceneNode* getNode();
    protected:
        Vector3D m_position;
        Ogre::SceneNode *m_sceneNode;
		Ogre::SceneManager* m_sceneManager;
		GameEngine *m_game;
};

#endif // OBJETTERRAIN_H
