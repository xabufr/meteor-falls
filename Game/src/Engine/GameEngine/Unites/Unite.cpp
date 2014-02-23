#include "Unite.h"
#include "../Factions/Equipe.h"

Unite::Unite(Equipe *equipe, TypeUnite* type, int id): WorldObject(equipe->game(), type, id), m_equipe(equipe)
{
    m_vie = 100;
    m_equipe->addUnit(this);
}
Unite::~Unite()
{
    m_equipe->removeUnit(this);
}
const TypeUnite* Unite::type() const
{
    return static_cast<const TypeUnite*>(WorldObject::type());
}
void Unite::update(float time)
{
    WorldObject::update(time);
}
bool Unite::estVivant() const
{
    return m_vie > 0;
}
int Unite::vie() const
{
    return m_vie;
}
void Unite::subirDegats(int degats)
{
    m_vie -= degats;
}
void Unite::tuer()
{
    m_vie = 0;
}
bool Unite::destroyNeeded() const
{
    return !estVivant();
}
Equipe* Unite::equipe() const
{
    return m_equipe;
}
