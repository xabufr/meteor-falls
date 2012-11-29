#ifndef SOUNDENGINE_H
#define SOUNDENGINE_H
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include "precompiled/sfml_audio.h"
#include "../Engine.h"
#include "soundbuffermanager.h"
#include "../../Engine/SoundEngine/Fade.h"
#include "../../Engine/EngineType.h"

class EngineMessage;
struct SoundParams
{
    sf::Sound *sound;
    bool removeWhenFinished;
    Fade fade_in, fade_out;
    int dureeFadeIn, dureeFadeOut;
    bool spacialized, isFadeIn, isFadeOut;
    sf::Clock timerIn, timerOut;
    float timeIn, timeOut, attenuation;
    SoundParams()
    {
        removeWhenFinished=true;
        spacialized=false;
    }
};

typedef unsigned int SoundId;
class SoundEngine : public Engine
{
    public:
        SoundEngine(EngineManager * manager);
            virtual ~SoundEngine();

        SoundId playSound(const std::string&);
        SoundId playLocalizedSound(const std::string&);

        void setListenerPosition(SoundId,sf::Vector3f position);
        void setListenerDirection(SoundId,sf::Vector3f direction);
        void setListenerAttenuation(SoundId id, float attenuation);
        void setGlobalVolume(float);

        void stop(SoundId);
        void play(SoundId);

        void set_loop(SoundId){ m_loop = true;};
        void unset_loop(SoundId){ m_loop = false;};
        bool get_loop(SoundId) { return m_loop;};

        sf::Sound* getSound(SoundId);

        void removeWhenFinished(SoundId id, bool=true);

        virtual void work();


        // parametres
        void set_fadeIn_time(int time);
        void set_fadeOut_time(int time);
        void set_type_transition(Fade::fadeFunction string);

        // rajouter le stop / loop pour le son

        virtual void handleEngineEvent(EngineMessage*);// Type engineEvent ??
        virtual EngineType getType() const;

    protected:
    private:
        std::unordered_map<unsigned int, SoundParams*> m_sounds;
        unsigned int m_last;
        bool m_loop;
        int m_fadeIn_time;
        int m_volume;
        int m_fadeOut_time;
        sf::Clock m_temps_ecoule;
        Fade MonFade;
};

#endif
