#ifndef H_SERVER_UNITE_FACTORY_H
#define H_SERVER_UNITE_FACTORY_H
#include "UniteFactory.h"

class ServerUniteFactory: public UniteFactory
{
public:
    ServerUniteFactory(WorldObjectIdentifierProvider &idProvider, Equipe *e): UniteFactory(idProvider, e) { }
protected:
    virtual Unite* create_impl(UniteBuilder* builder, Joueur*, Avatar*, TypeUnite* type, UnitId id);
};

#endif
