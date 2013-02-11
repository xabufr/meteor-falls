#include "GraphicConfig.h"
#include "../../precompiled/lexical_cast.h"
#include "Engine/GraphicEngine/Ogre/ogrecontextmanager.h"
#include "Engine/GraphicEngine/Ogre/OgreApplication.h"
#include <OgreRoot.h>
#include <CEGUI.h>
#include <string>

GraphicConfig::GraphicConfig()
{

}

GraphicConfig::~GraphicConfig()
{

}

void GraphicConfig::defaultGraphicConfig()
{

}

void GraphicConfig::loadConfig()
{
    auto it = Ogre::Root::getSingleton().getRenderSystem()->getConfigOptions().begin();
    auto itF = Ogre::Root::getSingleton().getRenderSystem()->getConfigOptions().end();
    for (it; it != itF; ++it)
        m_config.push_back(it->second);
}

void GraphicConfig::saveConfig()
{
    for (int i=0; i < m_config.size(); ++i)
    {
        std::string key = CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->getChild("TextGraphic"+boost::lexical_cast<std::string>(i))->getText().c_str();
        CEGUI::Combobox *combobox= (CEGUI::Combobox*)(CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->getChild("ComboBoxGraphic"+boost::lexical_cast<std::string>(i)));
        std::string value = combobox->getSelectedItem()->getText().c_str();
        Ogre::Root::getSingleton().getRenderSystem()->setConfigOption(key, value);
    }
    if (!Ogre::Root::getSingleton().getRenderSystem()->validateConfigOptions().empty())
        return;
    Ogre::Root::getSingleton().saveConfig();
    /*OgreContextManager::get()->reinitialise();

    Ogre::SceneManager *scene_mgr = OgreContextManager::get()->getOgreApplication()->getRoot()->getSceneManager("Menu");
    Ogre::Viewport *vp = OgreContextManager::get()->getOgreApplication()->getWindow()->addViewport(scene_mgr->getCamera("MenuCam"));
    vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));*/
}
