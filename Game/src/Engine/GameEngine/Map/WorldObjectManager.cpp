#include "WorldObjectManager.h"
#include "../../ScriptEngine/XmlDocumentManager.h"
#include "WorldObjectType.h"
#include "../../../precompiled/lexical_cast.h"

WorldObjectManager::WorldObjectManager()
{
}
WorldObjectManager::~WorldObjectManager()
{
    //dtor
}
WorldObjectType* WorldObjectManager::getType(WorldObjectTypeId id) const
{
    auto it = m_types.find(id);
    if(it!=m_types.end())
        return it->second;
    return nullptr;
}
