#include "ServerGameEngine.h"
#include "Joueur/Joueur.h"
#include "Factions/Equipe.h"
#include "../EngineMessage/EngineMessage.h"
#include "../NetworkEngine/ServerNetworkEngine.h"
#include "Unites/UniteFactory.h"
#include "Heros/ClasseHeroManager.h"
#include "Heros/Hero.h"
#include "Unites/Unite.h"
#include "Factions/Faction.h"
#include "Factions/FactionManager.h"

ServerGameEngine::ServerGameEngine(EngineManager* mng): GameEngine(mng)
{
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
				std::cout << "SPAWN 1" << j << std::endl;
				if(j==nullptr||j->getTypeGameplay() != Joueur::TypeGameplay::RPG)
					return;
				Unite *unit = j->equipe()->getUnite(message.ints[EngineMessageKey::OBJECT_ID]);
				ClasseHero* cl = j->equipe()->faction()->getClassesManager().classe(message.ints[EngineMessageKey::CLASS_ID]);
				std::cout << "SPAWN 2" << std::endl;
				if(cl==nullptr||unit==nullptr)
				{
				std::cout << "SPAWN 3" << std::endl;
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
				std::cout << "SPAWN 4" << std::endl;
					Vector3D position(unit->position());
					message.ints[EngineMessageKey::RESULT] = 1;
					message.positions[EngineMessageKey::OBJECT_POSITION] = unit->position();
					int id = j->equipe()->factory()->getNextId();
					message.ints[EngineMessageKey::OBJECT_ID] = id;
					net->sendToAllTcp(&message);

					Hero *hero;
					if(static_cast<bool>(message.ints[EngineMessageKey::AVATAR_DEFAULT])&&
							j->avatar(message.ints[EngineMessageKey::AVATAR_ID]))
					{
						hero = new Hero(j->getRPG(), j->avatar(message.ints[EngineMessageKey::AVATAR_ID]),
								id);
						hero->setPosition(message.positions[EngineMessageKey::OBJECT_POSITION]);
					}
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
