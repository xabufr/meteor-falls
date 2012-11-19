#include "../UnitTest.h"
#include "Engine/SoundEngine/SoundEngine.h"
#include "Engine/SoundEngine/Playlist.h"
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

    Playlist MyPlaylist;

    MyPlaylist.addMusic("../sound/music/test/01.ogg", "MaPlaylist");
    MyPlaylist.addMusic("../sound/music/test/02.ogg", "MaPlaylist");
    MyPlaylist.addMusic("../sound/music/test/k.ogg", "MaPlaylist");

    MyPlaylist.select_group("MaPlaylist");

    assert(MyPlaylist.get_HowManyMusic() == 3);
    //assert(MyPlaylist.get_MusicPlayed() == 1);

    for(;;)
    {
        MyPlaylist.work();
    }


}



