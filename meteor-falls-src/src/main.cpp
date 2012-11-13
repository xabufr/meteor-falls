//#define MF_UNITTEST_ENABLED
#include <iostream>
#include "Application/application.h"
#include "Application/parameterparserexception.h"
#include "UnitTest/UnitTest.h"

int main(int argc, char **argv)
#ifdef MF_UNITTEST_ENABLED

        launchUnitTestForSound();

#else
    try{
        Application app(argc, argv);
    }
    catch(ParameterParserException &e){
        std::cout << "L'argument " << e.getArgument() << " n'existe pas"<<std::endl;
    }
#endif
    return 0;
}
