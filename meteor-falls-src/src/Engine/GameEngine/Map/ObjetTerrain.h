#ifndef OBJETTERRAIN_H
#define OBJETTERRAIN_H

#include "../../../Utils/Vector3D.h"
#include "WorldObject.h"

class GameEngine;
class ObjetTerrain: public WorldObject
{
    public:
        ObjetTerrain(GameEngine*);
        virtual ~ObjetTerrain();
};

#endif // OBJETTERRAIN_H
