#include "Vector3D.h"

Vector3D Vector3D::operator+(const Vector3D& vec2) const
{
    Vector3D vec(*this);
    vec += vec2;
    return vec;
}
Vector3D Vector3D::operator-(const Vector3D& vec2) const
{
    Vector3D vec(*this);
    vec -= vec2;
    return vec;
}
Vector3D Vector3D::operator/(double val) const
{
    Vector3D vec(*this);
    vec /= val;
    return vec;
}
Vector3D Vector3D::operator*(double val) const
{
    Vector3D vec(*this);
    vec *= val;
    return vec;
}
bool Vector3D::operator==(const Vector3D& vec) const
{
	return x==vec.x&&y==vec.y&&z==vec.z;
}
Vector3D& Vector3D::operator+=(const Vector3D& vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;
	return *this;
}
Vector3D& Vector3D::operator-=(const Vector3D& vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
	return *this;
}
Vector3D& Vector3D::operator-=(const int val)
{
	x -= val;
	y -= val;
	z -= val;
	return *this;
}
Vector3D& Vector3D::operator*=(double val)
{
	x*=val;
	y*=val;
	z*=val;
	return *this;
}
Vector3D& Vector3D::operator/=(double val)
{
	if(val==0)
		return *this;
	return operator*=(1.f/val);
}
double Vector3D::produitScalaire(const Vector3D& vec) const
{
	return x*vec.x + y*vec.y + z*vec.z;
}
double Vector3D::normeCarre() const
{
	return x*x + y*y + z*z;
}
double Vector3D::norme() const
{
	return sqrt(normeCarre());
}
bool Vector3D::estNul() const
{
	return x==0.f&&y==0.f&&z==0.f;
}
double Vector3D::angle(const Vector3D& vec) const
{
	if(vec.estNul())
		return 0;
	return acos(produitScalaire(vec)/(norme()*vec.norme()));
}
double Vector3D::distanceCarre(const Vector3D& vec) const
{
	float a,b,c;
	a=x-vec.x;
	b=y-vec.y;
	c=z-vec.z;
	return a*a+b*b+c*c;
}
Vector3D Vector3D::produit_vectoriel(const Vector3D& v1, const Vector3D& v2)
{
	Vector3D ret;
	ret.x= v1.y*v2.z - v1.z*v2.y;
	ret.y= v1.z*v2.x - v1.x*v2.z;
	ret.z= v1.x*v2.y - v1.y*v2.x;
	return ret;
}
