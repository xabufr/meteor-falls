#include <string.h>
#include <iostream>
#include <stdio.h>
#include <map>
#include <SFML/Audio.hpp>

class SoundEngine
{
    public:
        SoundEngine();
        void addMusic(std::string path); // ajouter une musique au vector
        void readAudio();

        void set_Volume(int type_son, int new_volume);
        void up_Volume(int type_son);
        void down_Volume(int type_son);
        void set_Stop(bool stop){m_stop = true;} ;
        void set_Pause(bool pause) {m_pause = true;};
        void set_Loop(bool loop) {m_loop = loop;};

        int get_Audio_State(); // stop / pause / read
        int get_Volume();
        int get_Temps_Chanson();
        int get_Time_Elapsed();
        int get_HowManyMusic();
        int get_MusicPlayed();
        bool get_Loop();

        void make_Fadeout(int sec_restantes);

    private:

        bool m_stop;
        bool m_pause;
        std::map <int, std::string> m_audio_state;
        int m_volume;
        int m_music_playing; // indice de la musique jouée dans le tableau
        sf::Music m_music;
        sf::Clock m_temps_ecoule;
        std::vector <std::string> m_vector_paths_musiques; // vecteur de chemins de musiques
        bool m_loop; // activer ou non la redondance de la playlist

};
