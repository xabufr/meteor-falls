#include "JoueurRTS.h"
#include "Joueur.h"

JoueurRTS::JoueurRTS(Joueur *j): m_joueur(j)
{
    //ctor
}
JoueurRTS::~JoueurRTS()
{
    //dtor
}
Joueur* JoueurRTS::joueur()
{
	return m_joueur;
}
