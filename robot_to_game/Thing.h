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
#include "Color.h"
#include <string>

class Thing
{
    public:
        Thing(std::string type, GLdouble size,
                GLdouble x, GLdouble y, GLdouble z,
                GLdouble rx, GLdouble ry, GLdouble rz);
        Thing(std::string type, GLdouble size, GLdouble x, GLdouble y, GLdouble z): Thing(type, size, x, y, z, 0, 0, 0) {}
        Thing(std::string type, GLdouble size) : Thing(type, size, 0, 0, 0, 0, 0, 0){}
        Thing(std::string type): Thing(type, 1, 0, 0, 0, 0, 0, 0){}
        Thing(): Thing("sphere", 1, 0, 0, 0, 0, 0, 0){}

        std::string type;

        // dimensions
        GLdouble size;
        GLdouble x;
        GLdouble y;
        GLdouble z;

        // rotation
        GLdouble rx;
        GLdouble ry;
        GLdouble rz;

        GLUquadric* quadric;

        void draw();
};

#endif
