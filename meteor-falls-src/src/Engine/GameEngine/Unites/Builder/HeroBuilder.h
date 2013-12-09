#ifndef H_HERO_BUILDER_H
#define H_HERO_BUILDER_H
#include "UniteBuilder.h"

class HeroBuilder: public UniteBuilder
{
public:
	HeroBuilder(UniteFactory* fac): UniteBuilder(fac){ }
	virtual bool canCreate(TypeUnite* type) const;
	virtual Unite* create(Joueur*, Avatar*, TypeUnite*, UnitId id) const;
};

#endif 
