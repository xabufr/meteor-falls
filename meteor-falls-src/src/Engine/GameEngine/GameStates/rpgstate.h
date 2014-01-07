#ifndef RPGSTATE_H
#define RPGSTATE_H

#include "State/State.h"

class ClientGameEngine;
class CameraRPG;
class Hero;
class SpawnState;
class RPGState: public State
{
public:
    RPGState(StateManager *manager, ClientGameEngine *clientGameEngine);
    virtual ~RPGState();
    virtual bool isVisible();
    virtual void enter();
    virtual void exit();
    virtual ret_code work(const TimeDuration& elapsed);
private:
    ClientGameEngine *m_clientGameEngine;
    CameraRPG *m_camera;
    Hero* m_hero;
    SpawnState *m_spawnState;
    State *m_currentState;
};

#endif // RPGSTATE_H
