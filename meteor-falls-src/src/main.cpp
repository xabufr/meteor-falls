
#include <iostream>
#ifdef UNIT_TEST
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include "UnitTest/UnitTest.h"

#else
#include <iostream>
#include "Application/application.h"
#include "Application/parameterparserexception.h"
<<<<<<< HEAD
#include "Engine/GameEngine/Map.h"

    #include "UnitTest/Tests/SoundEngineTest.cpp"
=======
#include "UnitTest/Tests/SoundEngineTest.cpp"
>>>>>>> ab3b80dacc94d37bbb464cbf8554e5c64cb94b8f

int main(int argc, char **argv)
{

    //launchUnitTestForSound();
<<<<<<< HEAD
    Map *map = new Map();
    map->load("test");
=======
>>>>>>> ab3b80dacc94d37bbb464cbf8554e5c64cb94b8f

    try
    {
        Application app(argc, argv);
    }
    catch(ParameterParserException &e){
        std::cout << "L'argument " << e.getArgument() << " n'existe pas"<<std::endl;
    }
    catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }

    return 0;
}
#endif
