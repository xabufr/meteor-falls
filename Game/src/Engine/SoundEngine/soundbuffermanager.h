#ifndef SOUNDBUFFERMANAGER_H
#define SOUNDBUFFERMANAGER_H
#include "../../precompiled/sfml_audio.h"
#include <unordered_map>
#include "../../Utils/singleton.h"

class SoundBufferManager: public Singleton<SoundBufferManager>
{
    friend class Singleton<SoundBufferManager>;
    public:
        sf::SoundBuffer* Get(const std::string&);
    protected:
        SoundBufferManager();
        virtual ~SoundBufferManager();
    private:
        std::unordered_map<std::string, sf::SoundBuffer*> m_buffers;
};

#endif // SOUNDBUFFERMANAGER_H
