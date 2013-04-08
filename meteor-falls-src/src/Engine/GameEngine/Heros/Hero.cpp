#include "Hero.h"
#include "Avatar.h"
#include "ClasseHero.h"
#include "../Joueur/JoueurRPG.h"
#include "../Joueur/Joueur.h"
#include "../../../Utils/Physique/MotionState.h"
#include "../Factions/Equipe.h"
#include "../GameEngine.h"
#include "../../EngineManager/EngineManager.h"
#include "../../NetworkEngine/clientnetworkengine.h"
#include "../../EngineMessage/EngineMessage.h"

Hero::Hero(JoueurRPG *j, Avatar *a,  int id):
Unite(j->joueur()->equipe(), nullptr, id),
m_joueur(j),
m_avatar(a),
m_world(j->joueur()->equipe()->game()->bulletWorld()),
m_isModified(true)
{
	btVector3 vect(0,0,0);
	m_avancer = m_reculer = m_droite = m_gauche = false;
	j->setHero(this);

	btTransform startTransform;
    startTransform.setIdentity();
    startTransform.setOrigin (vect);

    m_ghost_object = new btPairCachingGhostObject();
    m_ghost_object->setWorldTransform(startTransform);

    btScalar characterHeight=1;

    btScalar characterWidth =1;

    btConvexShape* capsule = new btCapsuleShape(characterWidth, characterHeight);
    m_ghost_object->setCollisionShape (capsule);
    m_ghost_object->setCollisionFlags (btCollisionObject::CF_CHARACTER_OBJECT);
    m_world->getBroadphase()->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());

    btScalar stepHeight = btScalar(1);

    m_character_controller = new btKinematicCharacterController(m_ghost_object, capsule, stepHeight);
    m_character_controller->setMaxSlope(btScalar(0.872664626));  // 50°

    m_world->addCollisionObject(m_ghost_object, btBroadphaseProxy::CharacterFilter, btBroadphaseProxy::StaticFilter|btBroadphaseProxy::DefaultFilter);
    m_world->addAction(m_character_controller);
    m_world->getDispatchInfo().m_allowedCcdPenetration=0.0001f;
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
	Vector3D dep;
	if(m_avancer||m_reculer||m_droite||m_gauche)
	{
		if(m_reculer)
			dep.z = 1;
		else if(m_avancer)
			dep.z = -1;
		if(m_droite)
			dep.x = 1;
		else if(m_gauche)
			dep.x       = -1;
		dep = m_rotation * dep;
	}
	m_character_controller->setWalkDirection(dep);
	if(m_isModified)
	{
		m_comportementModifie();
		m_isModified=false;
	}
	setPosition(m_ghost_object->getWorldTransform().getOrigin());
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
	//if(m_sceneNode) // CLIENT
	//{
//		if(m_equipe->game()->getCurrentJoueur() == this->joueur()->joueur())
//		{
//			((ClientNetworkEngine*)m_equipe->game()->getManager()->getNetwork())->sendRpgModification(!m_isModified);
//		}
//	}
}
void Hero::serializeComportement(EngineMessage* mess, bool all)
{
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
	setRotation(m_rotation * Quaternion::fromAngleAxis(0,1,0,angle));
}
void Hero::m_move(const btVector3& vect)
{
    m_character_controller->setWalkDirection(vect);
    Vector3D ogre_vect;
    ogre_vect = m_ghost_object->getWorldTransform().getOrigin();
}
void Hero::setPosition(const Vector3D& pos)
{
	m_character_controller->warp(pos);
	WorldObject::setPosition(pos);
}
