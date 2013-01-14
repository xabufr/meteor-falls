#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <string>
#include "Map/Map.h"
#include "../EngineMessage/EngineMessage.h"
#include "../Engine.h"
#include "../../State/State.h"
#include "Preface/TeamList.h"

class Joueur;
class Equipe;
class GameEngine : public Engine
{
    public:
        enum TypeState{
            TEAM_LIST,
            TEAM_STATE
        };
        enum Type{
            CLIENT,
            SERVER
        };
        GameEngine(EngineManager*, Type);
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
		bool tryJoinTeam(char, Joueur*);
		Joueur* findJoueur(int);

    protected:

    private:
        Map *m_map;
        Type m_type;
        TypeState m_type_sous_state;
        State *m_sous_state;
		Joueur *m_currentJoueur;
		std::vector<Equipe*> m_teams;
		std::vector<Joueur*> m_joueurs;
		bool m_change_sous_state;
};

#endif // GAMEENGINE_H
