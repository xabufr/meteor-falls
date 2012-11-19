#include "SoundEngine.h"

SoundEngine::SoundEngine(EngineManager * manager)
    : Engine(manager)
{
    m_last = 0;
}

SoundEngine::~SoundEngine()
{
    //dtor
}


unsigned int SoundEngine::playSound(const std::string& chemin)
{
    m_sounds[m_last] = new SoundParams;
    sf::Sound *s = new sf::Sound;
    m_sounds[m_last]->sound = s;
    s->setRelativeToListener(true);
    s->setPosition(0,0,0);
    s->setBuffer(*SoundBufferManager::get()->Get(chemin));// get instance inconnu
    s->play();

    return m_last++;
}


unsigned int SoundEngine::playLocalizedSound(const std::string& chemin)
{
    m_sounds[m_last] = new SoundParams;
    m_sounds[m_last]->spacialized=true;
    m_sounds[m_last]->sound = new sf::Sound;
    m_sounds[m_last]->sound->setRelativeToListener(false);
    m_sounds[m_last]->sound->setPosition(0,0,0);
    m_sounds[m_last]->sound->setBuffer(*SoundBufferManager::get()->Get(chemin));// encore getinstance
    m_sounds[m_last]->sound->play();
    return m_last++;
}


void SoundEngine::removeWhenFinished(unsigned int id, bool rem)
{
    auto it = m_sounds.find(id);
    if(it==m_sounds.end())
        return;
    it->second->removeWhenFinished=rem;
}


void SoundEngine::work()// appeller la classe Fade
{
    for (auto it: m_sounds)
    {
         int new_volume;

        //SoundBufferManager *MonBuffer = new SoundBufferManager();

          //sf::Sound *sound_to_get_duration = new sf::Sound;
         //sound_to_get_duration = m_sounds[m_last]->sound;
        // sound_to_get_duration->setBuffer(*SoundBufferManager::get()->Get(m_sounds[m_last]->sound));



        int sec_restantes = it.second->sound->getBuffer()->getDuration().asSeconds(); - m_temps_ecoule.getElapsedTime().asSeconds();


        if (sec_restantes <= m_fadeOut_time)
        {
            MonFade.setType(Fade::fadeType::out);
            new_volume = MonFade.work(m_temps_ecoule.getElapsedTime().asMilliseconds(), it.second->sound->getBuffer()->getDuration().asMilliseconds(), 20000, m_volume);
            it.second->sound->setVolume(new_volume);

      //  std::cout << "fadeout" << std::endl;
        }
        else if (m_temps_ecoule.getElapsedTime().asSeconds() <= m_fadeIn_time)
        {
            MonFade.setType(Fade::fadeType::in);
            new_volume = MonFade.work(m_temps_ecoule.getElapsedTime().asMilliseconds(), it.second->sound->getBuffer()->getDuration().asMilliseconds(), 20000, m_volume);
            it.second->sound->setVolume(new_volume);
              //      std::cout << "fadein" << std::endl;
        }
        else
        {
            it.second->sound->setVolume(m_volume);
        }
    }


      //  std::cout << "new voilume : "<<new_volume << std::endl;
}

/*
void SoundEngine::handleEngineEvent(EngineEvent* event)
{
    switch(event->GetMessage())
    {
    case TypeMessage::JouerSon:
        this->PlaySound(event->GetStrings().find(IndexMessages::Chemin)->second);
        break;
    }
}
*/

EngineType SoundEngine::getType() const
{
   // return EngineType::SoundEngine;// enginetype
}


sf::Sound* SoundEngine::getSound(SoundId id)
{
    auto it = m_sounds.find(id);
    if(it==m_sounds.end())
        return 0;
    return it->second->sound;
}


void SoundEngine::stop(SoundId id)
{
    m_sounds[id]->sound->stop();
}

void SoundEngine::setListenerAttenuation(SoundId id, float attenuation)
{
      m_sounds[id]->sound->setAttenuation(attenuation);
      //void sf::SoundSource::setAttenuation ( float  attenuation).
}

void SoundEngine::play(SoundId id)
{
    m_sounds[id]->sound->play();
    m_sounds[id]->isFadeIn=false;
    m_sounds[id]->isFadeOut=false;
}

void SoundEngine::set_fadeIn_time(int time)
{

    m_sounds[m_last]->dureeFadeIn = time;
    m_fadeIn_time = time;

}

void SoundEngine::set_fadeOut_time(int time)
{

    m_sounds[m_last]->dureeFadeOut = time;
    m_fadeOut_time = time;

}

void SoundEngine::set_type_transition(Fade::fadeFunction string)
{

    if (string == Fade::fadeFunction::carre)
        MonFade.setFunction(Fade::fadeFunction::carre);
    else if (string == Fade::fadeFunction::cubique)
        MonFade.setFunction(Fade::fadeFunction::cubique);
    else if (string == Fade::fadeFunction::constant)
        MonFade.setFunction(Fade::fadeFunction::constant);

}





