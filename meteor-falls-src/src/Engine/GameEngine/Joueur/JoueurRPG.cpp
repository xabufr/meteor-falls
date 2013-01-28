#include "JoueurRPG.h"
#include "Joueur.h"

JoueurRPG::JoueurRPG(Joueur *j): m_joueur(j)
{
	m_joueur->setRPG(this);
	m_joueur->setTypeGamplay(Joueur::TypeGameplay::RPG);
}
JoueurRPG::~JoueurRPG()
{
    //dtor
}
Joueur* JoueurRPG::joueur() const
{
	return m_joueur;
}
