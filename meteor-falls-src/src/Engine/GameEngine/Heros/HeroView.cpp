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
	m_avancer = m_reculer = m_droite = m_gauche = false;
	Avatar* av = hero->avatar();
	m_entBody = m_node->getCreator()->createEntity(av->classe()->mesh(1)->mesh);
	m_entBody->setCastShadows(true);
	m_node->attachObject(m_entBody);
	m_node->setScale(0.01, 0.01, 0.01);
	m_animAvancer = m_entBody->getAnimationState(av->classe()->mesh(1)->walk);
	m_animJump = m_entBody->getAnimationState("JumpNoHeight");
	Ogre::AnimationStateSet *anims = m_entBody->getAllAnimationStates();
	auto it = anims->getAnimationStateIterator().begin();
	while(it!=anims->getAnimationStateIterator().end())
	{
		std::cout << it->first << std::endl;
		++it;
	}
}
void HeroView::update(float time)
{
	std::cout << time << std::endl;
	if(m_avancer && !m_animAvancer->getEnabled())
	{
		m_animAvancer->setEnabled(true);
		m_animAvancer->setLoop(true);
		m_animAvancer->setTimePosition(0);
	}
	else if(!m_avancer)
	{
		m_animAvancer->setEnabled(false);
	}
	else if(m_avancer)
	{
		m_animAvancer->addTime(time);
	}
	m_animJump->addTime(time);
}
void HeroView::positionChanged(const Vector3D& position)
{
	m_node->setPosition(position);
}
void HeroView::rotationChanged(const Quaternion& q)
{
	m_node->setOrientation(q);
}
void HeroView::avancer(bool a)
{
	m_avancer = a;
}
void HeroView::reculer(bool r)
{
	m_reculer = r;
}
void HeroView::droite(bool d)
{
	m_droite = d;
}
void HeroView::gauche(bool g)
{
	m_gauche = g;
}
void HeroView::sauter()
{
	m_animJump->setEnabled(true);
	m_animJump->setLoop(true);
}
