#include "OgreApplication.h"
#include "Utils/Exception/BasicException.h"

OgreApplication::OgreApplication()
{
    #ifdef RELEASE
    m_root = new Ogre::Root("plugins.cfg", "ogre.cfg", "Ogre.log");
        #elifdef DEBUG
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
    m_ceguiRenderer = &CEGUI::OgreRenderer::bootstrapSystem();
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
    while(sec_it.hasMoreElements())
    {
        sec_name = sec_it.peekNextKey();
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
        Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
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
