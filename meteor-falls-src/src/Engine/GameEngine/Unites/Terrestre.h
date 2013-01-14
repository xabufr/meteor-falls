#ifndef TERRESTRE_H
#define TERRESTRE_H

#include "Mobile.h"

class Terrestre: public Mobile
{
    public:
        Terrestre(Ogre::SceneManager*);
        virtual ~Terrestre();
    protected:
    private:
};

#endif // TERRESTRE_H
