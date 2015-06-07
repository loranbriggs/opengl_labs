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
#include "Material.h"
#include "Camera.h"
#include "Mouse.h"
#include "Vector3.h"
#include "Point3.h"
#include "VectorPoint3.h"
#include "Robot.h"
#include "Thing.h"
#include "Baddy.h"
#include <string>

#ifndef PI
#define PI 3.14159265359
#define RADS (PI/180)
#define DEGS (180/PI)
#endif

//Global Variables
const int screenWidth = 800;	   // width of screen window in pixels
const int screenHeight = 600;	   // height of screen window in pixels

// lighting
GLfloat lightingPosition[] = {2.0f, 6.0f, 3.0f, 1.0f};
GLfloat lightIntensity0[] = {0.7f, 0.7f, 0.7f, 1.0f};
GLfloat lightIntensity1[] = {1.0f, 1.0f, 1.0f, 1.0f};

const int gridDim =  10;

Robot robot;

GLfloat camBehind;
GLfloat camAhead;
Point3 camLoc;
Point3 camLook;

Camera cam; // global camera object
Mouse mouse;

// key states
bool keyPressed[255] = {false};
bool upPressed = false;
bool downPressed = false;
bool leftPressed = false;
bool rightPressed = false;
int  inverseCam = 1;

const int NUM_THINGS = 4;
Thing things[NUM_THINGS];
Thing table1;
Thing table2;

bool table1Flash;
bool table2Flash;
bool flashOn;

Baddy baddy1;
Baddy baddy2;

bool damageFlash;

// methods
void mySleep(int sleepMs);
void updateCam();

#endif
