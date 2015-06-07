#ifndef LAB_CAMERA_H
#define LAB_CAMERA_H

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
#include "Camera.h"
#include "Mouse.h"
#include "Vector3.h"

#define PI 3.1415

//Global Variables
const int screenWidth = 500;	   // width of screen window in pixels
const int screenHeight = 500;	   // height of screen window in pixels

// lighting
GLfloat position[] = {2.0f, 6.0f, 3.0f, 1.0f};
GLfloat lightIntensity0[] = {0.7f, 0.7f, 0.7f, 1.0f};
GLfloat lightIntensity1[] = {1.0f, 1.0f, 1.0f, 1.0f};

const int gridDim =  5;

Camera cam; // global camera object
Mouse mouse;

GLfloat tea1X = 2;
GLfloat tea1Y = 0;
GLfloat tea1Z = -2;

GLfloat tea2X = -2;
GLfloat tea2Y = 0;
GLfloat tea2Z = 2;

GLfloat teaAngle = 0;

// animation variables
bool animate = false;
int cnt = 0;
float t;
int intervals = 100;
int scale = 3;

// methods
void mySleep(int sleepMs);

#endif
