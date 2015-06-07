#ifndef VECTOR_POINT3_H
#define VECTOR_POINT3_H
#include <iostream>
#include <math.h>
#include "Vector3.h"
#include "Point3.h"

// Point3 class 
class VectorPoint3{ 
public: 
    static Point3 pointPlusVector(Point3 p, Vector3 v)
    { return Point3(p.x + v.x, p.y + v.y, p.z + v.z);}

};

#endif
