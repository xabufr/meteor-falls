#ifndef _HOME_THOMAS_METEOR_FALLS_SRC_ENGINE_GAMEENGINE_HEROS_HERO_H__
#define _HOME_THOMAS_METEOR_FALLS_SRC_ENGINE_GAMEENGINE_HEROS_HERO_H__
#include "../Unites/Unite.h"

class JoueurRPG;
class Avatar;
namespace Ogre {
	class Entity;
} // namespace Ogre
class Hero: public Unite
{
public:
	Hero(Ogre::SceneManager*, JoueurRPG*, Avatar*, int id);
	virtual ~Hero();
	JoueurRPG* joueur() const;
	Avatar *avatar() const;
	virtual void update(unsigned int);
	void setAvancer(bool);
	void setReculer(bool);
	void setGauche(bool);
	void setDroite(bool);
private:
	JoueurRPG *m_joueur;
	Avatar *m_avatar;
	Ogre::Entity *m_entityBody;
	bool m_avancer, m_reculer, m_droite, m_gauche;
};

#endif 
