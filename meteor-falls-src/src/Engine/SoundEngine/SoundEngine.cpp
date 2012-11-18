#include "SoundEngine.h"

SoundEngine::SoundEngine()
{
        m_stop = true;
        m_pause = false;
        m_volume = 100;
        m_music_playing = 0;
        m_music = new sf::Music;
}

void SoundEngine::readAudio()
{

    if (m_music_playing + 1 > m_vector_paths_musiques.size())
        m_music_playing = 0;

    if (get_Audio_State() != 1)
    {
        if (!m_music->openFromFile(m_vector_paths_musiques[(m_music_playing)]))// musique en cours (tableau commence a zero)
        {

        }
        m_music_playing++;
        std::cout << " musique jouee :  " << m_music_playing<< std::endl;
        m_music->play();
        m_temps_ecoule->restart();

        if (m_music_playing > 1)
        {
            m_fading_in = true;
            m_music->setVolume(1);
            m_volume = 1;
            std::cout << " Volume set 1  " << std::endl;
        }

        else
            m_fading_in = false;

        if (m_music->getDuration().asSeconds() < 20)
            m_fading_out = true;
        else
            m_fading_out = false;

        m_stop = 0;
        m_pause = 0;
        m_loop = 1;

    }

}

void SoundEngine::m_set_Volume(int type_son, int new_volume)
{

    m_volume = new_volume;
    if (m_volume > 100)
        m_volume = 100;

    m_music->setVolume(m_volume);
}

void SoundEngine::up_Volume(int type_son)
{

    m_volume += 10;
    if (m_volume > 100)
        m_volume = 100;

    m_music->setVolume(m_volume);

}

void SoundEngine::down_Volume(int type_son)
{

    m_volume -= 10;
    if (m_volume < 0)
        m_volume = 0;

    m_music->setVolume(m_volume);
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
    int sec_totale_chanson = m_music->getDuration().asSeconds();
    return sec_totale_chanson;
}

int SoundEngine::get_Time_Elapsed()
{
    int sec_ecoulees_horloge = m_temps_ecoule->getElapsedTime().asSeconds();
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
   // int Pourcentage_Destack = 0;
   // Pourcentage_Destack = m_volume / sec_restantes ; // calcul du %age de volume decroissant

    // m_volume -= (m_volume * Pourcentage_Destack) / 100; // destack constant

    int new_volume;

    new_volume = (sec_restantes * 5);
    m_set_Volume(1,new_volume);
    std::cout << "ancien volume : " << get_Volume() << std::endl;
    std::cout << "new volume : " << new_volume << std::endl;
    // fonction
}

void SoundEngine::make_Fadein()
{
    int Pourcentage_Stack = 0;
    int new_volume = 0;

    new_volume = 5 * (m_temps_ecoule->getElapsedTime().asSeconds()); // calcul du volume croissant

    if (new_volume < 1)
        new_volume = 1;

    m_set_Volume(1,new_volume);

}

bool SoundEngine::isFading_In()
{

    if (m_temps_ecoule->getElapsedTime().asSeconds() > 20)
        m_fading_in = false;

            std::cout << "volume" << m_volume<<std::endl;
        return m_fading_in;
}

bool SoundEngine::isFading_Out(int sec_restantes)
{

    if (sec_restantes < 20)
        m_fading_out = true;
    else
        m_fading_out = false;

            std::cout << "volume" << m_volume<<std::endl;
        return m_fading_out;
}

void SoundEngine::setPos_Depth(int SoundPlayed, int distance)
{

    m_depth = distance;
    m_music->setAttenuation(m_depth);

}

void SoundEngine::setPos_3D(int SoundPlayed, sf::Vector3f p_vector3f)
{

 //   m_vector3f = p_vector3f;
    m_music->setPosition(p_vector3f);

}

void SoundEngine::setPos_3D(int SoundPlayed, int x, int y, int z)
{


    m_music->setPosition(x,y,z);

}


