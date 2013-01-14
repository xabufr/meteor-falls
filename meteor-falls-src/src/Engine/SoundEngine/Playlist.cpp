#include "Playlist.h"
#include "../ScriptEngine/XmlDocumentManager.h"
#include "Utils/File.h"

Playlist::Playlist()
{
    m_stop = true;
    m_pause = false;
    m_volume = 100;
    m_music = new sf::Music;
    m_loop = true;
    m_temps_ecoule.restart();
    first_song = true;
}

void Playlist::select_group(std::string group)
{
    m_groupe_courant = group;
}


void Playlist::addMusic(std::string path, std::string group) // ajouter une musique au vector
{
    m_vector_paths_group_musiques[group].push_back(path);
    m_music_playing[group] = 0;
    // ecrire sur un doc xml
}


void Playlist::readPlaylist()
{
    if (m_loop)
    {
        if (m_music_playing[m_groupe_courant] > m_vector_paths_group_musiques[m_groupe_courant].size())
            m_music_playing[m_groupe_courant] = 0;
    }

    if (get_Audio_State() != 1) // different de stop
    {
        if (!m_music->openFromFile(m_vector_paths_group_musiques[m_groupe_courant][(m_music_playing[m_groupe_courant])]))// musique en cours (tableau commence a zero)
        {

        }
        m_music_playing[m_groupe_courant]++;
        m_music->play();
        m_temps_ecoule.restart();
        m_stop = false;
        m_pause = false;
    }

}


void Playlist::set_Volume(int type_son, int new_volume)
{
    m_volume = new_volume;

    if (m_volume > 100)
        m_volume = 100;


    if (m_volume < 0)
        m_volume = 0;

    m_music->setVolume(m_volume);
}


int Playlist::get_Audio_State() // stop / pause / read
{
    if (m_stop == true)
        m_music_playing[m_groupe_courant] = 0; // debut de la liste de lecture
    return 3;

    if (m_pause == true)
        return 2;

    else
        return 1;
}


int Playlist::get_Temps_Chanson()
{
    int sec_totale_chanson = m_music->getDuration().asSeconds();
    return sec_totale_chanson;
}


int Playlist::get_Time_Elapsed()
{
    int sec_ecoulees_horloge = m_temps_ecoule.getElapsedTime().asSeconds();
    return sec_ecoulees_horloge;
}


int Playlist::get_HowManyMusic()
{
    return m_vector_paths_group_musiques[m_groupe_courant].size();
}


int Playlist::get_MusicPlayed()
{
    return m_music_playing[m_groupe_courant];
}

void Playlist::work()
{

    int new_volume;

    if (first_song)
    {
        readPlaylist();
        first_song = false;
    }

    //  std::cout << "volume principal : " <<m_volume << std::endl;

    int sec_restantes =  get_Temps_Chanson() - m_temps_ecoule.getElapsedTime().asSeconds();
    /*  std::cout << "temps chanson : "<< get_Temps_Chanson() << std::endl;
      std::cout << "temps ecoule : "<< m_temps_ecoule.getElapsedTime().asSeconds() << std::endl;
      std::cout << "secondes rest : "<< sec_restantes << std::endl;*/


    if (sec_restantes <= m_fade_time)
    {
        MonFade.setType(Fade::fadeType::out);
        new_volume = MonFade.work(m_temps_ecoule.getElapsedTime().asMilliseconds(), m_music->getDuration().asMilliseconds(), 20000, m_volume);
        m_music->setVolume(new_volume);

        //  std::cout << "fadeout" << std::endl;
    }
    else if (m_temps_ecoule.getElapsedTime().asSeconds() <= m_fade_time)
    {
        MonFade.setType(Fade::fadeType::in);
        new_volume = MonFade.work(m_temps_ecoule.getElapsedTime().asMilliseconds(), m_music->getDuration().asMilliseconds(), 20000, m_volume);
        m_music->setVolume(new_volume);
    }
    else
    {
        m_music->setVolume(m_volume);
    }

    if (m_music->getStatus() == sf::SoundSource::Status::Stopped)
    {
        select_group(m_groupe_courant);
        m_music_playing[m_groupe_courant]++;
        readPlaylist();
    }
}


void Playlist::set_fade_time(int time)
{

    m_fade_time = time;

}

void Playlist::set_type_transition(Fade::fadeFunction string)
{

    if (string == Fade::fadeFunction::carre)
        MonFade.setFunction(Fade::fadeFunction::carre);
    else if (string == Fade::fadeFunction::cubique)
        MonFade.setFunction(Fade::fadeFunction::cubique);
    else if (string == Fade::fadeFunction::constant)
        MonFade.setFunction(Fade::fadeFunction::constant);

}
void Playlist::loadFile(const std::string &file)
{
    rapidxml::xml_document<>* doc = XmlDocumentManager::get()->getDocument(file);
    rapidxml::xml_node<>* root = doc->first_node("playlists");
    rapidxml::xml_node<>* current;
    Playlist *playlist = Playlist::get();
    for(current=root->first_node("playlist");current;current=current->next_sibling("playlist"))
    {
        rapidxml::xml_attribute<>* att = current->first_attribute("rep");
        if(att)
        {
            std::string repertoire(att->value());
            std::string groupe(current->first_attribute("nom")->value());
            std::list<std::string> liste = FileUtils::getRecurse(repertoire, std::list<std::string>({"ogg", "wav"}));
            for(std::string &s : liste)
            {
                playlist->addMusic(s, groupe);
                std::cout << s << std::endl;
            }
        }
    }
}

