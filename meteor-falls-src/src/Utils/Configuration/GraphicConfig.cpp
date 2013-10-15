#include "GraphicConfig.h"
#include "../../Engine/GraphicEngine/Ogre/ogrecontextmanager.h"
#include "../../Engine/GraphicEngine/Ogre/OgreApplication.h"
#include "../../Engine/ScriptEngine/XmlDocumentManager.h"
#include <boost/property_tree/xml_parser.hpp>
#include "../../precompiled/lexical_cast.h"
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
    m_quality_water = 3;
}

void GraphicConfig::loadConfig()
{
    auto it = Ogre::Root::getSingleton().getRenderSystem()->getConfigOptions().begin();
    auto itF = Ogre::Root::getSingleton().getRenderSystem()->getConfigOptions().end();
    for (it; it != itF; ++it)
        m_config.push_back(it->second);

    try
    {
		XmlDocumentManager::Document& doc = XmlDocumentManager::get()->getDocument("config.cfg");
		m_quality_water = doc.get<int>("configuration.graphic.water.xmlattr.quality");
    }
    catch(...)
    {
        defaultGraphicConfig();
    }
}

void GraphicConfig::saveConfig()
{
	XmlDocumentManager::Document& document = XmlDocumentManager::get()->getDocument("config.cfg");
	document.put("configuration.graphic.water.xmlattr.quality", m_quality_water);

	boost::property_tree::write_xml("config.cfg", document);

    for (int i=0; i < m_config.size(); ++i)
    {
        std::string key = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChild("OptionState")->getChild("TextGraphic"+boost::lexical_cast<std::string>(i))->getText().c_str();
        CEGUI::Combobox *combobox= (CEGUI::Combobox*)(CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChild("OptionState")->getChild("ComboBoxGraphic"+boost::lexical_cast<std::string>(i)));
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
