#ifndef LOADINGLISTENER_H
#define LOADINGLISTENER_H
#include <OgreResourceGroupManager.h>

class LoadingScreen;
class LoadingListener: public Ogre::ResourceGroupListener
{
    public:
        LoadingListener();
        virtual ~LoadingListener();

        void start();
        void finished();
        void setLoadingScreen(LoadingScreen* l){m_loadingScreen=l;}


        virtual void resourceGroupScriptingStarted(const Ogre::String& groupName, size_t scriptCount);
		virtual void scriptParseStarted(const Ogre::String& scriptName, bool& skipThisScript);
		virtual void scriptParseEnded(const Ogre::String& scriptName, bool skipped);
		virtual void resourceGroupScriptingEnded(const Ogre::String& groupName);
		virtual void resourceGroupPrepareStarted(const Ogre::String& groupName, size_t resourceCount)
                { (void)groupName; (void)resourceCount; }

		virtual void resourcePrepareStarted(const Ogre::ResourcePtr& resource)
                { (void)resource; }

        virtual void resourcePrepareEnded(void) {}
        virtual void worldGeometryPrepareStageStarted(const Ogre::String& description)
        { (void)description; }
        virtual void worldGeometryPrepareStageEnded(void) {}
        virtual void resourceGroupPrepareEnded(const Ogre::String& groupName)
        { (void)groupName; }
		virtual void resourceGroupLoadStarted(const Ogre::String& groupName, size_t resourceCount);
		virtual void resourceLoadStarted(const Ogre::ResourcePtr& resource);
        virtual void resourceLoadEnded(void);
        virtual void worldGeometryStageStarted(const Ogre::String& description);
        virtual void worldGeometryStageEnded(void);
        virtual void resourceGroupLoadEnded(const Ogre::String& groupName);


    protected:
    private:
        LoadingScreen *m_loadingScreen;
};

#endif // LOADINGLISTENER_H
