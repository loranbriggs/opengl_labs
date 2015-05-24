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
#include "Mouse.h"
#include "Vector3.h"

//Global Variables
const int screenWidth = 500;	   // width of screen window in pixels
const int screenHeight = 500;	   // height of screen window in pixels

// global values for shading
GLfloat ambient[] = {0.7f, 0.7f, 0.7f, 1.0f};
GLfloat diffuse[] = {0.6f, 0.6f, 0.6f, 1.0f};
GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat shininess[] = {50.0f};

GLfloat position[] = {2.0f, 6.0f, 3.0f, 0.0f};
GLfloat lightIntensity[] = {0.7f, 0.7f, 0.7f, 1.0f};

const int gridDim =  50;

Camera cam; // global camera object
Mouse mouse;

GLfloat teaX = 0;
GLfloat teaY = 0;
GLfloat teaZ = 0;
GLfloat teaAngle = 0;
#endif
