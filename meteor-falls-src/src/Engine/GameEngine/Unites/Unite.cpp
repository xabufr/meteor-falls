#include "Unite.h"
#include "../Factions/Equipe.h"

Unite::Unite(Equipe *equipe, TypeUnite* type, int id): WorldObject(equipe->game(), nullptr), m_type(type), m_id(id), m_equipe(equipe)
{
	m_equipe->create_unit(this);
}
Unite::~Unite()
{
	m_equipe->destroy_unite(this);
}
int Unite::id() const
{
	return m_id;
}
TypeUnite* Unite::type() const
{
	return m_type;
}
void Unite::update(unsigned int)
{

}
