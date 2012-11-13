#include "../UnitTest.h"
#include <string>
#include <iostream>
#include <SFML/Audio.hpp>
#include "Engine/SoundEngine/SoundEngine.h"

BOOST_AUTO_TEST_CASE(SoundEngineTest)
{
    SoundEngine MyAudio;

    MyAudio.readAudio("../sound/music/test/01.ogg");
    std::cout << "Sound ok" << std::endl;
}



