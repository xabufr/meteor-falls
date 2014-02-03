#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "vector2d.h"
#include <algorithm>

template<typename T> class Rectangle
{
public:
    T width, height, left, top;
    Rectangle(){}
    Rectangle(T w, T h, T _left, T _top): width(w), height(h), left(_left), top(_top) {}
    Rectangle(const Vector2D<T> &pointA, const Vector2D<T> &pointB);
    void setCenter(const Vector2D<T> &center)
    {
        left = center.x - width * 0.5;
        top = center.y - height * 0.5;
    }
    template<typename VectorType>
    bool contains(const Vector2D<VectorType> point) const {
        return left <= point.x && left + width >= point.x &&
                top <= point.y && top + height >= point.y;
    }
};

template<typename T>
Rectangle<T>::Rectangle(const Vector2D<T> &pointA, const Vector2D<T> &pointB)
{
    this->left = std::min(pointA.x, pointB.x);
    this->top = std::min(pointA.y, pointB.y);
    this->width = std::abs(pointA.x - pointB.x);
    this->height = std::abs(pointA.y - pointB.y);
}

#endif // RECTANGLE_H
