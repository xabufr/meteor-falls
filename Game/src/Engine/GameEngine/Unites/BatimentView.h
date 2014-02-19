#ifndef H_BATIMENT_VIEW_H
#define H_BATIMENT_VIEW_H
#include "UniteView.h"

class Batiment;
class BatimentView: public UniteView
{
public:
    BatimentView(Batiment*, Ogre::SceneNode*);
    virtual void positionChanged(const Vector3D& position, WorldObject *sender);
private:
    Ogre::Entity *m_entity;
};

#endif
