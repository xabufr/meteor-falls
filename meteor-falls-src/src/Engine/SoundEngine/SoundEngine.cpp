#include "SoundEngine.h"

SoundEngine::SoundEngine()
{
        m_stop = true;
        m_pause = false;
        m_volume = 100;
}

void SoundEngine::readAudio(std::string path)
{

    sf::Music Music1;
    if (!Music1.openFromFile(path))
    {

    }

    Music1.play();

}


