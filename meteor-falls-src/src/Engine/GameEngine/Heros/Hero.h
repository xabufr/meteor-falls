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
namespace Ogre {
	class Entity;
} // namespace Ogre
class Hero: public Unite
{
public:
	Hero(Ogre::SceneManager*, JoueurRPG*, Avatar*, int id, btDynamicsWorld*, const btVector3& vect);
	virtual ~Hero();
	JoueurRPG* joueur() const;
	Avatar *avatar() const;
	virtual void update(unsigned int);
	void setAvancer(bool);
	void setReculer(bool);
	void setGauche(bool);
	void setDroite(bool);
	void serializeComportement(EngineMessage*, bool all=true);
	void deserializeComportement(EngineMessage*, bool all=true);
	const Ogre::Entity* entity() const;
	void tournerGaucheDroite(float angle);
private:
	JoueurRPG *m_joueur;
    btDynamicsWorld* m_world;
	Avatar *m_avatar;
	Ogre::Entity *m_entityBody;
	btPairCachingGhostObject *m_ghost_object;
	btKinematicCharacterController *m_character_controller;
	bool m_avancer, m_reculer, m_droite, m_gauche;
	bool m_isModified;
	void m_comportementModifie();
	void m_move(const btVector3& vect);
};

#endif
