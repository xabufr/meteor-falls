#define MF_UNITTEST_ENABLED
#include <iostream>
#include "UnitTest/UnitTest.h"


int main(){

    #ifdef MF_UNITTEST_ENABLED

        launchUnitTests();

    #endif

    return 0;
}

