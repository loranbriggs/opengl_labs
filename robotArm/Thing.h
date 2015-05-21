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

class Thing
{
    public:
        Thing();

        // dimensions
        GLdouble size;
        GLdouble x;
        GLdouble y;
        GLdouble z;

        // rotation
        GLdouble rx;
        GLdouble ry;
        GLdouble rz;

        void Reset();
};

#endif
