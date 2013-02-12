#ifndef GRAPHICCONFIG_H_INCLUDED
#define GRAPHICCONFIG_H_INCLUDED

#include <OgreConfigOptionMap.h>
#include <vector>

class GraphicConfig
{
public:
    GraphicConfig();
    ~GraphicConfig();
    void defaultGraphicConfig();
    void loadConfig();
    void saveConfig();
    std::vector<Ogre::ConfigOption> getConfig(){return m_config;}
private:
    std::vector<Ogre::ConfigOption> m_config;
};

#endif // GRAPHICCONFIG_H_INCLUDED
