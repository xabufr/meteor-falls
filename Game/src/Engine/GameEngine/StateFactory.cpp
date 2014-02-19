#include "StateFactory.h"
#include "GameStates/RTSState.h"
#include "Preface/TeamList.h"
#include "Preface/TeamState.h"
#include "Preface/SpawnState.h"
#include "GameStates/RTSState.h"
#include "GameStates/rpgstate.h"


State *createClientGameState(StateManager *manager, ClientGameEngine *client, TypeState type)
{
    switch(type) {
    case SPAWN_STATE:
        return new SpawnState(nullptr, client);
    case TEAM_LIST:
        return new TeamList(nullptr, client);
    case TEAM_STATE:
        return new TeamState(nullptr, client);
    case PLAYING_RPG:
        return new RPGState(nullptr, client);
    case PLAYING_RTS:
        return new RTSState(nullptr, client);
    }
}
