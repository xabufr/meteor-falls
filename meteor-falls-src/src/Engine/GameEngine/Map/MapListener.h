#ifndef H_MAP_LISTENER_H
#define H_MAP_LISTENER_H

#include <string>

class ObjetTerrain;
class MapListener
{
public:
	virtual ~MapListener(){ }
	virtual void mapLoaded(const std::string&) = 0;
	virtual void mapUnloaded() = 0;
	virtual void update() = 0;
	virtual bool autoDelete() const = 0;
	virtual void objetAdded(ObjetTerrain*) = 0;
	virtual void objetRemoved(ObjetTerrain*) = 0;
};

#endif 
