#ifndef CAMERARTS_H
#define CAMERARTS_H

#include "Camera.h"

class CameraRTS : public Camera
{
    public:
        CameraRTS();
        virtual ~CameraRTS();
        void setCamera(Ogre::Camera*);
        void update(int); //temps entre 2 update (utilisation du speed)
        void forward(bool); // m_forward = bool
        void back(bool);
        void right(bool);
        void left(bool);
        void zoom(int);

    protected:
        Ogre::Camera *m_camera;

    private:
        bool m_forward;
        bool m_back;
        bool m_right;
        bool m_left;
};

#endif // CAMERARTS_H
