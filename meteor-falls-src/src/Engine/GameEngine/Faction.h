#ifndef FACTION_H
#define FACTION_H
#include <string>

class Faction
{
    public:
        Faction();
        virtual ~Faction();
    protected:
    private:
        std::string m_nom;
};

#endif // FACTION_H
