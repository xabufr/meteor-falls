#include "Armure.h"

Armure::Armure(ArmureId id, const std::string& nom) : m_id(id), m_nom(nom)
{

}

ArmureId Armure::id() const
{
    return m_id;
}
const std::string& Armure::nom() const
{
    return m_nom;
}

void Armure::addDegat(Degat* deg, int val)
{
    m_degats[deg]=val;
}

const Armure::Degats& Armure::getDegats()
{
    return m_degats;
}

int Armure::getResistance(Degat* deg)
{
    auto it = m_degats.find(deg);
    if(it != m_degats.end())
        return it->second;
    return 0;
}
