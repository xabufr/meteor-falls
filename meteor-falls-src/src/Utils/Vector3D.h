#ifndef VECTOR3D_H
#define VECTOR3D_H
#include "../precompiled/serialization.h"
#include <SFML/System/Vector3.hpp>
#include <OgreVector3.h>
#include <cmath>

class Vector3D
{
public:
    double x,y,z;
    Vector3D()
    {
        x=y=z=0.f;
    }
    Vector3D(float _x, float _y, float _z):
        x(_x),
        y(_y),
        z(_z)
    {
    }
    template<class T>
    Vector3D(const T &vec)
    {
        x = vec.x;
        y = vec.y;
        z = vec.z;
    }
    template<class T>
    Vector3D& operator=(const T &vec)
    {
        x = vec.x;
        y = vec.y;
        z = vec.z;
        return *this;
    }
    template<class T>
    bool operator==(const T& vec) const
    {
        return x==vec.x&&y==vec.y&&z==vec.z;
    }
    template<class T>
    T convert() const
    {
        T vec;
        vec.x=x;
        vec.y=y;
        vec.z=z;
        return vec;
    }
    template<class T>
    Vector3D& operator+=(const T& vec)
    {
        x += vec.x;
        y += vec.y;
        z += vec.z;
        return *this;
    }
    template<class T>
    Vector3D& operator-=(const T& vec)
    {
        x -= vec.x;
        y -= vec.y;
        z -= vec.z;
        return *this;
    }
    Vector3D& operator-=(const int val)
    {
        x -= val;
        y -= val;
        z -= val;
        return *this;
    }
    template<class T>
    Vector3D& operator*=(const T& val)
    {
        x*=val;
        y*=val;
        z*=val;
        return *this;
    }
    template<class T>
    Vector3D& operator/=(const T& val)
    {
        if(val==0)
            return *this;
        return operator*=(1.f/double(val));
    }
    template<class T>
    double produitScalaire(const T& vec) const
    {
        return x*vec.x + y*vec.y + z*vec.z;
    }
    double normeCarre() const
    {
        return x*x + y*y + z*z;
    }
    double norme() const
    {
        return sqrt(normeCarre());
    }
    bool estNul() const
    {
        return x==0.f&&y==0.f&&z==0.f;
    }
    template<class T>
    double angle(const T& vec) const
    {
        return angle(Vector3D(vec));
    }
    double angle(const Vector3D& vec) const
    {
        if(vec.estNul())
            return 0;
        return acos(produitScalaire(vec)/(norme()*vec.norme()));
    }
    template<class T>
    double distanceCarre(const T& vec) const
    {
        float a,b,c;
        a=x-vec.x;
        b=y-vec.y;
        c=z-vec.z;
        return a*a+b*b+c*c;
    }
    static Vector3D produit_vectoriel(const Vector3D& v1, const Vector3D& v2)
    {
        Vector3D ret;
        ret.x= v1.y*v2.z - v1.z*v2.y;
        ret.y= v1.z*v2.x - v1.x*v2.z;
        ret.z= v1.x*v2.y - v1.y*v2.x;
        return ret;
    }

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar & x & y & z;
    }
};
template<class T>
Vector3D operator+(const Vector3D& vec1, const T& vec2)
{
    Vector3D vec(vec1);
    vec += vec2;
    return vec;
}
template<class T>
Vector3D operator-(const Vector3D& vec1, const T& vec2)
{
    Vector3D vec(vec1);
    vec -= vec2;
    return vec;
}
template<class T>
Vector3D operator/(const Vector3D& vec1, const T& val)
{
    Vector3D vec(vec1);
    vec /= val;
    return vec;
}
template<class T>
Vector3D operator*(const Vector3D& vec1, const T& val)
{
    Vector3D vec(vec1);
    vec *= val;
    return vec;
}

#endif // VECTOR3D_H
