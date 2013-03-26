#ifndef H_HERO_VIEW_H
#define H_HERO_VIEW_H
#include "../Unites/UniteView.h"

class Hero;
class HeroView: public UniteView
{
public:
	HeroView(Hero*, Ogre::SceneNode*);
	virtual void update(float time);
	virtual void positionChanged(const Vector3D& p);
	virtual void rotationChanged(const Quaternion& q);
private:
	Hero *m_hero;
	Ogre::Entity *m_entBody;
};

#endif 
