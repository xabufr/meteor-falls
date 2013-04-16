#ifndef _HOME_THOMAS_METEOR_FALLS_SRC_ENGINE_GAMEENGINE_HEROS_HERO_H__
#define _HOME_THOMAS_METEOR_FALLS_SRC_ENGINE_GAMEENGINE_HEROS_HERO_H__
#include "../Unites/Unite.h"
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include "BulletCollision/CollisionDispatch/btGhostObject.h"
#include "BulletDynamics/Character/btKinematicCharacterController.h"

class JoueurRPG;
class EngineMessage;
class Avatar;
class HeroController;
class Hero: public Unite
{
public:
	Hero(JoueurRPG*, Avatar*, int id);
	virtual ~Hero();
	JoueurRPG* joueur() const;
	Avatar *avatar() const;
	virtual void update(float time);
	virtual void setPosition(const Vector3D& pos);
	const Quaternion& look() const;
	void setAvancer(bool);
	void setReculer(bool);
	void setGauche(bool);
	void setDroite(bool);
	void sauter();
	void serializeComportement(EngineMessage*);
	void deserializeComportement(EngineMessage*);
	void tournerGaucheDroite(float angle);
	void lookUpDown(float angle);
	float verticalVelocity() const;
	bool isOnGround() const;

private:
	JoueurRPG *m_joueur;
    btDynamicsWorld* m_world;
	Avatar *m_avatar;
	btPairCachingGhostObject *m_ghost_object;
	HeroController *m_character_controller;
	btConvexShape *m_capsule;
	bool m_avancer, m_reculer, m_droite, m_gauche;
	bool m_isModified;
	void m_comportementModifie();
	void m_move(const btVector3& vect);
	Quaternion m_look;
};

#endif
