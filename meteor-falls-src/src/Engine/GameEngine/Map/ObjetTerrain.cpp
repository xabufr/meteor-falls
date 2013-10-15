#include "ObjetTerrain.h"

ObjetTerrain::ObjetTerrain(GameEngine* g, ObjetTerrainType* type): 
WorldObject(g, nullptr), m_type(type), nodeId(0), paged(false)
{
}
ObjetTerrain::~ObjetTerrain()
{
}
