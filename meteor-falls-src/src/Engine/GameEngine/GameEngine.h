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
class Chat;
class GameEngine : public Engine
{
    public:
        enum Type{
            CLIENT,
            SERVER
        };
		GameEngine(EngineManager*);
        virtual ~GameEngine();
        virtual void handleMessage(EngineMessage&) = 0;
        virtual void work();
        virtual EngineType getType();

		virtual void loadMap(const std::string &);
		const std::vector<Equipe*>& getTeams() const;
		void addTeam(Equipe*);
		void addPlayer(Joueur*);
		Equipe* getEquipe(char);
		virtual Joueur* findJoueur(int);
		void deleteJoueur(int);
		virtual Type getTypeServerClient() const=0;
	protected:
        Map *m_map;
		std::vector<Equipe*> m_teams;
		std::vector<Joueur*> m_joueurs;
};

#endif // GAMEENGINE_H
