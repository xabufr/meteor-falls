#include "UniteFactory.h"
#include "../Factions/Equipe.h"
#include "../Factions/Faction.h"
#include "TypeUnite.h"
#include "Batiment.h"
#include "Builder/UniteBuilder.h"

UniteFactory::UniteFactory(Equipe* e): m_equipe(e)
{
	m_last_id = 0;
}
UniteFactory::~UniteFactory()
{
	for(UniteBuilder* b : m_builders)
		delete b;
}
Unite* UniteFactory::create(UnitId idType, UnitId id)
{
    TypeUnite *type = m_equipe->faction()->getType(idType);
	return create(type, id);
}
Unite* UniteFactory::create(TypeUnite* t, UnitId id)
{
	return create(nullptr, nullptr, t, id);
}
Unite* UniteFactory::create(Joueur* j, Avatar* a, TypeUnite* t, UnitId id)
{
	if(id==0)
		id = getNextId();
	if(t)
	{
		UniteBuilder* builder = getBuilder(t);
		if(builder)
			return create_impl(builder, j, a, t, id);
	}
	return nullptr;
}
UniteBuilder* UniteFactory::getBuilder(TypeUnite* t) const
{
	for(UniteBuilder* builder: m_builders)
	{
		if(builder->canCreate(t))
			return builder;
	}
	return nullptr;
}
int UniteFactory::getNextId()
{
	return m_last_id++;
}
Equipe* UniteFactory::equipe() const
{
	return m_equipe;
}
