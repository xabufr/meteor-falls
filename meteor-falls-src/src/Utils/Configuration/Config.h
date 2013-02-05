#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include "../singleton.h"
#include "SoundConfig.h"
//#include "GraphicConfig.h"
//#include "CommandConfig.h"

class SoundConfig;
class GraphicConfig;
class CommandConfig;
class Config: public Singleton<Config>
{
    public:
        Config(){m_sound_config = SoundConfig::get();}
        void defaultConfig(){m_sound_config->defaultSoundConfig();
                            //m_graphic_config->defaultGraphicConfig();
                            //m_command_config->defaultCommandConfig();
                            }
        SoundConfig *getSoundConfig(){return m_sound_config;}
        GraphicConfig *getGraphicConfig(){return m_graphic_config;}
        CommandConfig *getCommandConfig(){return m_command_config;}
    private:
        SoundConfig *m_sound_config;
        GraphicConfig *m_graphic_config;
        CommandConfig *m_command_config;
};

#endif // CONFIG_H_INCLUDED
