#include "Random.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

bool Random::m_initialized = false;

int Random::Rand(int min, int max)
{
    if(!m_initialized){
        m_initialized=true;
        srand(time(0));
    }
    return rand()%(max - min) + min;
}
float Random::Rand(float min, float max)
{
    if(!m_initialized){
        m_initialized=true;
        srand(time(0));
    }
    return Rand(int(min),int(max));
    int precision = 10000;
    float r = rand()%(int(max-min)*precision);
    r/=float(precision);
    return r+min;
}
