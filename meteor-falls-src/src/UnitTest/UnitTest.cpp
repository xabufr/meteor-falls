#include "UnitTest.h"
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <map>
#include <assert.h>
#include <SFML/Audio.hpp>
void launchUnitTests()
{
    launchUnitTestForSound();
}

void launchUnitTestForSound()
{

    SoundEngine MyAudio;

    MyAudio.addMusic("../sound/music/test/02.ogg");
    MyAudio.addMusic("../sound/music/test/y.ogg");

    MyAudio.readAudio();
    assert(MyAudio.get_HowManyMusic() == 2);
    assert(MyAudio.get_MusicPlayed() == 1);

    MyAudio.set_Volume(1,0);
    MyAudio.down_Volume(1);
    assert(MyAudio.get_Volume() == 0);

    MyAudio.set_Volume(1,100);
    MyAudio.up_Volume(1);
    assert(MyAudio.get_Volume() == 100);

    MyAudio.set_Volume(1,100);

    for (;;)
    {
        int sec_restantes =  MyAudio.get_Temps_Chanson() - MyAudio.get_Time_Elapsed();
       // std::cout << sec_restantes << std::endl;
      //  MyAudio.make_Fadeout(sec_restantes);

      if (sec_restantes == 0)
      {
          if ((MyAudio.get_MusicPlayed() == MyAudio.get_HowManyMusic()) and (MyAudio.get_Loop() == false))
            break;

          else
            MyAudio.readAudio();
      }

    }
    std::cout << "Sound ok" << std::endl;
    while(1);

}
