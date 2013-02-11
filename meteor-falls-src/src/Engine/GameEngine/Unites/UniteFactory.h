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
        Unite* create(Ogre::SceneManager*, UnitId idType, UnitId id=0);

    protected:
    private:
        Equipe* m_equipe;
		UnitId m_last_id;
};

#endif // UNITEFACTORY_H
