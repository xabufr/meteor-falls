#include <string.h>
#include <iostream>
#include <stdio.h>
#include <map>
#include <SFML/Audio.hpp>

class SoundEngine
{
    public:
        SoundEngine();

        // classic
        void addMusic(std::string path); // ajouter une musique au vector
        void readAudio();

        // control
        void up_Volume(int type_son);
        void down_Volume(int type_son);

        // state
        void set_Stop(bool stop){m_stop = true;} ;
        void set_Pause(bool pause) {m_pause = true;};
        void set_Loop(bool loop) {m_loop = loop;};

        // fade
        void make_Fadeout(int sec_restantes);
        void make_Fadein();
        bool isFading_In();
        bool isFading_Out(int sec_restantes);

        // situation
        void setPos_Depth(int SoundPlayed, int distance); // étouffage du son par rapport à la distance
        void setPos_3D(int SoundPlayed, sf::Vector3f p_vector3f); // situer le son dans l'espace (droite / gauche)
        void setPos_3D(int SoundPlayed, int x, int y, int z); // situer le son dans l'espace (droite / gauche)
        int getPos_Depth() {return m_depth;};
        sf::Vector3f getPos_3D() {return m_music->getPosition();};
        int get_attenuation() { return m_music->getAttenuation();};

        // getters
        int get_Audio_State(); // stop / pause / read
        int get_Volume();
        int get_Temps_Chanson();
        int get_Time_Elapsed();
        int get_HowManyMusic();
        int get_MusicPlayed();
        bool get_Loop();


    private:

        int m_depth;
        bool m_stop;
        bool m_pause;
        bool m_fading_in;
        bool m_fading_out;
        int m_volume;
        int m_music_playing; // indice de la musique jouée dans le tableau
        bool m_loop; // activer ou non la redondance de la playlist

        sf::Music *m_music;
        sf::Clock *m_temps_ecoule;
        std::map <int, std::string> m_audio_state;
        std::vector <std::string> m_vector_paths_musiques; // vecteur de chemins de musiques

        void m_set_Volume(int type_son, int new_volume);

};
