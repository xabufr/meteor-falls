#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <CEGUI/Vector.h>

template<typename T> class Vector2D
{
public:
    T x, y;
    Vector2D() {}
    Vector2D(T _x, T _y): x(_x), y(_y) {}
    Vector2D(const CEGUI::Vector2f &o): x(o.d_x), y(o.d_y) {}

    template<typename OtherType>
    Vector2D(const OtherType &o): x(o.x), y(o.y) {
    }

    Vector2D & operator=(const Vector2D<T> & o) {
        this->x = o.x;
        this->y = o.y;
        return *this;
    }

    template<typename OtherType>
    Vector2D& operator=(const OtherType &o) {
        Vector2D tmp(o);
        *this = tmp;
        return *this;
    }

    template <typename VectorType>
    Vector2D operator-(const VectorType& other) const {
        Vector2D<T> tmp(*this);
        tmp -= other;
        return tmp;
    }

    template <typename VectorType>
    Vector2D<T> &operator-=(const VectorType& other) {
        this->x -= other.x;
        this->y -= other.y;
        return *this;
    }

    template <typename VectorType>
    Vector2D operator+(const VectorType& other) const {
        Vector2D<T> tmp(*this);
        tmp += other;
        return tmp;
    }

    template <typename VectorType>
    Vector2D<T> &operator+=(const VectorType& other) {
        this->x += other.x;
        this->y += other.y;
        return *this;
    }

    Vector2D<T> operator/(const T& value) const {
        Vector2D<T> tmp(*this);
        tmp.x /= value;
        tmp.y /= value;
        return tmp;
    }
};

#endif // VECTOR2D_H
