#ifndef RPGSTATE_H
#define RPGSTATE_H

#include "State/State.h"
#include <OIS/OISMouse.h>

class ClientGameEngine;
class CameraRPG;
class Hero;
class SpawnState;
class RPGState: public State, public OIS::MouseListener
{
public:
    RPGState(StateManager *manager, ClientGameEngine *clientGameEngine);
    virtual ~RPGState();
    virtual bool isVisible();
    virtual void enter();
    virtual void exit();
    virtual ret_code work(const TimeDuration& elapsed);

    virtual bool mouseMoved( const OIS::MouseEvent &arg );
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
private:
    ClientGameEngine *m_clientGameEngine;
    CameraRPG *m_camera;
    Hero* m_hero;
    SpawnState *m_spawnState;
    State *m_currentState;
};

#endif // RPGSTATE_H
