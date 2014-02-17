#include "rpgstate.h"
#include "../ClientGameEngine.h"
#include "../Joueur/JoueurRPG.h"
#include "../Heros/Hero.h"

#include <Utils/Configuration/CommandConfig.h>
#include <Utils/Configuration/Config.h>

#include <Engine/GraphicEngine/Ogre/ogrecontextmanager.h>
#include <Engine/GraphicEngine/Ogre/OgreWindowInputManager.h>

#include <Engine/NetworkEngine/clientnetworkengine.h>
#include <Engine/EngineManager/EngineManager.h>
#include "../Preface/SpawnState.h"

#include "../Camera/CameraRPG.h"
#include "../Camera/CameraManager.h"

RPGState::RPGState(StateManager *manager, ClientGameEngine *clientGameEngine): State(manager),
        m_clientGameEngine(clientGameEngine)
{
    m_spawnState = new SpawnState(nullptr, clientGameEngine);
    m_camera = new CameraRPG(m_clientGameEngine->getCurrentJoueur()->getRPG()->hero());
    m_hero = m_clientGameEngine->getCurrentJoueur()->getRPG()->hero();
}

RPGState::~RPGState()
{
    delete m_camera;
}


bool RPGState::isVisible()
{
    return true;
}

void RPGState::enter()
{
    m_clientGameEngine->cameraManager()->setCameraContener(m_camera);
    OgreContextManager::get()->getInputManager()->addMouseListener(this);
}

void RPGState::exit()
{
    m_clientGameEngine->cameraManager()->setCameraContener(nullptr);
    OgreContextManager::get()->getInputManager()->delMouseListener(this);
}

ret_code RPGState::work(const TimeDuration &elapsed)
{
    CommandConfig* commandes = Config::get()->getCommandConfig();
    m_hero->setGauche(commandes->eventActif(CommandConfig::KeyType::RPG_KEY,
                                            CommandConfig::KeyRPG::RPG_LEFT));
    m_hero->setDroite(commandes->eventActif(CommandConfig::KeyType::RPG_KEY,
                                            CommandConfig::KeyRPG::RPG_RIGHT));
    m_hero->setAvancer(commandes->eventActif(CommandConfig::KeyType::RPG_KEY,
                                             CommandConfig::KeyRPG::RPG_FORWARD));
    m_hero->setReculer(commandes->eventActif(CommandConfig::KeyType::RPG_KEY,
                                             CommandConfig::KeyRPG::RPG_BACKWARD));
    if (commandes->eventActif(CommandConfig::KeyType::RPG_KEY,
                              CommandConfig::KeyRPG::RPG_JUMP))
        m_hero->sauter();

    ClientNetworkEngine* net = static_cast<ClientNetworkEngine*>(m_clientGameEngine->getManager()->getNetwork());
    net->sendRpgPosition();
}

bool RPGState::mouseMoved(const OIS::MouseEvent &arg)
{
    m_hero->tournerGaucheDroite(arg.state.X.rel *
    -Config::get()->getCommandConfig()->getMouseSensibility());
    m_hero->lookUpDown(arg.state.Y.rel
                       * Config::get()->getCommandConfig()->getMouseSensibility());
}

bool RPGState::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{

}

bool RPGState::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{

}
