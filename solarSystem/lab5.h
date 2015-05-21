#ifndef LAB_SOLAR_H
#define LAB_SOLAR_H

#ifdef WINDOWS
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

#define PI 3.1415


//Global Variables
const int screenWidth = 500;	   // width of screen window in pixels
const int screenHeight = 500;	   // height of screen window in pixels

const float worldWidth = 500.0;
const float worldHeight = 500.0;

const int RESOLUTION = 100;

// Initial values
GLdouble earthX, earthZ, earthRadius;

// Rotation Constants
GLdouble scale=0.0;
GLdouble sunRotateScale;
GLdouble mercuryRotateScale;
GLdouble venusRotateScale;
GLdouble earthRotateScale;
GLdouble moonRotateScale;
GLdouble marsRotateScale;
GLdouble mercuryOrbitScale;
GLdouble venusOrbitScale;
GLdouble earthOrbitScale;
GLdouble moonOrbitScale;
GLdouble marsOrbitScale;


GLdouble   mercuryAxis = 0.7;
GLdouble   venusAxis = 1.0;
GLdouble   earthMinorAxis = 1.5;
GLdouble   earthMajorAxis = 2.5;
GLdouble   marsAxis = 3.2;

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

#endif
