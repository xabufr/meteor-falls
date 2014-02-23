#include "UniteFactory.h"
#include "../Factions/Equipe.h"
#include "../Factions/Faction.h"
#include "TypeUnite.h"
#include "Batiment.h"
#include "Builder/UniteBuilder.h"
#include "../Map/worldobjectidentifierprovider.h"

UniteFactory::UniteFactory(WorldObjectIdentifierProvider &idProvider, Equipe *equipe): m_equipe(equipe), m_idProvider(idProvider)
{
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
        id =m_idProvider.createId();
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
Equipe* UniteFactory::equipe() const
{
    return m_equipe;
}
