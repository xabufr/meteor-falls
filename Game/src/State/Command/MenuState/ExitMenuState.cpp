#include "ExitMenuState.h"
#include "Engine/GraphicEngine/Ogre/ogrecontextmanager.h"
#include "Engine/GraphicEngine/Ogre/OgreApplication.h"
#include <string>
#include <vector>

ExitMenuState::ExitMenuState():Command("exit")
{

}

ExitMenuState::~ExitMenuState()
{

}

void ExitMenuState::use(std::string s)
{
    OgreContextManager::get()->getOgreApplication()->getWindow()->destroy();
}
