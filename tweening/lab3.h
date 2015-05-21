#ifndef LAB_ANIM_H
#define LAB_ANIM_H

#define PI 3.1415

struct GLintPoint2D {
	GLint x, y;
};

struct GLfloatPoint2D {
	GLfloat x,y;
};


//Global Variables
const int screenWidth = 500;	   // width of screen window in pixels
const int screenHeight = 500;	   // height of screen window in pixels

const float worldWidth = 500.0;
const float worldHeight = 500.0; 

const int RESOLUTION = 1000;

GLfloatPoint2D line[2];
GLfloatPoint2D pent[10];
GLfloatPoint2D star[10];
GLfloatPoint2D draw1[10];
GLfloatPoint2D draw2[RESOLUTION];
GLdouble lineLength;

// Initial values
int res = 0;
GLdouble t = 0.0;



void setWindow(float left, float right, float bottom, float top);
float computeLineLength(GLfloatPoint2D p1, GLfloatPoint2D p2);
void mySleep(int sleepMs);

float lerp(float a, float b, float t);

#endif
