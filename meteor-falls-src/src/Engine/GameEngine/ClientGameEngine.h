#ifndef H_CLIENT_GAME_ENGINE_H
#define H_CLIENT_GAME_ENGINE_H
#include "Layout/layoutRTS.h"
#include "GameEngine.h"


#include <BtOgreExtras.h>
class MapView;
class WorldObjectView;
class ClientGameEngine : public GameEngine
{
public:
	enum TypeState{
		TEAM_LIST,
		TEAM_STATE,
		SPAWN_STATE,
		PLAYING_RTS,
		PLAYING_RPG,
	};
	ClientGameEngine(EngineManager*, Joueur*);
	virtual ~ClientGameEngine();
	virtual void handleMessage(EngineMessage&);
	virtual void work();

    void SetLayoutRts();
	Chat* getChat(){return m_chat;}
	CameraManager *cameraManager() const;
	Joueur* getCurrentJoueur();
	void setSousStateType(TypeState);
	virtual void addTeam(Equipe*);

	virtual Type getTypeServerClient() const;
private:
	BtOgre::DebugDrawer *debug ;
	MapView *m_map_view;
	Joueur *m_current_joueur;
	State *m_sous_state;

	CameraManager* m_camManager;
	Chat* m_chat;
	TypeState m_type_sous_state;
	bool m_change_sous_state;
};

#endif
