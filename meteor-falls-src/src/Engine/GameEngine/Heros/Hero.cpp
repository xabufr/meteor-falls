#include "Hero.h"
#include "Avatar.h"
#include "ClasseHero.h"
#include "../Joueur/JoueurRPG.h"
#include "../Joueur/Joueur.h"
#include "../Factions/Equipe.h"
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include "../GameEngine.h"
#include "../../EngineManager/EngineManager.h"
#include "../../NetworkEngine/clientnetworkengine.h"
#include "../../EngineMessage/EngineMessage.h"

Hero::Hero(Ogre::SceneManager* mng, JoueurRPG *j, Avatar *a, int id):
Unite(mng, j->joueur()->equipe(), nullptr, id),
m_joueur(j),
m_avatar(a),
m_entityBody(nullptr),
m_isModified(true)
{
	m_avancer = m_reculer = m_droite = m_gauche = false;
	j->setHero(this);
	if(mng)
	{
		std::string meshName = a->classe()->mesh(j->joueur()->getLevel());
		m_entityBody = mng->createEntity(meshName);
		m_sceneNode->attachObject(m_entityBody);
		m_sceneNode->setScale(0.1, 0.1, 0.1);
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
	m_comportementModifie();
}
void Hero::setAvancer(bool a)
{
	if(m_avancer!=a)
		m_isModified=true;
	m_avancer=a;
}
void Hero::setReculer(bool r)
{
	if(m_reculer!=r)
		m_isModified=true;
	m_reculer = r;
}
void Hero::setGauche(bool g)
{
	if(m_gauche!=g)
		m_isModified=true;
	m_gauche = g;
}
void Hero::setDroite(bool d)
{
	if(m_droite!=d)
		m_isModified=true;
	m_droite = d;
}
void Hero::m_comportementModifie()
{
	if(m_sceneNode) // CLIENT
	{
		if(m_equipe->game()->getCurrentJoueur() == this->joueur()->joueur())
		{
			((ClientNetworkEngine*)m_equipe->game()->getManager()->getNetwork())->sendRpgModification(!m_isModified);
		}
	}
	else  // SERVEUR
	{
	
	}
	m_isModified=false;
}
void Hero::serializeComportement(EngineMessage* mess)
{
	mess->positions[EngineMessageKey::OBJECT_POSITION] = m_sceneNode->getPosition();
	mess->ints[EngineMessageKey::OBJECT_ID] = this->id(); 
	mess->ints[EngineMessageKey::TEAM_ID] = m_equipe->id();
	mess->ints[EngineMessageKey::HERO_AVANCE] = static_cast<int>(m_avancer);
	mess->ints[EngineMessageKey::HERO_RECULE] = static_cast<int>(m_reculer);
	mess->ints[EngineMessageKey::HERO_GAUCHE] = static_cast<int>(m_gauche);
	mess->ints[EngineMessageKey::HERO_DROITE] = static_cast<int>(m_droite);
}
void Hero::deserializeComportement(EngineMessage* mess)
{
	setPosition(mess->positions[EngineMessageKey::OBJECT_POSITION]);
	m_reculer = static_cast<bool>(mess->ints[EngineMessageKey::HERO_RECULE]);
	m_avancer= static_cast<bool>(mess->ints[EngineMessageKey::HERO_AVANCE]);
	m_droite = static_cast<bool>(mess->ints[EngineMessageKey::HERO_DROITE]);
	m_gauche = static_cast<bool>(mess->ints[EngineMessageKey::HERO_GAUCHE]);
}
