#include "OgreApplication.h"
#include "Utils/Exception/BasicException.h"
#include <OgreConfigFile.h>
#include <OgreWindowEventUtilities.h>
#include <OgreResourceBackgroundQueue.h>
#include "LoadingScreen.h"

OgreApplication::OgreApplication()
{
    #ifdef RELEASE
    m_root = new Ogre::Root("plugins.cfg", "ogre.cfg", "Ogre.log");
    #elif defined DEBUG
    m_root = new Ogre::Root("plugins_debug.cfg", "ogre_debug.cfg", "Ogre_debug.log");
    #else
    m_root = new Ogre::Root();
    #endif // DEBUG

    if(!(m_root->restoreConfig() || m_root->showConfigDialog()))
    {
        THROW_BASIC_EXCEPTION("Aucune configuration de rendu");
    }

    m_window = m_root->initialise(true, "Meteor-Falls");
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
    m_ceguiStarted=false;
    m_bootstrapCegui();
}

OgreApplication::~OgreApplication()
{
    //dtor
}
void OgreApplication::LoadRessources(std::string fileName)
{
    m_ParcourirRessource(fileName, true);
}

void OgreApplication::UnloadRessources(std::string fileName)
{
    m_ParcourirRessource(fileName, false);
}
void OgreApplication::m_ParcourirRessource(std::string &fileName, bool add)
{
    Ogre::ConfigFile file;
    file.load(fileName);
    Ogre::ConfigFile::SectionIterator sec_it = file.getSectionIterator();

    std::string sec_name, type_name, archive;
    std::vector<std::string> groups;
    while(sec_it.hasMoreElements())
    {
        sec_name = sec_it.peekNextKey();
        if(!sec_name.empty())
            groups.push_back(sec_name);
        Ogre::ConfigFile::SettingsMultiMap *settings = sec_it.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator it;
        for(it=settings->begin(); it!=settings->end();++it)
        {
            type_name = it->first;
            archive = it->second;
            if(add)
                Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archive, type_name, sec_name);
            else
                Ogre::ResourceGroupManager::getSingleton().removeResourceLocation(archive, sec_name);
        }
    }
    if (add)
    {
        m_listener.start();
        LoadingScreen *load = 0;
        if(m_ceguiStarted)
        {
            load = new LoadingScreen;
            load->show();
        }
        m_listener.setLoadingScreen(load);
        for(auto group : groups)
        {
            Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup(group);
            Ogre::ResourceGroupManager::getSingleton().loadResourceGroup(group);
        }
        m_listener.finished();
    }
}
bool OgreApplication::RenderOneFrame()
{
    Ogre::WindowEventUtilities::messagePump();
    return (!m_window->isClosed()) && m_root->renderOneFrame();
}

Ogre::RenderWindow* OgreApplication::getWindow()
{
    return m_window;
}

Ogre::Root* OgreApplication::getRoot()
{
    return m_root;
}
CEGUI::Renderer* OgreApplication::getCEGUI()
{
    return m_ceguiRenderer;
}
void OgreApplication::m_bootstrapCegui()
{
    m_ceguiRenderer = &CEGUI::OgreRenderer::bootstrapSystem();
    LoadRessources("bootstrap.cfg");

    CEGUI::Imageset::setDefaultResourceGroup("Imagesets");
    CEGUI::Font::setDefaultResourceGroup("Fonts");
    CEGUI::Scheme::setDefaultResourceGroup("Schemes");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
    CEGUI::WindowManager::setDefaultResourceGroup("Layouts");

    CEGUI::SchemeManager::getSingleton().create("Interface.scheme");
    CEGUI::SchemeManager::getSingleton().create("OgreTray.scheme");
    m_ceguiStarted = true;
}
/*
 * First param -> path
 * Second param -> type
 * */
void OgreApplication::AddResourceLocation(std::vector<std::pair<std::string, std::string>> locations)
{
	for(auto location : locations){
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(location.first, location.second, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,true);
        std::cout << "adding :" << location.first << std::endl;
	}
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}
