#ifndef LAB_ANIM_H
#define LAB_ANIM_H

#ifndef PI
#define PI 3.14159265359
#endif

// windows headers
#ifdef WINDOWS
#include <windows.h>
#include <gl/Gl.h>
#include <gl/glut.h>
#endif

// linux headers
#ifdef __linux__
#include <unistd.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#endif

// other headers
#include <ctime>
#include <iostream>
#include <math.h>
#include <cmath>
#include <algorithm>

#include "Ball.h"

//Global Variables
const int screenWidth = 500;	   // width of screen window in pixels
const int screenHeight = 500;	   // height of screen window in pixels

const float worldWidth = 500.0;
const float worldHeight = 500.0; 

const int MAX_BALLS = 5;
const int MIN_BALLS = 1;
Ball balls[MAX_BALLS];
int ballCnt = 0;
int selectedBall = 0;
int mouseSelected = -1;
bool leftDown = false;
GLintVec2 mouseStart;

GLfloatVec2 left, top, right, bottom;

// Initial values

void setWindow(float left, float right, float bottom, float top);
void mySleep(int sleepMs);
float randFloat(float a, float b);
float randFloat();
void addBall();
void addBall(float r, float x, float y, float dx, float dy);
void removeBall();

int dot(GLintVec2 a, GLintVec2 b);
float dot(GLfloatVec2 a, GLfloatVec2 b);

void reflect(GLfloatVec2 &a, GLfloatVec2 b);
void checkCollision(Ball &a, Ball&b);
void unFreeze(Ball &ball);
void drawLabel(int i, float x, float y);
#endif
