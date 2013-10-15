#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <string>
#include <vector>
#include <bullet/BulletDynamics/btBulletDynamicsCommon.h>
#include <bullet/BulletCollision/btBulletCollisionCommon.h>
#include <bullet/Bullet-C-Api.h>
#include "../Engine.h"

class ObjetTerrainTypeManager;
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
		virtual void addTeam(Equipe*);
		void addPlayer(Joueur*);
		Equipe* getEquipe(char);
		virtual Joueur* findJoueur(int);
		void deleteJoueur(int);
		virtual Type getTypeServerClient() const=0;
		btDiscreteDynamicsWorld* bulletWorld() const;
		ObjetTerrainTypeManager* objetTerrainTypeManager() const;
	protected:
        Map *m_map;
		std::vector<Equipe*> m_teams;
		std::vector<Joueur*> m_joueurs;

		//physique
		btDbvtBroadphase* m_broadphase;
        btDefaultCollisionConfiguration* m_collisionConfiguration;
        btCollisionDispatcher* m_dispatcher;
        btSequentialImpulseConstraintSolver* m_solver;
        btDiscreteDynamicsWorld* m_world;
		ObjetTerrainTypeManager* m_objectTypeManager;
};

#endif // GAMEENGINE_H
