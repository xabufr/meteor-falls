#include "UniteFactory.h"
#include "../Factions/Faction.h"
#include "TypeUnite.h"

UniteFactory::UniteFactory(Faction* f)
{

}
UniteFactory::~UniteFactory()
{

}
Unite* UniteFactory::create(UnitId id)
{
    TypeUnite *type = m_faction->getType(id);
    if(type==0)
        return 0;
    switch(type->type())
    {
    case TypeUnite::BATIMENT:
        break;
    case TypeUnite::AERIEN:
        break;
    case TypeUnite::TERRESTE:
        break;
    }
    return 0;
}
