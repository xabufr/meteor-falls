#include "Equipe.h"

Equipe::Equipe()
{
    //ctor
}

Equipe::~Equipe()
{
    //dtor
}
Faction* Equipe::faction()
{
    return m_faction;
}

void Equipe::setFaction(Faction* f)
{
    m_faction=f;
}
void Equipe::setJoueurRTS(JoueurRTS* joueur)
{
	m_joueurRTS = joueur;
}
