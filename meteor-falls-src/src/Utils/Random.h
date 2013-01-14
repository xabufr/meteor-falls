#ifndef RANDOM_H
#define RANDOM_H


class Random
{
public:
    static int Rand(int min, int max);
    static float Rand(float min, float max);
private:
    static bool m_initialized;
};

#endif // RANDOM_H
