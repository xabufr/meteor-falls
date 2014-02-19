#ifndef H_OBJET_TERRAIN_TYPE_MANAGER_H
#define H_OBJET_TERRAIN_TYPE_MANAGER_H
#include "typedefs.h"
#include <map>
#include <string>

class ObjetTerrainType;
class ObjetTerrainTypeManager
{
public:
	ObjetTerrainType* get(const std::string &name) const;
	ObjetTerrainTypeManager();
	~ObjetTerrainTypeManager();
private:
	std::map<std::string, ObjetTerrainType*> m_types;
};

#endif 
