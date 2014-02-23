#ifndef OBJETTERRAIN_H
#define OBJETTERRAIN_H

#include "../../../Utils/Vector3D.h"
#include "WorldObject.h"

class GameEngine;
struct ObjetTerrainType;
class ObjetTerrain: public WorldObject
{
    public:
        ObjetTerrain(GameEngine*, ObjetTerrainType*, int id);
        virtual ~ObjetTerrain();
        int nodeId;
        bool paged;
    protected:
        ObjetTerrainType *m_type;
};

#endif // OBJETTERRAIN_H
