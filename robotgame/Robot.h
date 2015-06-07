#ifndef ROBOT
#define ROBOT

#ifndef PI
#define PI 3.14159265359
#define RADS (PI/180)
#define DEGS (180/PI)
#endif

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
#include "Material.h"

enum ClawState { CLOSED, CLOSING, OPENED, OPENING, HOLDING };

class Robot
{
    public:
        Robot();

        // positions
        Point3 pos;
        GLdouble shoulderRotation;
        GLdouble shoulderAngle;
        GLdouble elbowAngle;
        GLdouble wristAngle;
        GLdouble fingersAngle;
        Point3   elbowPos;
        Point3   clawPos;

        // dimensions
        GLdouble width;
        GLdouble length;
        GLdouble height;
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
        GLdouble    fingersAngleHolding;

        // other
        GLdouble numberOfFingers;
        bool        activated;
        GLUquadric* quadric;
        int         objectInClaw;
        ClawState   clawState;
        int health;

        // methods
        GLdouble baseRadius(){ return sqrt( pow(width,2) + pow(length,2) ) / 3; }
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

        void updateClawPos();

};

#endif
