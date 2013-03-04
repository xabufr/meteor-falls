#ifndef CAMERA_H
#define CAMERA_H

#include <OgreCamera.h>

class Camera
{
    public:
        Camera();
        virtual ~Camera();
        virtual void update(int) = 0;
        virtual void setCamera(Ogre::Camera*);
        Ogre::Camera* getCamera();

    protected:
        Ogre::Camera *m_camera;
};

#endif // CAMERA_H
