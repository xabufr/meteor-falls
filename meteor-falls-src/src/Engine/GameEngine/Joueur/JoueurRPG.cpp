#include "JoueurRPG.h"
#include "Joueur.h"

JoueurRPG::JoueurRPG(Joueur *j): m_joueur(j)
{
    //ctor
}

JoueurRPG::~JoueurRPG()
{
    //dtor
}
Joueur* JoueurRPG::joueur() const
{
	return m_joueur;
}
