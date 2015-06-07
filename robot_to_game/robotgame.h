#ifndef ROBOT_GAME_H
#define ROBOT_GAME_H

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

#include <iostream>
#include <math.h>
#include "Color.h"
#include "Robot.h"
#include "Thing.h"
#include "Camera.h"
//#include "Mouse.h"
#include "Vector3.h"
#include "Point3.h"

#ifndef PI
#define PI 3.14159265359
#endif


//Global Variables
const int screenWidth = 800;	   // width of screen window in pixels
const int screenHeight = 600;	   // height of screen window in pixels

const float worldWidth = 1000.0;
const float worldHeight = 1000.0;

const float roomSize = 50.0;

const int RESOLUTION = 100;

Camera cam;
//Mouse mouse;

Robot robot;
Thing teapot;
Thing cup;
Thing water;

bool        displayAxis = true;
bool        moveCamera = false;
bool        animate     = false;
double      cameraCounter = 0.0;

// global values for camera
GLdouble eyex=25.0, eyey=25.0, eyez=25.0;
GLdouble lookx=0.0, looky=0.0, lookz=0.0;
int view=0;

// global values for shading
GLfloat ambient[] = {0.7f, 0.7f, 0.7f, 1.0f};
GLfloat diffuse[] = {0.6f, 0.6f, 0.6f, 1.0f};
GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat shininess[] = {50.0f};

GLfloat position[] = {2.0f, 6.0f, 3.0f, 0.0f};
GLfloat lightIntensity[] = {0.7f, 0.7f, 0.7f, 1.0f};


// methods
void mySleep(int sleepMs);
float lerp( float a, float b, float t );

// animation arrays
const int frames = 20;
GLdouble animX[frames]      = {   0,   12.3,  6.1,  2.2,  2.2,  2.2,  2.2,   2.2,  5.5,  5.5,
                                5.5,    5.5,  2.2,  2.2,  2.2,  2.2,  2.2,     0,    0,    0 };
//GLdouble animY[frames] = { 0, 3 };
//
GLdouble animZ[frames]      = {   0,    4.2, 12.1,  4.8,  4.8,  4.8,  4.8,   4.8,  4.8,  4.8,
                                4.8,    4.8,  4.8,  4.8,  4.8,  4.8,  4.8,     0,    0,    0 };

GLdouble animSR[frames]     = {   0,      0,    0,   85,   85,   85,   85,    85,   85,   85,
                                 85,     85,   85,   85,   85,   85,    0,     0,    0,    0 };

GLdouble animSA[frames]     = {  60,     60,   60,   60,   45,   45,   45,    80,   80,   80,
                                 80,     80,   80,   45,   45,   60,   60,    60,   60,   60 };

GLdouble animEA[frames]     = { -25,    -25,  -25,  -25,  -25,  -85,  -85,   -85,  -85,  -85,
                                -85,    -85,  -85,  -85,  -85,  -85,  -85,   -85,  -25,  -25 };

GLdouble animWA[frames]     = {  35,     35,   35,   35,   35,   35,   35,     5,    5,  -25,
                                -25,      5,    5,   35,   35,   35,   35,    35,   35,   35 };

GLdouble animFA[frames]     = {  35,     35,   35,   35,   35,   35,   31,    31,   31,   31,
                                 31,     31,   31,   31,   35,   35,   35,    35,   35,   35 };

GLdouble animTX[frames]     = {   5,      5,    5,    5,    5,    5,    5,  4.36, 7.66, 7.20,
                               7.20,   7.66, 4.36,    5,    5,    5,    5,     5,    5,    5};

GLdouble animTY[frames]     = {  35,    0.1,  0.1,  0.1,  0.1,  0.1,  0.1,  1.53, 1.53, 1.63,
                               1.63,   1.53, 1.53,  0.1,  0.1,  0.1,  0.1,   0.1,  0.1,   35 };

GLdouble animTZ[frames]     = {   5,      5,    5,    5,    5,    5,    5,     5,    5,    5,
                                  5,      5,    5,    5,    5,    5,    5,     5,    5,    5 };

GLdouble animTrX[frames]    = {   0,      0,    0,    0,    0,    0,    0,     0,    0,    0,
                                  0,      0,    0,    0,    0,    0,    0,     0,    0,    0 };

GLdouble animTrY[frames]    = {   0,      0,    0,    0,    0,    0,    0,     0,    0,    0,
                                  0,      0,    0,    0,    0,    0,    0,     0,    0,    0 };

GLdouble animTrZ[frames]    = {   0,      0,    0,    0,    0,    0,    0,     0,    0,  -25,
                                -25,      0,    0,    0,    0,    0,    0,     0,    0,    0 };

GLdouble animCX[frames]     = {   8,      8,    8,    8,    8,    8,    8,     8,    8,    8,
                                  8,      8,    8,    8,    8,    8,    8,     8,    8,    8};

GLdouble animCY[frames]     = {  35,     35,  0.2,  0.2,  0.2,  0.2,  0.2,   0.2,  0.2,  0.2,
                                0.2,    0.2,  0.2,  0.2,  0.2,  0.2,  0.2,   0.2,   35,   35 };

GLdouble animCZ[frames]     = {   5,      5,    5,    5,    5,    5,    5,     5,    5,    5,
                                  5,      5,    5,    5,    5,    5,    5,     5,    5,    5 };

GLdouble animWX[frames]     = {   5,      5,    5,    5,    5,    5,    5,  4.36, 7.66,    8,
                                  8,      8,    8,    8,    8,    8,    8,     8,    8,    8};

GLdouble animWY[frames]     = {  35,      0,    0,    0,    0,    0,    0,  1.40, 1.20, 1.50,
                               0.05,   0.05, 0.05, 0.05, 0.05, 0.05, 0.05,  0.05,   35,   35 };

GLdouble animWZ[frames]     = {   5,      5,    5,    5,    5,    5,    5,     5,    5,    5,
                                  5,      5,    5,    5,    5,    5,    5,     5,    5,    5 };

GLdouble animWS[frames]     = { 0.1,    0.1,  0.1,  0.1,  0.1,  0.1,  0.1,   0.1,  0.1,  0.1,
                                0.2,    0.2,  0.2,  0.2,  0.2,  0.2,  0.2,   0.2,  0.2,  0.2 };
// animation variables
int frame = 0;
float t;
int animationSmoothness = 100;
int cnt = 0;

#endif
