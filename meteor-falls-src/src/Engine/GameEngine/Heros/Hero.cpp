#include "Hero.h"
#include "../Joueur/JoueurRPG.h"
#include "../Joueur/Joueur.h"

Hero::Hero(Ogre::SceneManager* mng, JoueurRPG *j, Avatar *a, int id):
Unite(mng, j->joueur()->equipe(), nullptr, id),
m_joueur(j),
m_avatar(a)
{
	j->setHero(this);
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

}
