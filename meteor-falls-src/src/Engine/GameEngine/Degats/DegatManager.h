#ifndef DEGATMANAGER_H
#define DEGATMANAGER_H
#include "Utils/singleton.h"
#include "typedefs.h"

#include <unordered_map>

class Degat;
class Armure;
class DegatManager : public Singleton<DegatManager>
{
    friend class Singleton<DegatManager>;
    public:
        Armure* getArmure(ArmureId);
        Degat* getDegat(DegatId);
    protected:
        DegatManager();
        virtual ~DegatManager();
    private:
        std::unordered_map<ArmureId, Armure*> m_armures;
        std::unordered_map<DegatId, Degat*> m_degats;
};

#endif // DEGATMANAGER_H
