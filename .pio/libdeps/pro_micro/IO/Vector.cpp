#include "Vector.h"

#include <float.h>

Vector::Vector(void) : x(0), y(0), z(0) {}
Vector::Vector(float X, float Y, float Z) : x(X), y(Y), z(Z) {}
Vector::Vector(const Vector &copy) { *this = copy; }
    
Vector    &Vector::operator=(const Vector &copy)
{
    x = copy.x;
    y = copy.y;
    z = copy.z;
    return (*this);
}
    
bool    Vector::operator!=(const Vector &other) const { return (!(*this == other)); }
bool    Vector::operator==(const Vector &other) const { return (other.x - x < FLT_MIN && other.y - y < FLT_MIN && other.z - z < FLT_MIN); }
bool    Vector::eq(const Vector &other, float prec) const { return (other.x - x < prec && other.y - y < prec && other.z - z < prec); }