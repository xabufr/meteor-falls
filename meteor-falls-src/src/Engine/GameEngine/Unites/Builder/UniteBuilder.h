#ifndef H_UNITE_BUILDER_H  
#define H_UNITE_BUILDER_H 
#include "../typedefs.h"

class TypeUnite;
class Unite;
class UniteFactory;
class Joueur;
class Avatar;
class UniteBuilder
{
public:
	UniteBuilder(UniteFactory* fac): m_factory(fac)
	{}
	virtual ~UniteBuilder(){}
	virtual bool canCreate(TypeUnite* type) const = 0;
	virtual Unite* create(Joueur*, Avatar*, TypeUnite*, UnitId id) const = 0;
protected:
	UniteFactory* m_factory;
};

#endif
