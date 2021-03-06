#ifndef PLAYLIST_H
#define PLAYLIST_H
#include <string.h>
#include <stdio.h>
#include <map>
#include "precompiled/sfml_audio.h"
#include "Engine/SoundEngine/Fade.h"
#include "../../Utils/singleton.h"

class Playlist: public Singleton<Playlist>
{
    friend class Singleton<Playlist>;
    public:
        void addMusic(std::string path, std::string group); // ajouter une musique au vector et au groupe

        // control/*
        void set_Volume(int new_volume);
        void work();

        // state
        void set_Stop(bool stop);
        void set_Pause(bool pause);
        void set_Loop(bool loop) {m_loop = loop;};

        // getters
        int get_Volume() {return m_volume;};
        int get_Temps_Chanson();
        int get_HowManyMusic();
        int get_MusicPlayed();
        bool get_Loop() {return m_loop;};
        bool get_Pause(){return m_pause;}
        bool get_Stop(){return m_stop;}
        int get_Time_Elapsed();
        void select_group(std::string group);

        // parametres
        void set_fade_time(int time);
        void set_type_transition(Fade::fadeFunction string);

        static Playlist* get(){return Singleton<Playlist>::get();};
        static void loadFile(const std::string &file);

    protected:
        Playlist();

    private:
        int m_fade_time;
        bool m_stop;
        bool m_pause;
        int m_volume;
        bool m_loop; // activer ou non la redondance de la playlist
        bool first_song;

        Fade MonFade;
        sf::Clock m_temps_ecoule;
        sf::Music *m_music;
        std::map <int, std::string> m_audio_state;
        std::map <std::string, std::vector <std::string> > m_vector_paths_group_musiques; // vecteur de chemins de musiques
        std::string m_groupe_courant;
        std::map <std::string, int > m_music_playing; // indice de la musique jouée dans le tableau

        void readPlaylist();
};

#endif // PLAYLIST_H

// parametrer le temps des fade
// parametrer le type de transition
