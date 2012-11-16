#include "../UnitTest.h"
#include "Engine/SoundEngine/SoundEngine.h"
#include <string>
#include <iostream>
#include <stdio.h>
#include <map>
#include <assert.h>
#include <SFML/Audio.hpp>

void launchUnitTestForSound();
void launchUnitTests()
{
    launchUnitTestForSound();
}

//BOOST_AUTO_TEST_CASE(SoundEngineTest)
void launchUnitTestForSound()
{
    SoundEngine MyAudio;

    MyAudio.addMusic("../sound/music/test/k.ogg");
    MyAudio.addMusic("../sound/music/test/02.ogg");
    MyAudio.addMusic("../sound/music/test/01.ogg");

    MyAudio.readAudio();

    assert(MyAudio.get_HowManyMusic() == 3);
    assert(MyAudio.get_MusicPlayed() == 1);

    MyAudio.setPos_Depth(1,100);
    assert(MyAudio.get_attenuation() == 100);

    MyAudio.setPos_Depth(1,12);
    assert(MyAudio.get_attenuation() == 12);


    sf::Vector3f MyVector3F;
    MyVector3F.x = 10;
    MyVector3F.y = 10;
    MyVector3F.z = 10;

    MyAudio.setPos_3D(1,MyVector3F);
    assert(MyAudio.getPos_3D() == MyVector3F);


    for (;;)
    {
        int sec_restantes =  MyAudio.get_Temps_Chanson() - MyAudio.get_Time_Elapsed();

        if (MyAudio.isFading_Out(sec_restantes) == true)
            MyAudio.make_Fadeout(sec_restantes);

        if (MyAudio.isFading_In() == true) // 20 sec du début
            MyAudio.make_Fadein();

      if (sec_restantes == 1)
      {

          if ((MyAudio.get_MusicPlayed() == MyAudio.get_HowManyMusic()) and (MyAudio.get_Loop() == false))
            break;

          else
            MyAudio.readAudio();
            std::cout << "lis chanson suivante" << std::endl;
      }

    }
    std::cout << "Sound ok" << std::endl;

}



