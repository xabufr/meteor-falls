#include "JoueurRPG.h"
#include "Joueur.h"

JoueurRPG::JoueurRPG(Joueur *j): m_joueur(j)
{
}
JoueurRPG::~JoueurRPG()
{
}
Joueur* JoueurRPG::joueur() const
{
	return m_joueur;
}
