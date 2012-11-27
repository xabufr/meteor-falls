#include "TypeUnite.h"

TypeUnite::TypeUnite(UnitId id, Type type, Faction* fac): m_id(id), m_type(type), m_fation(fac)
{

}

TypeUnite::~TypeUnite()
{

}

TypeUnite::Type TypeUnite::typeFromString(const std::string& type)
{
    if(type=="BAT")
        return BATIMENT;
    else if(type=="TER")
        return TERRESTE;
    else if(type=="AIR")
        return AERIEN;
    return BATIMENT;
}
