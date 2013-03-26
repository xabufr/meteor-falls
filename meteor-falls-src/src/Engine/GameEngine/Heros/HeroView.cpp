#include "HeroView.h"
#include "Hero.h"
#include "Avatar.h"
#include "ClasseHero.h"
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include "../../../Utils/Quaternion.h"

HeroView::HeroView(Hero* hero, Ogre::SceneNode* node): UniteView(hero, node), m_hero(hero)
{
	Avatar* av = hero->avatar();
	m_entBody = m_node->getCreator()->createEntity(av->classe()->mesh(1)->mesh);
	m_node->attachObject(m_entBody);
	m_node->setScale(0.01, 0.01, 0.01);
}
void HeroView::update(float time)
{
}
void HeroView::positionChanged(const Vector3D& position)
{
	m_node->setPosition(position);
}
void HeroView::rotationChanged(const Quaternion& q)
{
	m_node->setOrientation(q);
}
