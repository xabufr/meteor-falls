#ifndef UNITE_H
#define UNITE_H
#include "../Map/ObjetTerrain.h"
#include "TypeUnite.h"

class Unite : public ObjetTerrain
{
    public:
        Unite(Ogre::SceneManager*, TypeUnite* type, int id);
        TypeUnite* GetType();
        virtual ~Unite();

    private:
        TypeUnite* m_Type;
};

#endif // UNITE_H
