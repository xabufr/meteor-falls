#include "UnitTest.h"
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <map>
#include <SFML/Audio.hpp>

void launchUnitTestForSound()
{

    SoundEngine MyAudio;

    MyAudio.readAudio("../sound/music/test/01.ogg");
    std::cout << "Sound ok" << std::endl;

}
