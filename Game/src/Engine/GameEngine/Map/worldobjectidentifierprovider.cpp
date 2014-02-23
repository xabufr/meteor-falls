#include "worldobjectidentifierprovider.h"

WorldObjectIdentifierProvider::WorldObjectIdentifierProvider(): m_last_id_created(0)
{
}

unsigned int WorldObjectIdentifierProvider::createId()
{
    return ++m_last_id_created;
}

unsigned int WorldObjectIdentifierProvider::getLastCreatedId() const
{
    return m_last_id_created;
}
