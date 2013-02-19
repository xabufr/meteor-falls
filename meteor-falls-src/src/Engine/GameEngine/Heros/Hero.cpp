#include "Hero.h"
#include "Avatar.h"
#include "ClasseHero.h"
#include "../Joueur/JoueurRPG.h"
#include "../Joueur/Joueur.h"
#include <OgreSceneManager.h>
#include <OgreEntity.h>

Hero::Hero(Ogre::SceneManager* mng, JoueurRPG *j, Avatar *a, int id):
Unite(mng, j->joueur()->equipe(), nullptr, id),
m_joueur(j),
m_avatar(a),
m_entityBody(nullptr)
{
	j->setHero(this);
	if(mng)
	{
		std::string meshName = a->classe()->mesh(j->joueur()->getLevel());
		m_entityBody = mng->createEntity(meshName);
		m_sceneNode->attachObject(m_entityBody);
	}
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
