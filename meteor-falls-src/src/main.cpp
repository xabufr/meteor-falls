#include <iostream>
#include "Application/application.h"
#include "Application/parameterparserexception.h"

int main(int argc, char **argv){
    try{
        Application app(argc, argv);
    }
    catch(ParameterParserException &e){
        std::cout << "L'argument " << e.getArgument() << " n'existe pas"<<std::endl;
    }

    return 0;
}
