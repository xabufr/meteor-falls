#include "Hero.h"
#include "Avatar.h"
#include "ClasseHero.h"
#include "../Joueur/JoueurRPG.h"
#include "../Joueur/Joueur.h"
#include "../Factions/Equipe.h"
#include "../GameEngine.h"
#include "../../EngineManager/EngineManager.h"
#include "../../NetworkEngine/clientnetworkengine.h"
#include "../../EngineMessage/EngineMessage.h"

Hero::Hero(JoueurRPG *j, Avatar *a, int id):
Unite(j->joueur()->equipe(), nullptr, id),
m_joueur(j),
m_avatar(a),
m_isModified(true)
{
	m_avancer = m_reculer = m_droite = m_gauche = false;
	j->setHero(this);
}
Hero::~Hero()
{
	m_joueur->setHero(nullptr);
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
//	if(m_sceneNode) // CLIENT
//	{
//		if(m_equipe->game()->getCurrentJoueur() == this->joueur()->joueur())
//		{
//			((ClientNetworkEngine*)m_equipe->game()->getManager()->getNetwork())->sendRpgModification(!m_isModified);
//		}
//	}
	m_isModified=false;
}
void Hero::serializeComportement(EngineMessage* mess, bool all)
{
	//mess->positions[EngineMessageKey::OBJECT_POSITION] = m_sceneNode->getPosition();
	//mess->positions[EngineMessageKey::OBJECT_ROTATION] = m_sceneNode->getOrientation();
	//mess->doubles[EngineMessageKey::OBJECT_ROTATION] = m_sceneNode->getOrientation().w;
	mess->ints[EngineMessageKey::OBJECT_ID] = this->id(); 
	mess->ints[EngineMessageKey::TEAM_ID] = m_equipe->id();
	if(all)
	{
		mess->ints[EngineMessageKey::HERO_AVANCE] = static_cast<int>(m_avancer);
		mess->ints[EngineMessageKey::HERO_RECULE] = static_cast<int>(m_reculer);
		mess->ints[EngineMessageKey::HERO_GAUCHE] = static_cast<int>(m_gauche);
		mess->ints[EngineMessageKey::HERO_DROITE] = static_cast<int>(m_droite);
	}
}
void Hero::deserializeComportement(EngineMessage* mess, bool all)
{
	setPosition(mess->positions[EngineMessageKey::OBJECT_POSITION]);
	Ogre::Quaternion q;
	Vector3D axe = mess->positions[EngineMessageKey::OBJECT_ROTATION];
	q.x          = axe.x;
	q.y          = axe.y;
	q.z          = axe.z;
	q.w          = mess->doubles[EngineMessageKey::OBJECT_ROTATION];
	if(all)
	{
		m_reculer = static_cast<bool>(mess->ints[EngineMessageKey::HERO_RECULE]);
		m_avancer= static_cast<bool>(mess->ints[EngineMessageKey::HERO_AVANCE]);
		m_droite = static_cast<bool>(mess->ints[EngineMessageKey::HERO_DROITE]);
		m_gauche = static_cast<bool>(mess->ints[EngineMessageKey::HERO_GAUCHE]);
	}
}
void Hero::tournerGaucheDroite(float angle)
{
}
