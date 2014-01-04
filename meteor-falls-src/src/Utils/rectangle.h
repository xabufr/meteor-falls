#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "vector2d.h"

template<typename T> class Rectangle
{
public:
    T width, height, left, top;
    Rectangle(){}
    Rectangle(T w, T h, T _left, T _top): width(w), height(h), left(_left), top(_top) {}
    void setCenter(const Vector2D<T> &center)
    {
        left = center.x - width * 0.5;
        top = center.y - height * 0.5;
    }
};

#endif // RECTANGLE_H
