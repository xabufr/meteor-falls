#include "Playlist.h"
#include "../ScriptEngine/XmlDocumentManager.h"
#include "../../precompiled/lexical_cast.h"
#include "Utils/File.h"
#include "Utils/Configuration/Config.h"
#include "Utils/Exception/FileNotFound.h"
#include <iostream>

Playlist::Playlist()
{
    m_stop = false;
    m_music = new sf::Music;
    first_song = m_loop = true;
    m_temps_ecoule.restart();

    m_pause = Config::get()->getSoundConfig()->getActivate();
    m_volume = Config::get()->getSoundConfig()->getMusicVolume();
}

void Playlist::select_group(std::string group)
{
    m_groupe_courant = group;
}

void Playlist::set_Stop(bool stop)
{
    m_stop = stop;
    if (m_stop)
        m_music->stop();
    else
        m_music->play();
}

void Playlist::set_Pause(bool pause)
{
    m_pause = pause;
    if (m_pause)
        m_music->pause();
    else
        m_music->play();
}

void Playlist::addMusic(std::string path, std::string group) // ajouter une musique au vector
{
    m_vector_paths_group_musiques[group].push_back(path);
    m_music_playing[group] = 0;
    // ecrire sur un doc xmlreadPlaylist
}


void Playlist::readPlaylist()
{
    if (m_loop)
    {
        if (m_music_playing[m_groupe_courant] > m_vector_paths_group_musiques[m_groupe_courant].size())
            m_music_playing[m_groupe_courant] = 0;
    }

    if (first_song)
    {
        m_music->openFromFile(m_vector_paths_group_musiques[m_groupe_courant][m_music_playing[m_groupe_courant]]);
        m_music->play();
    }

    if (m_stop || m_pause)
    {
        m_music_playing[m_groupe_courant] = (m_stop)?0:++m_music_playing[m_groupe_courant];
        m_music->play();
        m_temps_ecoule.restart();
        m_pause = m_stop = false;
    }
}


void Playlist::set_Volume(int new_volume)
{
    m_volume = new_volume;

    if (m_volume > 100)
        m_volume = 100;


    if (m_volume < 0)
        m_volume = 0;

    m_music->setVolume(m_volume);
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

    if (first_song && !m_pause)
    {
        readPlaylist();
        first_song = false;
    }

    int sec_restantes =  get_Temps_Chanson() - m_temps_ecoule.getElapsedTime().asSeconds();

    if (sec_restantes <= m_fade_time)
    {
        MonFade.setType(Fade::fadeType::out);
        new_volume = MonFade.work(m_temps_ecoule.getElapsedTime().asMilliseconds(), m_music->getDuration().asMilliseconds(), 20000, m_volume);
        m_music->setVolume(new_volume);
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

    if (m_music->getStatus() == sf::SoundSource::Status::Stopped && !m_pause)
    {
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
	XmlDocumentManager::Document &doc = XmlDocumentManager::get()->getDocument(file);

	auto bounds = doc.get_child("playlists").equal_range("playlist");
	for(auto it=bounds.first;it!=bounds.second;++it)
    {
		std::string repertoire = it->second.get("xmlattr.rep", "");
		if(!repertoire.empty()) 
        {
            std::string groupe = it->second.get<std::string>("xmlattr.nom");
            std::list<std::string> liste = FileUtils::getRecurse(repertoire, std::list<std::string>({"ogg", "wav"}));
            for(std::string &s : liste)
            {
                Playlist::get()->addMusic(s, groupe);
                std::cout << s << std::endl;
            }
        }
    }
}
