#include "Joueur.h"
#include <iostream>
#include "JoueurRPG.h"
#include "JoueurRTS.h"
#include "../Factions/Equipe.h"

Joueur::Joueur()
{
	m_type_gamplay = TypeGameplay::NONE_GAMEPLAY;
	m_equipe = nullptr;
}
Joueur::~Joueur()
{
}
void Joueur::setNom(const std::string& nom)
{
	m_nom=nom;
}
const std::string& Joueur::getNom()
{
	return m_nom;
}
void Joueur::setNumSession(const std::string& num)
{
    m_num_session = num;
}
const std::string& Joueur::getNumSession()
{
    return m_num_session;
}
void Joueur::setLevel(int lvl)
{
    m_level = lvl;
}
const int& Joueur::getLevel()
{
    return m_level;
}
void Joueur::changeTeam(Equipe* equ)
{
	if(equ==m_equipe)
		return;
	setTypeGamplay(TypeGameplay::NONE_GAMEPLAY);
	if(m_equipe != nullptr)
	{
		m_equipe->removeJoueur(this);
	}
	m_equipe 		   = equ;
	if(m_equipe != nullptr)
		m_equipe->addJoueur(this);
}
void Joueur::setTypeGamplay(TypeGameplay t)
{
	if(m_type_gamplay==TypeGameplay::RTS)
	{
		m_equipe->setJoueurRTS(nullptr);
		delete getRTS();
		setRTS(nullptr);
	}
	else if (m_type_gamplay==TypeGameplay::RPG) 
	{
		m_equipe->removeRPG(getRPG());
		delete getRPG();
		setRPG(nullptr);	
	}
	m_type_gamplay = t;
	if(t==TypeGameplay::RTS)
	{
		setRTS(new JoueurRTS(this));
		m_equipe->setJoueurRTS(getRTS());
	}
	else if (t==TypeGameplay::RPG) 
	{
		setRPG(new JoueurRPG(this));
		m_equipe->addRPG(getRPG());
	}
}
