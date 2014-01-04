#include "CameraManager.h"
#include "Camera.h"
#include <OgreSceneManager.h>
#include <OgreCamera.h>
#include "../../GraphicEngine/Ogre/ogrecontextmanager.h"
#include "../../GraphicEngine/Ogre/OgreApplication.h"

CameraManager::CameraManager(Ogre::SceneManager* mng) :
        m_mng(mng)
{
    m_cameraContainer = nullptr;
    m_camera = m_mng->createCamera("camera_jeu");
    m_camera->setNearClipDistance(0.01);
    m_camera->setUseRenderingDistance(true);
    m_camera->setRenderingDistance(128);
    Ogre::RenderWindow *window =
            OgreContextManager::get()->getOgreApplication()->getWindow();
    window->addViewport(m_camera, 1);
}
CameraManager::~CameraManager()
{
    Ogre::RenderWindow *window =
            OgreContextManager::get()->getOgreApplication()->getWindow();
    window->removeViewport(1);
    m_mng->destroyCamera(m_camera);
}
Ogre::Camera* CameraManager::camera() const
{
    return m_camera;
}
Camera* CameraManager::cameraContainer() const
{
    return m_cameraContainer;
}
void CameraManager::setCameraContener(Camera *cam)
{
    if (m_cameraContainer)
        delete m_cameraContainer;
    m_cameraContainer = cam;
    if (m_cameraContainer)
        m_cameraContainer->setCamera(m_camera);
}

void CameraManager::update(const TimeDuration &elapsed)
{
    if (cameraContainer())
        cameraContainer()->update(elapsed);
}
