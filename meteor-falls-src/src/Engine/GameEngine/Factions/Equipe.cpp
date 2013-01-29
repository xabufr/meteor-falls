#include "Equipe.h"
#include "../Joueur/JoueurRPG.h"

Equipe::Equipe(char i): m_id(i)
{
	m_joueurRTS=nullptr;
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
};
void Equipe::removeRPG(JoueurRPG* j)
{
	for(auto it=m_joueursRPS.begin();it!=m_joueursRPS.end();)
	{
		if(j->joueur()==(*it)->joueur())
		{
			m_joueursRPS.erase(it);
			return;
		}
	}
}
void Equipe::addRPG(JoueurRPG* j)
{
	for(JoueurRPG *jt : m_joueursRPS)
		if(jt->joueur()==j->joueur())
			return;
	m_joueursRPS.push_back(j);
}
void Equipe::addJoueur(Joueur* j)
{
	for(Joueur* jt : m_joueurs)
		if(jt==j)
			return;
	m_joueurs.push_back(j);
}
void Equipe::removeJoueur(Joueur* j)
{
	for(auto it=m_joueurs.begin();it!=m_joueurs.end();)
	{
		if(*it==j)
		{
			m_joueurs.erase(it);
			return;
		}
	}
}
const std::vector<Joueur*> Equipe::joueurs() const
{
	return m_joueurs;
}
