#include "Unite.h"
#include "../Factions/Equipe.h"

Unite::Unite(Ogre::SceneManager* mng, Equipe *equipe, TypeUnite* type, int id): ObjetTerrain(equipe->game(),mng), m_type(type), m_id(id), m_equipe(equipe)
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
