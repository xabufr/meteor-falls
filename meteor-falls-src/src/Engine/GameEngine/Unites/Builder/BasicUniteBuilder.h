#ifndef H_BASIC_UNITE_BUILDER_H
#define H_BASIC_UNITE_BUILDER_H
#include "UniteBuilder.h"

class BatimentBuilder: public UniteBuilder
{
public:
	BatimentBuilder(UniteFactory* fac): UniteBuilder(fac)
	{}
	virtual ~BatimentBuilder() { }
	virtual bool canCreate(TypeUnite* type) const;
	virtual Unite* create(Joueur*, Avatar*, TypeUnite*, UnitId id) const;
};

#endif 
