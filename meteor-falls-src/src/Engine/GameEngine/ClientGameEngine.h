#ifndef H_CLIENT_GAME_ENGINE_H
#define H_CLIENT_GAME_ENGINE_H

#include "GameEngine.h"

class MapView;
class ClientGameEngine : public GameEngine
{
public:
	enum TypeState{
		TEAM_LIST,
		TEAM_STATE,
		SPAWN_STATE,
		PLAYING,
	};
	ClientGameEngine(EngineManager*, Joueur*);
	virtual ~ClientGameEngine();
	virtual void handleMessage(EngineMessage&);
	virtual void work();

	Chat* getChat(){return m_chat;}
	CameraManager *cameraManager() const;
	Joueur* getCurrentJoueur();
	void setSousStateType(TypeState);

	virtual Type getTypeServerClient() const;
private:
	MapView *m_map_view;
	Joueur *m_current_joueur;
	State *m_sous_state;
	CameraManager* m_camManager;
	Chat* m_chat;
	TypeState m_type_sous_state;
	bool m_change_sous_state;
};

#endif 
