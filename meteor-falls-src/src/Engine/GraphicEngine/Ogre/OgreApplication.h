#ifndef OGREAPPLICATION_H
#define OGREAPPLICATION_H

#include <OgreRenderWindow.h>
#include <OgreRoot.h>
#include <CEGUI.h>
#include <RendererModules/Ogre/CEGUIOgreRenderer.h>
#include "LoadingListener.h"

class OgreApplication
{
    public:
        OgreApplication();
        void LoadRessources(std::string fileName);
		void AddResourceLocation(std::vector<std::pair<std::string, std::string>>);
        void UnloadRessources(std::string fileName);
        virtual ~OgreApplication();
        bool RenderOneFrame();

        Ogre::RenderWindow* getWindow();
        Ogre::Root*         getRoot();
        CEGUI::Renderer* getCEGUI();


    protected:
    private:
        void m_ParcourirRessource(std::string &fileName, bool add);
        void m_bootstrapCegui();
        bool m_ceguiStarted;
        Ogre::Root *m_root;
        Ogre::RenderWindow *m_window;
        CEGUI::Renderer *m_ceguiRenderer;
        LoadingListener m_listener;
};

#endif // OGREAPPLICATION_H
