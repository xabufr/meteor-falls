#ifndef H_SERVER_GAME_ENGINE_H
#define H_SERVER_GAME_ENGINE_H

#include "GameEngine.h"

class Unite;
class ServerNetworkEngine;
class ServerGameEngine: public GameEngine
{
public:
    ServerGameEngine(EngineManager*);
    virtual void handleMessage(EngineMessage&);
    virtual Type getTypeServerClient() const;
    bool tryJoinTeam(char, Joueur*);
    virtual void addTeam(Equipe *e);

    void uniteSubirDegats(Unite* unite, int degats);
    void tuerUnite(Unite*);

    static bool contactAddedCallback(btManifoldPoint &cp, const btCollisionObjectWrapper *colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper *colObj1Wrap, int partId1, int index1);

private:
    ServerNetworkEngine* m_net() const;
    static ServerGameEngine *m_instance; //Pour la callback
};
#endif
