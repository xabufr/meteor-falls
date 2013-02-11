#ifndef SOUNDCONFIG_H_INCLUDED
#define SOUNDCONFIG_H_INCLUDED

class SoundConfig
{
    public:
        SoundConfig();
        void defaultSoundConfig();
        void loadConfig();
        void saveConfig();
        bool getActivate(){return m_activate;}
        int getMusicVolume(){return m_music_volume;}
        int getAmbiantVolume(){return m_ambiant_volume;}
        int getEffectVolume(){return m_effect_volume;}
        int getInterfaceVolume(){return m_interface_volume;}
    private:
        bool m_activate;
        int m_music_volume;
        int m_ambiant_volume;
        int m_effect_volume;
        int m_interface_volume;
};

#endif // SOUNDCONFIG_H_INCLUDED
