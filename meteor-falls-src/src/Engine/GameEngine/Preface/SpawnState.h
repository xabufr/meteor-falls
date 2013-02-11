#ifndef _HOME_THOMAS_METEOR_FALLS_SRC_ENGINE_GAMEENGINE_PREFACE_SPAWNSTATE_H__
#define _HOME_THOMAS_METEOR_FALLS_SRC_ENGINE_GAMEENGINE_PREFACE_SPAWNSTATE_H__

#include "../../../State/State.h"
#include "../../../State/StateManager.h"

class GameEngine;

class SpawnState: public State
{
public:
	SpawnState(StateManager*, GameEngine*);
	virtual bool isVisible();
    virtual void enter();
    virtual void exit();
    virtual ret_code work(unsigned int time);
private:
	GameEngine* m_game;
};

#endif 
