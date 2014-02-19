#ifndef WORLDOBJECTMANAGER_H
#define WORLDOBJECTMANAGER_H
#include "../../../Utils/singleton.h"
#include <unordered_map>

class WorldObjectType;
typedef unsigned short WorldObjectTypeId;
class WorldObjectManager: public Singleton<WorldObjectManager>
{
    friend class Singleton<WorldObjectManager>;
public:
    static WorldObjectManager* get() { return Singleton<WorldObjectManager>::get(); }
    WorldObjectType* getType(WorldObjectTypeId) const;

protected:
    WorldObjectManager();
    virtual ~WorldObjectManager();
private:
    std::unordered_map<WorldObjectTypeId, WorldObjectType*> m_types;
};

#endif // WORLDOBJECTMANAGER_H
