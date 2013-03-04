#include "CameraManager.h"
#include "Camera.h"
#include <OgreSceneManager.h>
#include <OgreCamera.h>
#include "../../GraphicEngine/Ogre/ogrecontextmanager.h"
#include "../../GraphicEngine/Ogre/OgreApplication.h"

CameraManager::CameraManager(Ogre::SceneManager* mng): m_mng(mng)
{
	m_cameraContener = nullptr;
	m_camera = m_mng->createCamera("camera_jeu");
	m_camera->setNearClipDistance(0.01);
	Ogre::RenderWindow *window = OgreContextManager::get()->getOgreApplication()->getWindow();
	window->addViewport(m_camera, 1);
}
CameraManager::~CameraManager()
{
	Ogre::RenderWindow *window = OgreContextManager::get()->getOgreApplication()->getWindow();
	window->removeViewport(1);
	m_mng->destroyCamera(m_camera);
}
Ogre::Camera* CameraManager::camera() const
{
	return m_camera;
}
void CameraManager::setCameraContener(Camera *cam)
{
	if(m_cameraContener)
		delete m_cameraContener;
	m_cameraContener = cam;
}
