#ifndef _H_CAMERA_MANAGER_H_
#define _H_CAMERA_MANAGER_H_

namespace Ogre 
{
	class Camera;
} // namespace Ogre
class Camera;
class CameraManager
{
public:
	Ogre::Camera* camera();
private:
	Ogre::Camera* m_camera;
	Camera *m_cameraContainer;
};

#endif 
