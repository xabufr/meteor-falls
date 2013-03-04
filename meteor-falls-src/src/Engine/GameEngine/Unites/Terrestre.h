#ifndef TERRESTRE_H
#define TERRESTRE_H

#include "Mobile.h"

class Equipe;
class Terrestre: public Mobile
{
    public:
        Terrestre(Ogre::SceneManager*, Equipe*, TypeUnite* type, int id);
        virtual ~Terrestre();
    protected:
    private:
};

#endif // TERRESTRE_H
