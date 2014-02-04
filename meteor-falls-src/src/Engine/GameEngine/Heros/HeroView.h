#ifndef H_HERO_VIEW_H
#define H_HERO_VIEW_H
#include "../Unites/UniteView.h"
#include "HeroListener.h"
#include <SFML/System/Clock.hpp>
#include "../../ScriptEngine/MeshManager.h"

class Hero;
namespace Ogre {
    class AnimationState;
} // namespace Ogre
class HeroView: virtual public HeroListener, virtual public UniteView
{
public:
    HeroView(Hero*, Ogre::SceneNode*);
    virtual void update(float time, WorldObject *sender);
    virtual void positionChanged(const Vector3D& p, WorldObject *sender);
    virtual void rotationChanged(const Quaternion& q, WorldObject *sender);
    virtual void avancer(bool);
    virtual void reculer(bool);
    virtual void droite(bool);
    virtual void gauche(bool);
    virtual void sauter();
private:
    Hero *m_hero;
    Ogre::Entity *m_entBody;
    bool m_avancer, m_reculer, m_droite, m_gauche, m_saute, m_tombe;
    Ogre::AnimationState *m_animAvancer, *m_animJump, *m_animTombe;
    MeshManager::Mesh *m_mesh;
};

#endif
