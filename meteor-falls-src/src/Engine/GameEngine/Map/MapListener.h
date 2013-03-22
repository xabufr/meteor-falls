#ifndef H_MAP_LISTENER_H
#define H_MAP_LISTENER_H

#include <string>

class MapListener
{
public:
	virtual void mapLoaded(const std::string&) = 0;
	virtual void mapUnloaded() = 0;
	virtual void update() = 0;
};

#endif 
