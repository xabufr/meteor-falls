#include "JoueurRPG.h"
#include "Joueur.h"

JoueurRPG::JoueurRPG(Joueur *j): m_joueur(j),
m_hero(nullptr)
{
}
JoueurRPG::~JoueurRPG()
{
}
Joueur* JoueurRPG::joueur() const
{
	return m_joueur;
}
void JoueurRPG::setHero(Hero* h)
{
	m_hero = h;
}
Hero* JoueurRPG::hero() const
{
	return m_hero;
}

