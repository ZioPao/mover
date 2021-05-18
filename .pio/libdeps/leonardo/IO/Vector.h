#pragma once

struct Vector
{
    float    x;
    float    y;
    float    z;
    
    Vector(void);
    Vector(float X, float Y, float Z);
    Vector(const Vector &copy);
    
    Vector    &operator=(const Vector &copy);
    
    bool            operator==(const Vector &other) const;
    bool            operator!=(const Vector &other) const;
    bool            eq(const Vector &other, float prec) const;
};
