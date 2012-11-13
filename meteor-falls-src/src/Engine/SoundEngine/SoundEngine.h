#include <string.h>
#include <iostream>
#include <stdio.h>
#include <map>
#include <SFML/Audio.hpp>

class SoundEngine
{
    public:
        SoundEngine();
        void readAudio(std::string path);

        void set_Volume(int type_son, int new_volume);
        void set_Stop(bool stop){m_stop = true;} ;
        void set_Pause(bool pause) {m_pause = true;};

        int get_Audio_State(); // stop / pause / read
        int get_Volume();

    private:

        bool m_stop;
        bool m_pause;
        std::map <int, std::string> m_audio_state;
        int m_volume;

};
