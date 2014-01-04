#ifndef VECTOR2D_H
#define VECTOR2D_H

template<typename T> class Vector2D
{
public:
    T x, y;
    Vector2D() {}
    Vector2D(T _x, T _y): x(_x), y(_y) {}
};

#endif // VECTOR2D_H
