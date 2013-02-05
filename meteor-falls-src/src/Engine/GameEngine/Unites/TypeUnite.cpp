#include "TypeUnite.h"

TypeUnite::TypeUnite(UnitId id, Type type, Faction* fac): m_id(id), m_type(type), m_faction(fac)
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
UnitId TypeUnite::id() const
{
    return m_id;
}
TypeUnite::Type TypeUnite::type() const
{
    return m_type;
}
Faction* TypeUnite::faction() const
{
    return m_faction;
}
int TypeUnite::vie() const
{
    return m_vie;
}
const std::string& TypeUnite::nom() const
{
    return m_nom;
}
const Ressources& TypeUnite::cout() const
{
    return m_cout;
}
const Ressources& TypeUnite::apports() const
{
    return m_apports;
}
int TypeUnite::temps_construction() const
{
    return m_temps_construction;
}
int TypeUnite::attaque() const
{
    return m_attaque;
}
float TypeUnite::vision() const
{
    return m_vision;
}
float TypeUnite::portee() const
{
    return m_portee;
}
TypeUnite* TypeUnite::amelioration() const
{
    return m_amelioration;
}
const std::vector<TypeUnite*>& TypeUnite::construit() const
{
    return m_construit;
}
const std::vector<Recherche*>& TypeUnite::recherches() const
{
    return m_recherches;
}
const std::vector<Recherche*>& TypeUnite::necessiteRecherche() const
{
    return m_necessiteRecherche;
}
const std::vector<TypeUnite*>& TypeUnite::necessiteUnite() const
{
    return m_necessiteUnite;
}
int TypeUnite::niveau_recquis() const
{
    return m_niveau_recquis;
}
Degat* TypeUnite::typeDegats() const
{
    return m_typeDegats;
}
Armure* TypeUnite::armure() const
{
    return m_armure;
}
const TypeUnite::MeshParameters& TypeUnite::meshParameters() const
{
    return m_meshParameters;
}
