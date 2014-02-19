#include "LoadingListener.h"
#include <iostream>
#include "LoadingScreen.h"

using namespace Ogre;

void LoadingListener::start()
{
    Ogre::ResourceGroupManager::getSingleton().addResourceGroupListener(this);
}
void LoadingListener::finished()
{
    Ogre::ResourceGroupManager::getSingleton().removeResourceGroupListener(this);
}
LoadingListener::LoadingListener() : m_loadingScreen(0)
{
}
LoadingListener::~LoadingListener()
{
}
void LoadingListener::resourceGroupScriptingStarted(const String& groupName, size_t scriptCount)
{
    if(m_loadingScreen)
        m_loadingScreen->setGroup(groupName);
}
void LoadingListener::scriptParseStarted(const String& scriptName, bool& skipThisScript)
{

}
void LoadingListener::scriptParseEnded(const String& scriptName, bool skipped)
{

}
void LoadingListener::resourceGroupScriptingEnded(const String& groupName)
{

}
void LoadingListener::resourceGroupLoadStarted(const String& groupName, size_t resourceCount)
{

}
void LoadingListener::resourceLoadStarted(const ResourcePtr& resource)
{
    if(m_loadingScreen)
        m_loadingScreen->update(resource->getOrigin());
}
void LoadingListener::resourceLoadEnded(void)
{

}
void LoadingListener::worldGeometryStageStarted(const String& description)
{

}
void LoadingListener::worldGeometryStageEnded(void)
{

}
void LoadingListener::resourceGroupLoadEnded(const String& groupName)
{

}
