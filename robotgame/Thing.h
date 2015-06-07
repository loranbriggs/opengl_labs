#ifndef THING
#define THING

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>  //suitable when using Windows 95/98/NT
#include <gl/Gl.h>
#include <gl/Glu.h>
#include <gl/glut.h>
#endif

// linux headers
#ifdef __linux__
#include <unistd.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#endif

#include <math.h>
#include "Point3.h"
#include <string>

class Thing
{
    public:
        Thing();
        Thing(std::string type, GLdouble size,
                GLdouble x, GLdouble y, GLdouble z);

        std::string type;

        // dimensions
        GLdouble size;
        Point3   pos;

        // rotation
        GLdouble rx;
        GLdouble ry;
        GLdouble rz;

        GLUquadric* quadric;

        // gravity on if not held by claw
        bool gravity;

        void draw();
        bool aboveTable(Point3 center);
};

#endif
