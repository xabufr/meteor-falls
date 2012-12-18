#include "Joueur.h"

Joueur::Joueur()
{
    //ctor
}

Joueur::~Joueur()
{
    //dtor
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

void Joueur::setLevel(const int& lvl)
{
    m_level = lvl;
}

const int& Joueur::getLevel()
{
    return m_level;
}
