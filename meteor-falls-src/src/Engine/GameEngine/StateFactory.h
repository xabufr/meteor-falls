#ifndef STATEFACTORY_H
#define STATEFACTORY_H

class State;
class StateManager;
class ClientGameEngine;

enum TypeState {
    TEAM_LIST,
    TEAM_STATE,
    SPAWN_STATE,
    PLAYING_RTS,
    PLAYING_RPG
};

State* createClientGameState(StateManager *manager, ClientGameEngine *client, TypeState type);
#endif // STATEFACTORY_H
