#include "BasicUniteBuilder.h"
#include "../TypeUnite.h"
#include "../Batiment.h"
#include "../UniteFactory.h"

bool BatimentBuilder::canCreate(TypeUnite *t) const
{
	return t->type() == TypeUnite::BATIMENT;
}
Unite* BatimentBuilder::create(Joueur*, Avatar* a, TypeUnite* t, UnitId id) const
{
	return new Batiment(m_factory->equipe(), t, id);
}
