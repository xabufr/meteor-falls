#include "Batiment.h"
#include "TypeUnite.h"
#include "../Factions/Equipe.h"
#include "../../../precompiled/lexical_cast.h"

Batiment::Batiment(Equipe *equipe, TypeUnite* type, int id)
    : Unite(equipe, type, id)
{
    //m_timer.reset();
    m_isconstructed = false;
}
bool Batiment::isConstructed()
{
    return m_isconstructed;
}
