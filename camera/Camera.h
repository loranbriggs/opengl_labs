#ifndef CAMERA_H
#define CAMERA_H

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

#include "Point3.h"
#include "Vector3.h"

class Camera {
private:
    Point3 eye;
    Vector3 u,v,n;
    double viewAngle, aspect, nearDist, farDist; // view volume shape
    void setModelViewMatrix(); // tell OpenGL where the camera is	

public:
    Camera(); // default constructor
    ~Camera();
    void set(Point3 eye, Point3 look, Vector3 up); // like gluLookAt()	
    void slide(float delU, float delV, float delN); // slide it	
    void roll(float angle); // roll it

    void pitch(float angle); // increase pitch
    void yaw(float angle); // yaw it
    void zoom(float move);
    void setShape(float vAng, float asp, float nearD, float farD);
};

#endif
