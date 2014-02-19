#ifndef ARMURE_H
#define ARMURE_H
#include "typedefs.h"
#include <unordered_map>
#include <string>

class Degat;
class Armure
{
    public:
        typedef std::unordered_map<Degat*, int> Degats;
        Armure(ArmureId id, const std::string& nom);

        ArmureId id() const;
        const std::string& nom() const;

        void addDegat(Degat*, int);
        const Degats& getDegats();
        int getResistance(Degat*);
    protected:
    private:
        Degats m_degats;
        const ArmureId m_id;
        const std::string m_nom;
};

#endif // ARMURE_H
