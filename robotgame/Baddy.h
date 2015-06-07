#ifndef BADDY
#define BADDY

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

#ifndef PI
#define PI 3.14159265359
#define RADS (PI/180)
#define DEGS (180/PI)
#endif

#include <math.h>
#include "Material.h"
#include "Point3.h"
#include "Vector3.h"
#include "VectorPoint3.h"
#include <string>

class Baddy
{
    public:
        Baddy();
        Baddy(GLdouble size,
                GLdouble x, GLdouble y, GLdouble z);

        // dimensions
        GLdouble size;
        Point3   pos;
        Vector3  vel;

        GLUquadric* quadric;

        int  health;
        int  damageFlash;

        void draw();
        void move();
        void unmove();
        bool pointWithin(Point3 p);
};

#endif
