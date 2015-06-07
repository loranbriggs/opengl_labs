#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>

// Vector3 
class Vector3{ 
public: 
    GLdouble x,y,z;

    //default constructor
    Vector3()
    {
        x = y = z = 0;
    }

    Vector3(float xx, float yy, float zz)
    {
        x = xx; y = yy; z = zz;
    }

    Vector3(const Vector3& v)
    {
        x = v.x; y = v.y; z = v.z;
    }

    void set(float dx, float dy, float dz)
    {
        x = dx; y = dy; z = dz;
    }

    void set(Vector3 v)
    {
        x = v.x; y = v.y; z = v.z;
    }

    // reverse this vector
    void flip()
    {
        x = -x; y = -y; z = -z;
    }

    //set to this + b
    void add(Vector3 b)
    {
        x += b.x; y += b.y; z += b.z;
    }

    //set to difference a - b
    void setDiff(Point3& a, Point3& b)
    {
        x = a.x - b.x; y = a.y - b.y; z = a.z - b.z;
    }

    //adjust this vector to unit length
    void normalize()
    {
        double sizeSq = x * x + y * y + z * z;
        if(sizeSq < 0.0000001)
        {
            return; // does nothing to zero vectors;
        }
        float scaleFactor = 1.0/(float)sqrt(sizeSq);
        x *= scaleFactor; y *= scaleFactor; z *= scaleFactor;
    }

    void scale(float s)
    {
        x *= s; y *= s; z *= s;
    }

    //return this cross b
    Vector3 cross(Vector3 b)
    {
        Vector3 c(y*b.z - z*b.y, z*b.x - x*b.z, x*b.y - y*b.x);
        return c;
    }

    // return this dotted with b
    float dot(Vector3 b) 
    {
        return x * b.x + y * b.y + z * b.z;
    }

    // returns new vecotr a - b
    static Vector3 diffPoints(Point3& a, Point3& b)
    {
        Vector3 diff(a.x - b.x, a.y - b.y, a.z - b.z);
        return diff;
    }
};

#endif
