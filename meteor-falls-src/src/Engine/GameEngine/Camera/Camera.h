#ifndef CAMERA_H
#define CAMERA_H

#include <OgreCamera.h>

class Camera
{
    public:
        Camera();
        virtual ~Camera();
    protected:
        Ogre::Camera *m_camera;
};

#endif // CAMERA_H
