#include "Unite.h"
#include "../Factions/Equipe.h"

Unite::Unite(Ogre::SceneManager* mng, Equipe *equipe, TypeUnite* type, int id): ObjetTerrain(mng), m_type(type), m_id(id), m_equipe(equipe)
{
	m_equipe->create_unit(this);
}
TypeUnite* Unite::GetType()
{
    return m_type;
}
Unite::~Unite()
{
    //dtor
}
int Unite::id() const
{
	return m_id;
}
TypeUnite* Unite::type() const
{
	return m_type;
}
