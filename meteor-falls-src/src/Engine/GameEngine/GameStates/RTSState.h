#ifndef RTSSTATE_H_
#define RTSSTATE_H_

#include "State/State.h"
#include <Utils/Vector3D.h>
#include <Utils/rectangle.h>

class ClientGameEngine;
class Camera;
class CameraRTS;
class CommandConfig;
class RTSSelectionManager;
class Unite;

class RTSState: public State
{
public:
    RTSState(StateManager *manager, ClientGameEngine* gameEngine);
    virtual ~RTSState();
    virtual bool isVisible();
    virtual void enter();
    virtual void exit();
    virtual ret_code work(const TimeDuration &elapsed);
    Vector3D getMouseProjectedPosition() const;
    std::vector<Unite *> getUnitesInRectangle(const Rectangle<float> &rectangle) const;

private:
    void injectCameraEvents();

private:
    ClientGameEngine *m_gameEngine;
    CameraRTS *m_camera;
    CommandConfig *m_commandConfig;
    RTSSelectionManager *m_selectionManager;

    RTSState(const RTSState&);
};

#endif /* RTSSTATE_H_ */
