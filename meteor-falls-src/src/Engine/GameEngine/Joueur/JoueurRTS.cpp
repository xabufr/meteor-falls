#include "JoueurRTS.h"
#include "Joueur.h"

JoueurRTS::JoueurRTS(Joueur *j): m_joueur(j)
{
}
JoueurRTS::~JoueurRTS()
{
}
Joueur* JoueurRTS::joueur()
{
	return m_joueur;
}
