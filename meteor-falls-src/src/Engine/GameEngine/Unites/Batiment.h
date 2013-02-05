#ifndef BATIMENT_H
#define BATIMENT_H

#include "Unite.h"
#include <string>
#include <iostream>
#include <OgreTimer.h>

class Equipe;
namespace Ogre{
    class Entity;
	class SceneManager;
}
class Batiment: public Unite
{
    public:
        Batiment(Ogre::SceneManager*, Equipe*, TypeUnite* type, int id);

        bool Is_Constructed();
        bool Can_beConstructed();

    private:
        bool m_isconstructed;
        Ogre::Timer m_timer;
		Ogre::Entity* m_entite;
};

#endif // BATIMENT_H
