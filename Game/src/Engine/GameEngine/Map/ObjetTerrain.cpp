#include "ObjetTerrain.h"

ObjetTerrain::ObjetTerrain(GameEngine* g, ObjetTerrainType* type, int id):
WorldObject(g, (WorldObjectType*) type, id), nodeId(0), paged(false)
{
}
ObjetTerrain::~ObjetTerrain()
{
}
