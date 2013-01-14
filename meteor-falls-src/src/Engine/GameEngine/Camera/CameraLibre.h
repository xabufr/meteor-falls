#ifndef CAMERALIBRE_H
#define CAMERALIBRE_H

#include <Ogre.h>
#include "Camera.h"


class CameraLibre : public Camera
{
    public:
        CameraLibre();
        virtual ~CameraLibre();
        void update(int); //temps entre 2 update (utilisation du speed)
        void forward(bool); // m_forward = bool
        void back(bool);
        void right(bool);
        void left(bool);
        void lookUpDown(Ogre::Degree); // modifier pitch avec vérification angle max et min
        void lookRightLeft(Ogre::Degree); // modifier yaw

    protected:

    private:
        Ogre::Degree m_angle_up_down;
        float m_speed;
        bool m_forward;
        bool m_back;
        bool m_right;
        bool m_left;
};

#endif // CAMERALIBRE_H
