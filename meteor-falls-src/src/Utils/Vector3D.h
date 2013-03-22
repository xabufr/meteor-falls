#ifndef VECTOR3D_H
#define VECTOR3D_H
#include "../precompiled/serialization.h"
#include <SFML/System/Vector3.hpp>
#include <OgreVector3.h>
#include <cmath>
#include <bullet/LinearMath/btVector3.h>

class Vector3D
{
public:
    double x,y,z;
    Vector3D(): x(0), y(0), z(0) { }
    Vector3D(float _x, float _y, float _z):
        x(_x),
        y(_y),
        z(_z)
    {}
    template<class T>
    Vector3D(const T &vec): x(vec.x), y(vec.y), z(vec.z) {}
	operator sf::Vector3f() const
	{
		return convert<sf::Vector3f>();
	}
	operator Ogre::Vector3() const
	{
		return convert<Ogre::Vector3>();
	}
	operator btVector3() const
	{
		return convert<btVector3>();
	}

    bool operator==(const Vector3D& vec) const;
    template<class T>
    T convert() const
    {
        return T(x,y,z);
    }
    Vector3D& operator+=(const Vector3D& vec);
    Vector3D& operator-=(const Vector3D& vec);
    Vector3D& operator-=(const int val);
    Vector3D& operator*=(double);
    Vector3D& operator/=(double);
    double produitScalaire(const Vector3D& vec) const;
    double normeCarre() const;
    double norme() const;
    bool estNul() const;
    double angle(const Vector3D& vec) const;
    double distanceCarre(const Vector3D& vec) const;
    static Vector3D produit_vectoriel(const Vector3D& v1, const Vector3D& v2);
	Vector3D operator+(const Vector3D&) const;
	Vector3D operator-(const Vector3D&) const;
	Vector3D operator/(double) const;
	Vector3D operator*(double) const;
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar & x & y & z;
    }
};

#endif // VECTOR3D_H
