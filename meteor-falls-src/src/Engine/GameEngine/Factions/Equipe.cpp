#include "Equipe.h"

Equipe::Equipe(char i): m_id(i)
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
const std::vector<JoueurRPG*> Equipe::getRPG() const
{
	return m_joueursRPS;
}
JoueurRTS* Equipe::getRTS() const
{
	return m_joueurRTS;
}
char Equipe::id() const
{
	return m_id;
}
