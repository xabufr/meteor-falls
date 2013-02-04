#ifndef AERIEN_H
#define AERIEN_H

#include "Mobile.h"

class Aerien : public Mobile
{
    public:
        Aerien(Ogre::SceneManager*, TypeUnite* type, int id);
        virtual ~Aerien();
    protected:
    private:
};

#endif // AERIEN_H
