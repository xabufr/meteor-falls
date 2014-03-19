#include "BasicUniteBuilder.h"
#include "../TypeUnite.h"
#include "../Batiment.h"
#include "../Terrestre.h"
#include "../UniteFactory.h"

bool BatimentBuilder::canCreate(TypeUnite *t) const
{
    return t->type() == TypeUnite::BATIMENT;
}
Unite* BatimentBuilder::create(Joueur*, Avatar* a, TypeUnite* t, UnitId id) const
{
    return new Batiment(m_factory->equipe(), t, id);
}


bool TerrestreBuilder::canCreate(TypeUnite *type) const
{
    return type->type() == TypeUnite::TERRESTE;
}

Unite *TerrestreBuilder::create(Joueur *, Avatar *, TypeUnite *type, UnitId id) const
{
    return new Terrestre(m_factory->equipe(), type, id);
}
