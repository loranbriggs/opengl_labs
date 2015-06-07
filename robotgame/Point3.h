#ifndef POINT3_H
#define POINT3_H
#include <iostream>
#include <math.h>

// Point3 class 
class Point3{ 
public: 
    GLdouble x,y,z;
    void set(float dx, float dy, float dz){x = dx; y = dy; z = dz;}
    //void set(Point3& p){x = p.x; y = p.y; z = p.z;} 	
    void set(Point3 p){x = p.x; y = p.y; z = p.z;} 

    Point3(float xx,     float yy, float zz){x = xx; y = yy; z = zz;}
    Point3(){x = y = z = 0;}
    
    void build4tuple(float v[])
    {// load 4-tuple with this color: v[3] = 1 for homogeneous
        v[0] = x; v[1] = y; v[2] = z; v[3] = 1.0f;
    }	

    float dist(Point3 other)
    {
        return sqrt( pow(other.x - x, 2) + pow(other.y - y, 2) + pow(other.z - z, 2) );
    }

    float distInXzPlane(Point3 other)
    {
        return sqrt( pow(other.x - x, 2) + pow(other.z - z, 2) );
    }

    void dx(float dx)
    {
        y += dx;
    }

    void dy(float dy)
    {
        y += dy;
    }

    void dz(float dz)
    {
        y += dz;
    }

};

#endif
