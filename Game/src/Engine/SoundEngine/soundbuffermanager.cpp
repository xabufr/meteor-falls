#include "soundbuffermanager.h"
#include "Utils/Exception/BasicException.h"

SoundBufferManager::SoundBufferManager()
{
   // Logger::Log()<<"Création du SoundBufferManager" << Logger::endl;
}

SoundBufferManager::~SoundBufferManager()
{

    for(auto &it : m_buffers)
    {
        delete it.second;
    }

}

sf::SoundBuffer* SoundBufferManager::Get(const std::string& chemin)
{

    auto it = m_buffers.find(chemin);
    if(it!=m_buffers.end())
        return it->second;

    sf::SoundBuffer *buffer = new sf::SoundBuffer;

    if(!buffer->loadFromFile(chemin))
        THROW_BASIC_EXCEPTION("fichier Son non trouvé :" + chemin);

    m_buffers[chemin] = buffer;
    return buffer;

}
