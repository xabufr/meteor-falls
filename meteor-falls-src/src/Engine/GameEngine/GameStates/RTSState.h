/*
 * RTSState.h
 *
 *  Created on: 19 déc. 2013
 *      Author: thomas
 */

#ifndef RTSSTATE_H_
#define RTSSTATE_H_

#include "State/State.h"

class ClientGameEngine;
class Camera;
class CameraRTS;
class CommandConfig;

class RTSState: public State
{
public:
    RTSState(StateManager *manager, ClientGameEngine* gameEngine);
    virtual ~RTSState();
    virtual bool isVisible();
    virtual void enter();
    virtual void exit();
    virtual ret_code work(const TimeDuration &elapsed);

private:
    void injectCameraEvents();

private:
    ClientGameEngine *m_gameEngine;
    CameraRTS *m_camera;
    CommandConfig *m_commandConfig;
};

#endif /* RTSSTATE_H_ */
