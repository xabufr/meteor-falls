#include "Avatar.h"

Avatar::Avatar(int id, ClasseHero* cl): m_id(id), m_classe(cl)
{
	
}
const std::string& Avatar::nom() const
{
	return m_nom;
}
int Avatar::id() const
{
	return m_id;
}
ClasseHero* Avatar::classe() const
{
	return m_classe;
}
