#include "JoueurRPG.h"
#include "Joueur.h"
#include "../Heros/Hero.h"
#include <iostream>

JoueurRPG::JoueurRPG(Joueur *j): m_joueur(j),
m_hero(nullptr)
{
}
JoueurRPG::~JoueurRPG()
{
	if(m_hero)
	{
		delete m_hero;
	}
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

