#include "HeroBuilder.h"
#include "../../Heros/Hero.h"
#include "../../Joueur/Joueur.h"
#include "../TypeUnite.h"

bool HeroBuilder::canCreate(TypeUnite *t) const
{
	return t->type() == TypeUnite::HERO;
}
Unite* HeroBuilder::create(Joueur* j, Avatar* a, TypeUnite* t, UnitId id) const
{
	if(j&&a)
		return new Hero(j->getRPG(), a, id);
	return nullptr;
}
