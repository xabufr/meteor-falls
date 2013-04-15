#include "ServerGameEngine.h"
#include "Joueur/Joueur.h"
#include "Factions/Equipe.h"
#include "../EngineMessage/EngineMessage.h"
#include "../NetworkEngine/ServerNetworkEngine.h"
#include "Unites/UniteFactory.h"
#include "Heros/ClasseHeroManager.h"
#include "Heros/Hero.h"
#include "Heros/ClasseHero.h"
#include "Unites/Unite.h"
#include "Unites/ServerUniteFactory.h"
#include "Factions/Faction.h"
#include "Factions/FactionManager.h"
#include "../PhysicalEngine/BulletRelationPtr.h"

extern ContactAddedCallback gContactAddedCallback;
ServerGameEngine* ServerGameEngine::m_instance = nullptr;

ServerGameEngine::ServerGameEngine(EngineManager* mng): GameEngine(mng)
{
	m_instance = this;
	gContactAddedCallback = ServerGameEngine::contactAddedCallback;
	for(char i=0; i<3;++i)
	{
		Equipe *e = new Equipe(this, i);
		e->setFaction(FactionManager::get()->getFaction(1));
		addTeam(e);
	}
}
GameEngine::Type ServerGameEngine::getTypeServerClient() const
{
	return GameEngine::SERVER;
}
void ServerGameEngine::handleMessage(EngineMessage& message)
{
	ServerNetworkEngine* net = (ServerNetworkEngine*) m_manager->getNetwork();
	switch(message.message)
	{
		case CHAT_MESSAGE:
			{
				if(message.ints[EngineMessageKey::RANGE]==EngineMessageKey::TEAM_RANGE)
				{
					Equipe *equipe = nullptr;
					int playerId = message.ints[EngineMessageKey::PLAYER_NUMBER];
					for(Joueur *j : m_joueurs)
						if(j->id() == playerId)
							equipe = j->equipe();
					if(equipe==nullptr)
						return;
					net->sendToTeam(equipe, &message);
				}
				else if(message.ints[EngineMessageKey::RANGE] == EngineMessageKey::GLOBAL_RANGE)
					net->sendToAllTcp(&message);
			}
			break;
		case DEL_PLAYER:
			{
				deleteJoueur(message.ints[EngineMessageKey::PLAYER_NUMBER]);
			}
			break;
		case ADDOBJECT:
			{
				UnitId type       = message.ints[EngineMessageKey::OBJECT_TYPE];
				UnitId id         = message.ints[EngineMessageKey::OBJECT_ID];
				Vector3D position = message.positions[EngineMessageKey::OBJECT_POSITION];
				char teamId = message.ints[EngineMessageKey::TEAM_ID];
				Equipe *e   = getEquipe(teamId);
				Unite *unit = e->factory()->create(type, id);
				unit->setPosition(position);
			}
			break;
		case SPAWN:
			{
				Joueur *j = findJoueur(message.ints[EngineMessageKey::PLAYER_NUMBER]);
				if(j==nullptr||j->getTypeGameplay() != Joueur::TypeGameplay::RPG)
					return;
				Unite *unit = j->equipe()->getUnite(message.ints[EngineMessageKey::OBJECT_ID]);
				ClasseHero* cl = j->equipe()->faction()->getClassesManager().classe(message.ints[EngineMessageKey::CLASS_ID]);
				if(cl==nullptr||unit==nullptr)
				{
					message.ints.clear();
					message.ints[EngineMessageKey::RESULT] = 0;
					/**
					 * TODO : Revoir cette ligne
					 * */
					//message.ints[EngineMessageKey::ERROR_CODE] = SpawnState::ErrorMessages::INVALID_SPAWN;
					net->sendToTcp(j, &message);
				}
				else
				{
					Vector3D position(unit->position());
					message.ints[EngineMessageKey::RESULT] = 1;
					message.positions[EngineMessageKey::OBJECT_POSITION] = unit->position();

					Unite *hero;
					if(static_cast<bool>(message.ints[EngineMessageKey::AVATAR_DEFAULT])&&
							j->avatar(message.ints[EngineMessageKey::AVATAR_ID]))
					{
						Avatar *avatar = j->avatar(message.ints[EngineMessageKey::AVATAR_ID]);
						hero = j->equipe()->factory()->create(j, avatar, cl);
						hero->setPosition(message.positions[EngineMessageKey::OBJECT_POSITION]);
					}
					int id = hero->id();
					message.ints[EngineMessageKey::OBJECT_ID] = id;
					net->sendToAllTcp(&message);
				}
			}
			break;
		case SELECT_TEAM:
			{
				char teamId  = message.ints[EngineMessageKey::TEAM_ID];
				Joueur *joueur = findJoueur(message.ints[EngineMessageKey::PLAYER_NUMBER]);
				if(joueur==nullptr)
					break;
				bool alertOther = joueur->equipe() == nullptr;
				bool canJoin = tryJoinTeam(teamId, joueur);
				EngineMessage messageTeam(m_manager);
				messageTeam.message = EngineMessageType::SELECT_TEAM;
				messageTeam.ints[EngineMessageKey::PLAYER_NUMBER] = joueur->id();
				if(canJoin)
				{
					if(alertOther)
						net->announcePlayerConnectionTeam(joueur);
					messageTeam.ints[EngineMessageKey::TEAM_ID] = teamId;
					net->sendToAllTcp(&messageTeam);
				}
				else
				{
					messageTeam.ints[EngineMessageKey::TEAM_ID] = -1;
					net->sendToTcp(joueur, &messageTeam);
				}
			}
			break;
		case SELECT_GAMEPLAY:
			{
				Joueur *joueur = findJoueur(message.ints[EngineMessageKey::PLAYER_NUMBER]);
				EngineMessage messageRep(m_manager);
				messageRep.message = EngineMessageType::SELECT_GAMEPLAY;
				messageRep.ints[EngineMessageKey::PLAYER_NUMBER] = joueur->id();
				messageRep.ints[EngineMessageKey::GAMEPLAY_TYPE] = message.ints[EngineMessageKey::GAMEPLAY_TYPE];
				bool result = true;
				if(message.ints[EngineMessageKey::GAMEPLAY_TYPE] == EngineMessageKey::RTS_GAMEPLAY)
				{
					if(joueur->equipe()->getRTS() == nullptr)
					{
						messageRep.ints[EngineMessageKey::RESULT] = 1;
						joueur->setTypeGamplay(Joueur::RTS);
					}
					else
					{
						messageRep.ints[EngineMessageKey::RESULT] = 0;
						result = false;
					}
				}
				else
				{
					messageRep.ints[EngineMessageKey::RESULT] = 1;
					joueur->setTypeGamplay(Joueur::RPG);
				}
				if(result)
					net->sendToAllTcp(&messageRep);
				else
					net->sendToTcp(joueur, &messageRep);
			}
			break;
	}
}
bool ServerGameEngine::tryJoinTeam(char id, Joueur* j)
{
	int nb_min=999, nb_cur = 9999;
	Equipe *eJoueur = nullptr;
	for(Equipe *e : m_teams)
	{
		int nb = e->joueurs().size();
		if(nb<nb_min)
			nb_min=nb;
		if(id==e->id())
		{
			nb_cur = nb;
			eJoueur = e;
		}
	}
	if(eJoueur==nullptr || nb_cur >= nb_min+3)
		return false;

	j->changeTeam(eJoueur);

	return true;
}
void ServerGameEngine::addTeam(Equipe* e)
{
	e->setFactory(new ServerUniteFactory(e));
	GameEngine::addTeam(e);
}
void ServerGameEngine::uniteSubirDegats(Unite *unite, int degats)
{
	unite->subirDegats(degats);
	EngineMessage mes(m_manager);
	mes.message = EngineMessageType::SUBIR_DEGATS;
	mes.ints[TEAM_ID] = unite->equipe()->id();
	mes.ints[OBJECT_ID] = unite->id();
	mes.ints[EngineMessageKey::OBJECT_HEAL] = degats;
	m_net()->sendToAllTcp(&mes);
}
void ServerGameEngine::tuerUnite(Unite *unite)
{
	unite->tuer();
	EngineMessage mes(m_manager);
	mes.message         = EngineMessageType::KILL;
	mes.ints[OBJECT_ID] = unite->id();
	mes.ints[TEAM_ID] = unite->equipe()->id();
	m_net()->sendToAllTcp(&mes);
}
bool ServerGameEngine::contactAddedCallback(btManifoldPoint &cp, const btCollisionObjectWrapper *colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper *colObj1Wrap, int partId1, int index1)
{
	BulletRelationPtr *ptr1 = static_cast<BulletRelationPtr*>(colObj0Wrap->getCollisionObject()->getUserPointer());
	BulletRelationPtr *ptr2 = static_cast<BulletRelationPtr*>(colObj1Wrap->getCollisionObject()->getUserPointer());

	if(!ptr1||!ptr2) return false;
	if(ptr1->type==ptr2->type) return false;
	if(ptr1->type==BulletRelationPtr::Type::UNITE ||
	   ptr2->type==BulletRelationPtr::Type::UNITE)
	{
		Unite *u = static_cast<Unite*>((ptr1->type==BulletRelationPtr::Type::UNITE) ?ptr1->obj_ptr:ptr2->obj_ptr);
		if(ptr1->type == BulletRelationPtr::Type::DEATH_OBJ || ptr2->type==BulletRelationPtr::Type::DEATH_OBJ)
		{
			m_instance->tuerUnite(u);
		}
	}
	return false;
}
ServerNetworkEngine* ServerGameEngine::m_net() const
{
	return static_cast<ServerNetworkEngine*>(m_manager->getNetwork());
}
