#ifndef AERIEN_H
#define AERIEN_H

#include "Mobile.h"

class Equipe;
class Aerien : public Mobile
{
    public:
        Aerien(Ogre::SceneManager*, Equipe*, TypeUnite* type, int id);
        virtual ~Aerien();
    protected:
    private:
};

#endif // AERIEN_H
