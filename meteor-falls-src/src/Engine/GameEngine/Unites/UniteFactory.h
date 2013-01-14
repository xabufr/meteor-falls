#ifndef UNITEFACTORY_H
#define UNITEFACTORY_H
#include "typedefs.h"

class Unite;
class Faction;
class UniteFactory
{
    public:
        UniteFactory(Faction* f);
        virtual ~UniteFactory();

        Unite* create(UnitId id);

    protected:
    private:
        Faction *m_faction;
};

#endif // UNITEFACTORY_H
