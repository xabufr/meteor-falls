#include "ClasseHero.h"

ClasseHero::ClasseHero(int id, Faction* fac): m_id(id), m_faction(fac)
{
}
int ClasseHero::id() const
{
	return m_id;
}
const std::string& ClasseHero::icone() const
{
	return m_icone;
}
const std::string& ClasseHero::nom() const
{
	return m_nom;
}
