#include "ClientGameEngine.h"
#include "../EngineManager/EngineManager.h"
#include "../GraphicEngine/GraphicEngine.h"
#include "../EngineMessage/EngineMessage.h"
#include "../NetworkEngine/clientnetworkengine.h"
#include "Camera/CameraManager.h"
#include "Camera/CameraRPG.h"
#include "Camera/CameraRTS.h"
#include "Map/MapView.h"
#include "Map/Map.h"
#include "Preface/TeamList.h"
#include "Preface/SpawnState.h"
#include "Preface/TeamState.h"
#include "Interface/Chat.h"
#include "Unites/TypeUnite.h"
#include "Unites/Unite.h"
#include "Factions/Equipe.h"
#include "Unites/UniteFactory.h"
#include "Heros/Hero.h"
#include "Heros/Avatar.h"
#include "Heros/ClasseHero.h"
#include "Joueur/JoueurRPG.h"
#include "../../Utils/Configuration/Config.h"
#include "../GraphicEngine/Ogre/ogrecontextmanager.h"
#include "../GraphicEngine/Ogre/OgreWindowInputManager.h"
#include "Unites/ClientUniteFactory.h"

ClientGameEngine::ClientGameEngine(EngineManager* mng, Joueur* j):
	GameEngine(mng),
    m_change_sous_state(true)
{
	mng->getGraphic()->getSceneManager()->setShadowTechnique(Ogre::SHADOWTYPE_NONE);
	m_camManager = new CameraManager(mng->getGraphic()->getSceneManager());
	m_map_view = new MapView(m_map);
	m_sous_state = nullptr;
	m_type_sous_state = TypeState::TEAM_LIST;
	m_chat = new Chat(this);
	m_current_joueur = j;
	addPlayer(j);
	setSousStateType(TypeState::TEAM_LIST);
	debug = new BtOgre::DebugDrawer(mng->getGraphic()->getSceneManager()->getRootSceneNode(), m_world);
	m_world->setDebugDrawer(debug);
	debug->setDebugMode(true);
}
ClientGameEngine::~ClientGameEngine()
{
    if (m_sous_state != nullptr)
    {
        m_sous_state->exit();
        delete m_sous_state;
    }
	delete m_camManager;
    delete m_chat;
	if(m_current_joueur)
		m_current_joueur->changeTeam(nullptr);
}
void ClientGameEngine::addTeam(Equipe *e)
{
	e->setFactory(new ClientUniteFactory(e, m_manager->getGraphic()->getSceneManager()));
	GameEngine::addTeam(e);
}
void ClientGameEngine::handleMessage(EngineMessage& message)
{
	switch(message.message)
	{
		case EngineMessageType::CHAT_MESSAGE:
			{
				std::string nom = "\\[ "+findJoueur(message.ints[EngineMessageKey::PLAYER_NUMBER])->getNom()+" ]:"+message.strings[EngineMessageKey::MESSAGE];
				//m_chat->addMessage(nom);
			}
			break;
		case EngineMessageType::SELECT_GAMEPLAY:
			{
				if (message.ints[EngineMessageKey::RESULT] == 1)
				{
					Joueur *joueur = findJoueur(message.ints[EngineMessageKey::PLAYER_NUMBER]);
					if(joueur==nullptr)
						return;
					joueur->setTypeGamplay(message.ints[EngineMessageKey::GAMEPLAY_TYPE]==EngineMessageKey::RTS_GAMEPLAY?
							Joueur::TypeGameplay::RTS : Joueur::TypeGameplay::RPG);
					if(joueur == m_current_joueur)
					{
						if(joueur->getTypeGameplay() == Joueur::TypeGameplay::RPG)
							setSousStateType(TypeState::SPAWN_STATE);

						else if (joueur->getTypeGameplay() == Joueur::TypeGameplay::RTS)
							SetLayoutRts();
					}
				}
			}
			break;
		case EngineMessageType::DEL_PLAYER:
			{
				deleteJoueur(message.ints[EngineMessageKey::PLAYER_NUMBER]);
			}
			break;
		case EngineMessageType::SELECT_TEAM:
			{
				int team_id = message.ints[EngineMessageKey::TEAM_ID];
				if(team_id==-1)
					return;
				Joueur *joueur = findJoueur(message.ints[EngineMessageKey::PLAYER_NUMBER]);
				Equipe *equ = getEquipe(team_id);
				if(joueur==nullptr || equ == nullptr)
					return;
				joueur->changeTeam(equ);
				if(joueur == m_current_joueur)
				{
				}
			}
			break;
		case EngineMessageType::ADDOBJECT:
			{
				UnitId type       = message.ints[EngineMessageKey::OBJECT_TYPE];
				UnitId id         = message.ints[EngineMessageKey::OBJECT_ID];
				Vector3D position = message.positions[EngineMessageKey::OBJECT_POSITION];
				char teamId = message.ints[EngineMessageKey::TEAM_ID];
				Equipe *e   = getEquipe(teamId);
				Unite *unit = e->factory()->create(type, id);
				unit->setPosition(position);
				std::cout << unit->type()->meshParameters().at("normal") << std::endl;
			}
			break;
		case EngineMessageType::SPAWN:
			{
				Joueur *j = findJoueur(message.ints[EngineMessageKey::PLAYER_NUMBER]);
				if(j==nullptr||j->getTypeGameplay() != Joueur::TypeGameplay::RPG)
					return;
				if(message.ints[EngineMessageKey::RESULT] == 1)
				{
					Vector3D position(message.positions[EngineMessageKey::OBJECT_POSITION]);

					if(!j->avatar(message.ints[EngineMessageKey::AVATAR_ID]))
					{
					}
					Avatar *avatar = j->avatar(message.ints[EngineMessageKey::AVATAR_ID]);
					Unite* hero = j->equipe()->factory()->create(j, avatar, avatar->classe(),
							message.ints[EngineMessageKey::OBJECT_ID]);
					hero->setPosition(message.positions[EngineMessageKey::OBJECT_POSITION]+Vector3D(0,100,0));
					if(m_current_joueur==j)
					{
						setSousStateType(TypeState::PLAYING_RPG);
						m_camManager->setCameraContener(new CameraRPG(m_current_joueur->getRPG()->hero()));
						m_camManager->cameraContainer()->setCamera(m_camManager->camera());
					}
				}
				else if(m_sous_state!=nullptr)
				{
					SpawnState* sous_state = dynamic_cast<SpawnState*>(m_sous_state);
					if(sous_state)
					{
						sous_state->notifySpawnError((SpawnState::ErrorMessages)message.ints[EngineMessageKey::ERROR_CODE]);
					}
				}
			}
			break;
		case EngineMessageType::KILL:
			{
				Equipe *e = getEquipe(message.ints[TEAM_ID]);
				if(e)
				{
					Unite *u = e->getUnite(message.ints[OBJECT_ID]);
					if(u)
					{
						u->tuer();
						if(m_current_joueur->getTypeGameplay()==Joueur::TypeGameplay::RPG &&
								m_current_joueur->getRPG()->hero()==u)
							setSousStateType(TypeState::SPAWN_STATE);
					}
				}
			}
			break;
		case EngineMessageType::SUBIR_DEGATS:
			{
				Equipe *e = getEquipe(message.ints[TEAM_ID]);
				if(e)
				{
					Unite *u = e->getUnite(message.ints[OBJECT_ID]);
					if(u)
					{
						u->subirDegats(message.ints[OBJECT_HEAL]);
						std::cout << message.ints[OBJECT_HEAL] << std::endl;
					}
				}
			}
			break;
	}
}
GameEngine::Type ClientGameEngine::getTypeServerClient() const
{
	return GameEngine::Type::CLIENT;
}
CameraManager* ClientGameEngine::cameraManager() const
{
	return m_camManager;
}
void ClientGameEngine::setSousStateType(TypeState t)
{
    m_type_sous_state = t;
    m_change_sous_state = true;
}
Joueur* ClientGameEngine::getCurrentJoueur()
{
    return m_current_joueur;
}
void ClientGameEngine::work()
{
	GameEngine::work();
	if(m_map->getLoaded())
	{
		if(m_change_sous_state)
		{
			if(m_sous_state)
			{
				m_sous_state->exit();
				delete m_sous_state;
			}
			switch(m_type_sous_state)
			{
				case TEAM_LIST:
					m_sous_state = new TeamList(nullptr, this);
					break;
				case TEAM_STATE:
					m_sous_state = new TeamState(nullptr, this);
					break;
				case SPAWN_STATE:
					m_sous_state = new SpawnState(nullptr, this);
					break;
				default:
					m_sous_state = nullptr;
			}
			if(m_sous_state)
				m_sous_state->enter();
			m_change_sous_state = false;
		}
		if(m_sous_state)
			m_sous_state->work(0);
		CommandConfig* commandes = Config::get()->getCommandConfig();
		if(m_current_joueur->getTypeGameplay() == Joueur::RPG)
		{
			if(m_current_joueur->getRPG()->hero())
			{
				Hero* hero = m_current_joueur->getRPG()->hero();
				hero->setGauche(commandes->eventActif(CommandConfig::KeyType::RPG_KEY, CommandConfig::KeyRPG::RPG_LEFT));
				hero->setDroite(commandes->eventActif(CommandConfig::KeyType::RPG_KEY, CommandConfig::KeyRPG::RPG_RIGHT));
				hero->setAvancer(commandes->eventActif(CommandConfig::KeyType::RPG_KEY, CommandConfig::KeyRPG::RPG_FORWARD));
				hero->setReculer(commandes->eventActif(CommandConfig::KeyType::RPG_KEY, CommandConfig::KeyRPG::RPG_BACKWARD));
				if(commandes->eventActif(CommandConfig::KeyType::RPG_KEY, CommandConfig::KeyRPG::RPG_JUMP))
					hero->sauter();
				hero->tournerGaucheDroite(OgreContextManager::get()->getInputManager()->getMouse()->getMouseState().X.rel*-0.01);
				m_camManager->camera()->setPosition(hero->position()+Vector3D(0,0,10));
				m_camManager->camera()->setOrientation(hero->rotation());
				ClientNetworkEngine* net = static_cast<ClientNetworkEngine*>(m_manager->getNetwork());
				net->sendRpgPosition();
				hero->tournerGaucheDroite(OgreContextManager::get()->getInputManager()->getMouse()->getMouseState().X.rel*-Config::get()->getCommandConfig()->getMouseSensibility());
                hero->lookUpDown(OgreContextManager::get()->getInputManager()->getMouse()->getMouseState().Y.rel*-Config::get()->getCommandConfig()->getMouseSensibility());

				m_camManager->cameraContainer()->update(0);
			}
		}
		else if(m_current_joueur->getTypeGameplay() == Joueur::RTS)
		{

		}
	}
	OIS::Keyboard* key = OgreContextManager::get()->getInputManager()->getKeyboard();
	debug->setDebugMode(key->isKeyDown(OIS::KC_F1));
	m_world->debugDrawWorld();
	debug->step();
}
void ClientGameEngine::SetLayoutRts()
{
    LayoutRTS* MyLayoutRTS = new LayoutRTS(m_current_joueur);
    MyLayoutRTS->enter();

    CameraRTS* MyCameraRTS = new CameraRTS();
    MyCameraRTS->setCamera(m_camManager->camera());
    m_chat->hide();

    setSousStateType(PLAYING_RTS);
}
