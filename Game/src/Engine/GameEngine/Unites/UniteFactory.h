#ifndef UNITEFACTORY_H
#define UNITEFACTORY_H
#include "typedefs.h"
#include <list>

class Unite;
class Equipe;
class TypeUnite;
class UniteBuilder;
class Joueur;
class Avatar;
class WorldObjectIdentifierProvider;
namespace Ogre {
    class SceneManager;
} // namespace Ogre
class UniteFactory
{
    public:
        UniteFactory(WorldObjectIdentifierProvider &idProvider, Equipe*equipe);
        virtual ~UniteFactory();
        Unite* create(UnitId idType, UnitId id=0);
        Unite* create(TypeUnite* type, UnitId id=0);
        Unite* create(Joueur* joueur, Avatar*, TypeUnite* type, UnitId id=0);
        int getNextId();
        template<class T>
        void addBuilder()
        {
            m_builders.push_back(new T(this));
        }
        Equipe* equipe() const;

    protected:
        Equipe* m_equipe;
        virtual Unite* create_impl(UniteBuilder* builder, Joueur*, Avatar*, TypeUnite* type, UnitId id) = 0;
    private:
        WorldObjectIdentifierProvider &m_idProvider;
        std::list<UniteBuilder*> m_builders;

        UniteBuilder* getBuilder(TypeUnite*) const;
};

#endif // UNITEFACTORY_H
