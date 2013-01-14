#ifndef HERO_H
#define HERO_H

#include "Terrestre.h"

class Hero : public Terrestre
{
    public:
        Hero(Ogre::SceneManager* mng);
        virtual ~Hero();
    protected:
    private:
};

#endif // HERO_H
