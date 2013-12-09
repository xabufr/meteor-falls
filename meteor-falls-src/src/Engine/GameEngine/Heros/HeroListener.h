#ifndef H_HERO_LISTENER_H
#define H_HERO_LISTENER_H 
#include "../Map/WorldObjectListener.h"

class HeroListener : virtual public WorldObjectListener 
{
public:
	virtual void avancer(bool) = 0;
	virtual void reculer(bool) = 0;
	virtual void droite(bool) = 0;
	virtual void gauche(bool) = 0;
	virtual void sauter() = 0;
};
#endif 
