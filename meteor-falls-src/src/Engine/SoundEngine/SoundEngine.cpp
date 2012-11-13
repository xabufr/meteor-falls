#include "SoundEngine.h"

SoundEngine::SoundEngine()
{
        m_stop = true;
        m_pause = false;
        m_volume = 100;
        m_music_playing = 0;
}

void SoundEngine::readAudio()
{

    if (m_music_playing + 1 > m_vector_paths_musiques.size())
        m_music_playing = 0;

    if (get_Audio_State() != 1)
    {
        if (!m_music.openFromFile(m_vector_paths_musiques[(m_music_playing)]))// musique en cours (tableau commence a zero)
        {

        }
        m_music.play();
        m_music_playing++;
        m_temps_ecoule.restart();
        m_stop = 0;
        m_pause = 0;
        m_loop = 1;
    }

}

void SoundEngine::set_Volume(int type_son, int new_volume)
{

    m_volume = new_volume;
    if (m_volume > 100)
        m_volume = 100;

    m_music.setVolume(m_volume);
}

void SoundEngine::up_Volume(int type_son)
{

    m_volume += 10;
    if (m_volume > 100)
        m_volume = 100;

    m_music.setVolume(m_volume);

}

void SoundEngine::down_Volume(int type_son)
{

    m_volume -= 10;
    if (m_volume < 0)
        m_volume = 0;

    m_music.setVolume(m_volume);
}

int SoundEngine::get_Volume()
{
    return m_volume;
}

int SoundEngine::get_Audio_State()
{

    // 1 : play
    // 2 : pause
    // 3 : no music

    if (m_stop == 1)
    m_music_playing = 0; // debut de la liste de lecture
        return 3;

    if (m_pause == 1)
        return 2;

    else
        return 1;

}


int SoundEngine::get_Temps_Chanson()
{
    int sec_totale_chanson = m_music.getDuration().asSeconds();
    return sec_totale_chanson;
}

int SoundEngine::get_Time_Elapsed()
{
    int sec_ecoulees_horloge = m_temps_ecoule.getElapsedTime().asSeconds();
    return sec_ecoulees_horloge;
}

void SoundEngine::addMusic(std::string path)
{
    m_vector_paths_musiques.push_back(path);
}

int SoundEngine::get_HowManyMusic()
{
    return m_vector_paths_musiques.size();
}

int SoundEngine::get_MusicPlayed()
{
    return m_music_playing;
}

bool SoundEngine::get_Loop()
{
    return m_loop;
}

void SoundEngine::make_Fadeout(int sec_restantes)
{

    // fonction

}
