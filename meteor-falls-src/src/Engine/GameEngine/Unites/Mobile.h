#ifndef MOBILE_H
#define MOBILE_H

#include "Unite.h"

class Equipe;
class Mobile : public Unite
{
    public:
        Mobile(Ogre::SceneManager*, Equipe*, TypeUnite* type, int id);
        virtual ~Mobile();
    protected:
    private:
};

#endif // MOBILE_H
