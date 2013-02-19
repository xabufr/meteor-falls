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
    void setQualityWater(int v){m_quality_water=v;}
    std::vector<Ogre::ConfigOption> getConfig(){return m_config;}
    int getQualityWater(){return m_quality_water;}
private:
    std::vector<Ogre::ConfigOption> m_config;
    int m_quality_water;
};

#endif // GRAPHICCONFIG_H_INCLUDED
