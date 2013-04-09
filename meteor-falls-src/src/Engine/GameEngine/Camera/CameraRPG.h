#include "Camera.h"
#include "../../../Utils/Quaternion.h"

class Hero;
class CameraRPG: public Camera
{
public:
	CameraRPG(Hero*);
	~CameraRPG();
	virtual void setCamera(Ogre::Camera*);
	virtual void update(int);
private:
	Hero *m_hero;
	float m_distance;
	Quaternion m_vertical;
};
