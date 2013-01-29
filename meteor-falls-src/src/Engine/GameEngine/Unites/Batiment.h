#ifndef BATIMENT_H
#define BATIMENT_H

#include "Unite.h"
#include <string>
#include <iostream>
#include <OgreSceneManager.h>
#include "../../../Utils/Vector3D.h"

class Batiment: public Unite
{
    public:
        Batiment(Ogre::SceneManager*, int p_id, std::string p_nom, TypeUnite* type, int id);
        void SetPosition(Vector3D p_position);

        bool Is_Constructed();
        int GetId();
        std::string GetName();
        Vector3D GetPosition();
        bool Can_beConstructed();

    private:
        std::string m_nom;
        int m_id;
        Vector3D m_position;
        bool m_isconstructed;
        Ogre::Timer m_timer;
};

/*



*/
#endif // BATIMENT_H
