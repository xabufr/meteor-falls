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

const std::string& Joueur::getNom() const
{
		return m_nom;
}
 
