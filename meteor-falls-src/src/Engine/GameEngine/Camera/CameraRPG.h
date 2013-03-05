#include "Camera.h"

class Hero;
class CameraRPG: public Camera
{
public:
	CameraRPG(Hero*);
	~CameraRPG();
	virtual void setCamera(Ogre::Camera*);
	virtual void update(int);
private:
	Ogre::SceneNode *m_sceneNode;
	Hero *m_hero;
};
