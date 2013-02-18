#ifndef _HOME_THOMAS_METEOR_FALLS_SRC_ENGINE_GAMEENGINE_HEROS_HERO_H__
#define _HOME_THOMAS_METEOR_FALLS_SRC_ENGINE_GAMEENGINE_HEROS_HERO_H__
#include "../Unites/Unite.h"

class JoueurRPG;
class Avatar;
class Hero: public Unite
{
public:
	Hero(Ogre::SceneManager*, JoueurRPG*, Avatar*, int id);
	JoueurRPG* joueur() const;
	Avatar *avatar() const;
	virtual void update(unsigned int);
private:
	JoueurRPG *m_joueur;
	Avatar *m_avatar;
};

#endif 
