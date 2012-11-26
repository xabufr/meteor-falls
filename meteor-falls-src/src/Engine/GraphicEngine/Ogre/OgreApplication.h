#ifndef OGREAPPLICATION_H
#define OGREAPPLICATION_H

#include <Ogre.h>
#include <CEGUI.h>
#include <RendererModules/Ogre/CEGUIOgreRenderer.h>

class OgreApplication
{
    public:
        OgreApplication();
        void LoadRessources(std::string fileName);
        void UnloadRessources(std::string fileName);
        virtual ~OgreApplication();
        bool RenderOneFrame();

        Ogre::RenderWindow* getWindow();
        Ogre::Root*         getRoot();
        CEGUI::Renderer* getCEGUI();


    protected:
    private:
        void m_ParcourirRessource(std::string &fileName, bool add);
        Ogre::Root *m_root;
        Ogre::RenderWindow *m_window;
        CEGUI::Renderer *m_ceguiRenderer;
};

#endif // OGREAPPLICATION_H
