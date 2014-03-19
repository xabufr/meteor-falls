#ifndef RTSSTATE_H_
#define RTSSTATE_H_

#include "State/State.h"
#include <Utils/Vector3D.h>
#include <Utils/rectangle.h>
#include "RTS/rtsselectedunitscommand.h"

class ClientGameEngine;
class Camera;
class CameraRTS;
class CommandConfig;
class RTSSelectionManager;
class Unite;
class WorldObject;

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
    std::vector<Unite *> getUnitesInRectangleUnderCamera(const Rectangle<float> &rectangle) const;
    WorldObject* getObjectUnderRay(const Ogre::Ray &ray) const;
    Ogre::Ray getMouseRay() const;
    ClientGameEngine *game();
    void selectedUnitsChanged(const std::vector<WorldObject*> &newSelection);

private:
    void injectCameraEvents();
    RTSState(const RTSState&);

private:
    ClientGameEngine *m_gameEngine;
    CameraRTS *m_camera;
    CommandConfig *m_commandConfig;
    RTSSelectionManager *m_selectionManager;
    RTSSelectedUnitsCommand m_selectedUnitsCommands;
};

#endif /* RTSSTATE_H_ */
