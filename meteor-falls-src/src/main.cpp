#ifdef UNIT_TEST
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include "UnitTest/UnitTest.h"

#else
#include <iostream>
#include "Application/application.h"
#include "Application/parameterparserexception.h"

int main(int argc, char **argv)
{
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
