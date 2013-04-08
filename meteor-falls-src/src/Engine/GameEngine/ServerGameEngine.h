#ifndef H_SERVER_GAME_ENGINE_H
#define H_SERVER_GAME_ENGINE_H

#include "GameEngine.h"

class ServerGameEngine: public GameEngine
{
public:
	ServerGameEngine(EngineManager*);
	virtual void handleMessage(EngineMessage&);
	virtual Type getTypeServerClient() const;
	bool tryJoinTeam(char, Joueur*);
	virtual void addTeam(Equipe *e);
};
#endif 
