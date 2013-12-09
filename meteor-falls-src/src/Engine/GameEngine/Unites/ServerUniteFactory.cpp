#include "ServerUniteFactory.h"
#include "Builder/UniteBuilder.h"

Unite* ServerUniteFactory::create_impl(UniteBuilder* builder, Joueur* j, Avatar* a, TypeUnite *t, UnitId id)
{
	Unite* u = builder->create(j, a, t, id);
	return u;
}
