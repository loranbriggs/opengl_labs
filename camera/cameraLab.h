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

#include "Camera.h"

//Global Variables
const int screenWidth = 500;	   // width of screen window in pixels
const int screenHeight = 500;	   // height of screen window in pixels

Camera cam; // global camera object
GLfloat teaX = 0;
GLfloat teaY = 0;
GLfloat teaZ = 0;
GLfloat teaAngle = 0;
#endif
