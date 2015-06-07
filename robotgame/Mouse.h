#ifndef MOUSE_H
#define MOUSE_H

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

#include "Point3.h"
#include "Vector3.h"

class Mouse {
private:

public:
    Point3 current;
    Point3 previous;
    Vector3 diff;

    bool leftDown;
    bool rightDown;
    bool middleDown;

    void updateDiff() { diff.setDiff( current, previous ); }

    void updatePosition(int x, int y)
    {
        previous.set(current);
        current.set( x, -y, 0 );
        updateDiff();
    }

    Vector3 getDiff() { return diff; }
};

#endif
