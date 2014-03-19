#ifndef TERRESTREVIEW_H
#define TERRESTREVIEW_H
#include "UniteView.h"

class Terrestre;
namespace Ogre
{
class Entity;
class SceneNode;
}
class TerrestreView: public UniteView
{
    public:
        TerrestreView(Terrestre *terrestre, Ogre::SceneNode *node);

        void update(const TimeDuration &time, WorldObject *sender);
        void constructionFinished(WorldObject *sender);
    private:
        Ogre::Entity *m_entity;
};

#endif // TERRESTREVIEW_H
