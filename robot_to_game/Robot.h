#ifndef ROBOT
#define ROBOT

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

class Robot
{
    public:
        Robot();

        // positions
        GLdouble x;
        GLdouble y;
        GLdouble z;
        GLdouble shoulderRotation;
        GLdouble shoulderAngle;
        GLdouble elbowAngle;
        GLdouble wristAngle;
        GLdouble fingersAngle;

        // dimensions
        GLdouble width;
        GLdouble scaleX;
        GLdouble scaleY;
        GLdouble scaleZ;
        GLdouble wheelRadius;
        GLdouble shoulderRadius;
        GLdouble upperarmLength;
        GLdouble upperarmRadius;
        GLdouble elbowRadius;
        GLdouble forearmLength;
        GLdouble forearmRadius;
        GLdouble wristRadius;
        GLdouble fingersLength;
        GLdouble fingersRadius;


        // min / max angles
        GLdouble    shoulderAngleMax;
        GLdouble    shoulderAngleMin;
        GLdouble    elbowAngleMax;
        GLdouble    elbowAngleMin;
        GLdouble    wristAngleMax;
        GLdouble    wristAngleMin;
        GLdouble    fingersAngleMax;
        GLdouble    fingersAngleMin;

        // other
        GLdouble numberOfFingers;
        bool        activated;
        GLUquadric* quadric;

        // methods
        GLdouble baseRadius(){ return sqrt( pow(scaleX,2) + pow(scaleZ,2) ) / 3; }
        void Reset();
        void drawBase();
        void drawWheels();
        void drawShoulder();
        void drawUpperarm();
        void drawElbow();
        void drawForearm();
        void drawWrist();
        void drawFingers();
        void draw();

};

#endif
