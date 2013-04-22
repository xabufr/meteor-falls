#ifndef BATIMENT_H
#define BATIMENT_H

#include "Unite.h"
#include <string>
#include <iostream>

class GameEngine;
class Equipe;
class Batiment: public Unite
{
    public:
        Batiment(Equipe*, TypeUnite* type, int id);

        bool isConstructed();
        bool canBeConstructed();

    private:
        bool m_isconstructed;
		/*
		 * TODO: Utiliser un timer perso
		 * */
//        Ogre::Timer m_timer;
};

#endif // BATIMENT_H
