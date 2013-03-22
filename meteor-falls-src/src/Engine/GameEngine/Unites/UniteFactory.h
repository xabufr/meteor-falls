#ifndef UNITEFACTORY_H
#define UNITEFACTORY_H
#include "typedefs.h"

class Unite;
class Equipe;
namespace Ogre {
	class SceneManager;
} // namespace Ogre
class UniteFactory
{
    public:
        UniteFactory(Equipe*);
        virtual ~UniteFactory();
        Unite* create(UnitId idType, UnitId id=0);
		int getNextId();

    protected:
    private:
        Equipe* m_equipe;
		UnitId m_last_id;
};

#endif // UNITEFACTORY_H
