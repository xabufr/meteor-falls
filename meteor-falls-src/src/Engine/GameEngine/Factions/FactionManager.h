#ifndef FACTIONMANAGER_H
#define FACTIONMANAGER_H

#include "../../../Utils/singleton.h"
#include <vector>

typedef unsigned char FactionId;
class Faction;
class FactionManager: public Singleton<FactionManager>
{
    friend class Singleton<FactionManager>;
    public:
        Faction* getFaction(FactionId);
    protected:
        FactionManager();
        virtual ~FactionManager();
    private:
        std::vector<Faction*> m_factions;
};

#endif // FACTIONMANAGER_H
