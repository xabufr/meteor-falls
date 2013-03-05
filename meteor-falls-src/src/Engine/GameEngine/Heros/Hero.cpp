#include "Hero.h"
#include "Avatar.h"
#include "ClasseHero.h"
#include "../Joueur/JoueurRPG.h"
#include "../Joueur/Joueur.h"
#include "../../../Utils/Physique/MotionState.h"
#include <OgreSceneManager.h>
#include <OgreEntity.h>

Hero::Hero(Ogre::SceneManager* mng, JoueurRPG *j, Avatar *a, int id, btDynamicsWorld* world):
Unite(mng, j->joueur()->equipe(), nullptr, id),
m_joueur(j),
m_avatar(a),
m_entityBody(nullptr),
m_world(world)
{
	m_avancer = m_reculer = m_droite = m_gauche = false;
	j->setHero(this);
	if(mng)
	{
		std::string meshName = a->classe()->mesh(j->joueur()->getLevel());
		m_entityBody = mng->createEntity(meshName);
		m_sceneNode->attachObject(m_entityBody);
		m_sceneNode->setScale(0.1, 0.1, 0.1);

		m_shape = new btBoxShape(btVector3(5, 5, 5));
        btVector3 inertia;
        m_shape->calculateLocalInertia(1, inertia);
        MotionState* motionState = new MotionState(m_sceneNode);
        btRigidBody::btRigidBodyConstructionInfo BodyCI(1, motionState, m_shape, inertia);
        m_body = new btRigidBody(BodyCI);
        m_world->addRigidBody(m_body);
	}
}
Hero::~Hero()
{
	m_joueur->setHero(nullptr);
	if(m_sceneManager)
		m_sceneManager->destroyEntity(m_entityBody);
}
JoueurRPG* Hero::joueur() const
{
	return m_joueur;
}
Avatar* Hero::avatar() const
{
	return m_avatar;
}
btRigidBody* Hero::getRigidBody() const
{
    return m_body;
}
void Hero::update(unsigned int time)
{
	if(m_sceneNode)
	{
		if(m_avancer)
			m_sceneNode->translate(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_LOCAL);
		else if(m_reculer)
			m_sceneNode->translate(Ogre::Vector3(0, 0, 1), Ogre::Node::TS_LOCAL);
		if(m_droite)
			m_sceneNode->translate(Ogre::Vector3(1, 0, 0), Ogre::Node::TS_LOCAL);
		else if(m_gauche)
			m_sceneNode->translate(Ogre::Vector3(-1, 0, 0), Ogre::Node::TS_LOCAL);
	}
}
void Hero::setAvancer(bool a)
{
	m_avancer=a;
}
void Hero::setReculer(bool r)
{
	m_reculer = r;
}
void Hero::setGauche(bool g)
{
	m_gauche = g;
}
void Hero::setDroite(bool d)
{
	m_droite = d;
}
