#ifndef _H_CAMERA_MANAGER_H_
#define _H_CAMERA_MANAGER_H_

namespace Ogre 
{
	class Camera;
	class SceneManager;
} // namespace Ogre
class Camera;
class CameraManager
{
public:
	CameraManager(Ogre::SceneManager*);
	~CameraManager();
	Ogre::Camera* camera() const;
	void setCameraContener(Camera*);
private:
	Ogre::Camera* m_camera;
	Camera *m_cameraContainer;
	Ogre::SceneManager *m_mng;
	Camera *m_cameraContener;
};

#endif 
