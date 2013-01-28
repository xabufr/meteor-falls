#include "JoueurRTS.h"
#include "Joueur.h"

JoueurRTS::JoueurRTS(Joueur *j): m_joueur(j)
{
 	m_joueur->setRTS(this);
	m_joueur->setTypeGamplay(Joueur::TypeGameplay::RTS);
}
JoueurRTS::~JoueurRTS()
{
    //dtor
}
Joueur* JoueurRTS::joueur()
{
	return m_joueur;
}
