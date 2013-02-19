#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <string>
#include <vector>
#include "../Engine.h"

class State;
class Map;
class Joueur;
class Equipe;
class CameraManager;
class GameEngine : public Engine
{
    public:
        enum TypeState{
            TEAM_LIST,
            TEAM_STATE,
			SPAWN_STATE,
			PLAYING,
        };
        enum Type{
            CLIENT,
            SERVER
        };
        enum EtatClient{
			SelectTeam,
			SelectGameplay,
			Spawn,
			Playing,
		};
		GameEngine(EngineManager*, Type, Joueur* j=0);
        virtual ~GameEngine();
        virtual void handleMessage(EngineMessage&);
        virtual void work();
        virtual EngineType getType();

		void loadMap(const std::string &);
		const std::vector<Equipe*>& getTeams() const;
		void addTeam(Equipe*);
		void addPlayer(Joueur*);
		void setSousStateType(TypeState);
		Equipe* getEquipe(char);
		Joueur* getCurrentJoueur();
		bool tryJoinTeam(char, Joueur*);
		Joueur* findJoueur(int);
		void deleteJoueur(int);
		Type getTypeServerClient() const;
		CameraManager *cameraManager() const;

    private:
        Map *m_map;
        Type m_type;
        TypeState m_type_sous_state;
        State *m_sous_state;
		Joueur *m_current_joueur;
		std::vector<Equipe*> m_teams;
		std::vector<Joueur*> m_joueurs;
		bool m_change_sous_state;
		EtatClient m_etatClient;
		CameraManager* m_camManager;
};

#endif // GAMEENGINE_H
