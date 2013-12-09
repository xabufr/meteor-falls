#ifndef H_UNITE_VIEW_H
#define H_UNITE_VIEW_H

#include "../Map/WorldObjectView.h"

class Unite;
class UniteView: public WorldObjectView
{
public:
	UniteView(Unite*, Ogre::SceneNode*);
};

#endif 
