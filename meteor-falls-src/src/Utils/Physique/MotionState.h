#ifndef MOTIONSTATE_H_INCLUDED
#define MOTIONSTATE_H_INCLUDED

#include <bullet/LinearMath/btMotionState.h>
#include <bullet/LinearMath/btQuaternion.h>
#include <bullet/LinearMath/btVector3.h>
#include <OGRE/Ogre.h>

class MotionState:public btMotionState
{
public:
    MotionState(Ogre::SceneNode* node)
    {
            m_node = node;
            m_trans.setIdentity();
    }
    virtual ~MotionState()
    { }
    virtual void getWorldTransform(btTransform &worldTrans) const
    {
            worldTrans = m_trans;
    }
    virtual void setWorldTransform(const btTransform &worldTrans)
    {
            m_trans = worldTrans;
            btQuaternion ori = m_trans.getRotation();
            btVector3 pos = m_trans.getOrigin();
            m_node->setPosition(Ogre::Vector3(pos.x(),pos.y(),pos.z()));
            m_node->setOrientation(Ogre::Quaternion(ori.w(),ori.x(),ori.y(),ori.z()));
    }

protected:
    Ogre::SceneNode* m_node;
    btTransform m_trans;
};
#endif // MOTIONSTATE_H_INCLUDED
