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

#include "../../PhysicalEngine/BulletRelationPtr.h"
#include "HeroListener.h"

#include <Utils/timeduration.h>

class HeroController: public btKinematicCharacterController
{
public:
    HeroController(btPairCachingGhostObject* g, btConvexShape* shape, btScalar h, int up=1): btKinematicCharacterController(g,shape,h,up)
    {
    }
    btScalar verticalVelocity() const
    {
        return m_verticalVelocity;
    }
};
Hero::Hero(JoueurRPG *j, Avatar *a,  int id):
Unite(j->joueur()->equipe(), nullptr, id),
m_joueur(j),
m_avatar(a),
m_world(j->joueur()->equipe()->game()->bulletWorld()),
m_isModified(true)
{
    m_lastVerticalVelocity = 0.f;
    m_avancer = m_reculer = m_droite = m_gauche = false;
    j->setHero(this);


    m_ghost_object = new btPairCachingGhostObject();
    m_relationPtr = new BulletRelationPtr(m_ghost_object, this, BulletRelationPtr::Type::UNITE);

    btScalar characterHeight=1;

    btScalar characterWidth =1;

    m_capsule = new btCapsuleShape(characterWidth, characterHeight);
    m_ghost_object->setCollisionShape (m_capsule);
    m_ghost_object->setCollisionFlags (btCollisionObject::CF_CHARACTER_OBJECT|btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
    m_world->getBroadphase()->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());

    btScalar stepHeight = btScalar(1);

    m_character_controller = new HeroController(m_ghost_object, m_capsule, stepHeight);
    m_character_controller->setMaxSlope(btScalar(0.872664626));  // 50°
    m_character_controller->setFallSpeed(50000);

    m_world->addCollisionObject(m_ghost_object, btBroadphaseProxy::CharacterFilter, btBroadphaseProxy::StaticFilter|btBroadphaseProxy::DefaultFilter);
    m_world->addAction(m_character_controller);
    m_world->getDispatchInfo().m_allowedCcdPenetration=0.0001f;
}
Hero::~Hero()
{
    m_joueur->setHero(nullptr);
    m_world->removeCollisionObject(m_ghost_object);
    m_world->removeAction(m_character_controller);
    delete m_ghost_object;
    delete m_character_controller;
    delete m_capsule;
}
JoueurRPG* Hero::joueur() const
{
    return m_joueur;
}
Avatar* Hero::avatar() const
{
    return m_avatar;
}
void Hero::update(const TimeDuration &duration)
{
    Vector3D dep;
    m_lastVerticalVelocity = m_character_controller->verticalVelocity();
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
        dep *= duration.seconds()*50;
    }
    m_character_controller->setWalkDirection(dep);
    if(m_isModified)
    {
        m_comportementModifie();
        m_isModified=false;
    }
    setPosition(m_ghost_object->getWorldTransform().getOrigin());
    Unite::update(duration);
}
void Hero::setAvancer(bool a)
{
    if(m_avancer!=a)
        m_isModified=true;
    m_avancer=a;
    for(WorldObjectListener* l : m_listeners)
    {
        HeroListener *hl = dynamic_cast<HeroListener*>(l);
        if(hl)
            hl->avancer(a);
    }
}
void Hero::setReculer(bool r)
{
    if(m_reculer!=r)
        m_isModified=true;
    m_reculer = r;
    for(WorldObjectListener* l : m_listeners)
    {
        HeroListener *hl = dynamic_cast<HeroListener*>(l);
        if(hl)
            hl->reculer(r);
    }
}
void Hero::setGauche(bool g)
{
    if(m_gauche!=g)
        m_isModified=true;
    m_gauche = g;
    for(WorldObjectListener* l : m_listeners)
    {
        HeroListener *hl = dynamic_cast<HeroListener*>(l);
        if(hl)
            hl->gauche(g);
    }
}
void Hero::setDroite(bool d)
{
    if(m_droite!=d)
        m_isModified=true;
    m_droite = d;
    for(WorldObjectListener* l : m_listeners)
    {
        HeroListener *hl = dynamic_cast<HeroListener*>(l);
        if(hl)
            hl->droite(d);
    }
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
void Hero::serializeComportement(EngineMessage* mess)
{
    mess->ints[mf::EngineMessageKey::OBJECT_ID] = this->id();
    mess->ints[mf::EngineMessageKey::TEAM_ID] = m_equipe->id();
    mess->positions[mf::EngineMessageKey::OBJECT_POSITION] = Hero::position();
    mess->quaternions[mf::EngineMessageKey::OBJECT_ROTATION] = Hero::rotation();
    mess->ints[mf::EngineMessageKey::HERO_AVANCE] = static_cast<int>(m_avancer);
    mess->ints[mf::EngineMessageKey::HERO_RECULE] = static_cast<int>(m_reculer);
    mess->ints[mf::EngineMessageKey::HERO_GAUCHE] = static_cast<int>(m_gauche);
    mess->ints[mf::EngineMessageKey::HERO_DROITE] = static_cast<int>(m_droite);
}
void Hero::deserializeComportement(EngineMessage* mess)
{
    setPosition(mess->positions[mf::EngineMessageKey::OBJECT_POSITION]);
    setRotation(mess->quaternions[mf::EngineMessageKey::OBJECT_ROTATION]);
    m_reculer = static_cast<bool>(mess->ints[mf::EngineMessageKey::HERO_RECULE]);
    m_avancer= static_cast<bool>(mess->ints[mf::EngineMessageKey::HERO_AVANCE]);
    m_droite = static_cast<bool>(mess->ints[mf::EngineMessageKey::HERO_DROITE]);
    m_gauche = static_cast<bool>(mess->ints[mf::EngineMessageKey::HERO_GAUCHE]);
}
void Hero::tournerGaucheDroite(float angle)
{
    setRotation(m_rotation * Quaternion::fromAngleAxis(0,1,0,angle));
}
void Hero::lookUpDown(float angle)
{
    if (m_look.getPitch().valueRadians()+angle < (3.14/2) && m_look.getPitch().valueRadians()+angle > -(3.14/2))
        m_look = Quaternion::fromAngleAxis(1,0,0,angle) * m_look;
}
const Quaternion& Hero::look() const
{
    return m_look;
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
void Hero::sauter()
{
    if(m_character_controller->canJump())
    {
        m_character_controller->jump();
        for(WorldObjectListener* l : m_listeners)
        {
            HeroListener *hl = dynamic_cast<HeroListener*>(l);
            if(hl)
                hl->sauter();
        }
    }
}
float Hero::verticalVelocity() const
{
    m_character_controller->verticalVelocity();
}
bool Hero::isOnGround() const
{
    return m_character_controller->onGround();
}
float Hero::lastVerticalVelocity() const
{
    return m_lastVerticalVelocity;
}
