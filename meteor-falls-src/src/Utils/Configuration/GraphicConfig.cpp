#include "GraphicConfig.h"
#include "../../precompiled/lexical_cast.h"
#include "Engine/GraphicEngine/Ogre/ogrecontextmanager.h"
#include "Engine/GraphicEngine/Ogre/OgreApplication.h"
#include "../../Engine/ScriptEngine/XmlDocumentManager.h"
#include "../../precompiled/lexical_cast.h"
#include "Utils/Exception/FileNotFound.h"
#include <iostream>
#include <rapidxml_print.hpp>
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
        rapidxml::xml_document<>* doc = XmlDocumentManager::get()->getDocument("config.cfg");
        rapidxml::xml_node<>* root = doc->first_node("configuration");
        rapidxml::xml_node<>* graphic = root->first_node("graphic");

        m_quality_water = boost::lexical_cast<int>(graphic->first_node("water")->first_attribute("quality")->value());
    }
    catch(FileNotFound &e)
    {
        defaultGraphicConfig();
    }
}

void GraphicConfig::saveConfig()
{
    rapidxml::xml_document<>* document = XmlDocumentManager::get()->getDocument("config.cfg");
    rapidxml::xml_node<>* root;
    rapidxml::xml_node<>* graphic;
    rapidxml::xml_node<>* water;

    if (!document->first_node("configuration"))
    {
        root = document->allocate_node(rapidxml::node_type::node_element, "configuration");
        document->append_node(root);
    }
    else
        root = document->first_node("configuration");

    if (!root->first_node("graphic"))
    {
        graphic = document->allocate_node(rapidxml::node_type::node_element, "graphic");
        root->append_node(graphic);
    }
    else
        graphic = root->first_node("graphic");

    if (!graphic->first_node("water"))
    {
        water = document->allocate_node(rapidxml::node_type::node_element, "water");
        water->append_attribute(document->allocate_attribute("quality", document->allocate_string(boost::lexical_cast<std::string>(m_quality_water).c_str())));
        graphic->append_node(water);
    }
    else
    {
        water = graphic->first_node("water");
        water->first_attribute("quality")->value(document->allocate_string(boost::lexical_cast<std::string>(m_quality_water).c_str()));
    }

    std::ofstream file;
    file.open("config.cfg");
    if (file.bad())
        throw FileNotFound("config.cfg");
    file << *document;
    file.close();

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
