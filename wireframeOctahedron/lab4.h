#ifndef LAB_OBJ_TRANS_H
#define LAB_OBJ_TRANS_H

struct GLfloatPoint3D {
    GLfloat x,y,z;
};

struct GLfloatPoint3Dv {
    GLfloat vertices[3];
};

//Global Variables
const int screenWidth = 500;	   // width of screen window in pixels
const int screenHeight = 500;	   // height of screen window in pixels

GLfloatPoint3Dv octahedron[8];

// Initial values
GLdouble scale=1.0;
GLdouble tx=0.0, ty=0.0, tz=0.0;
GLdouble rx=0.0, ry=0.0, rz=0.0;
GLdouble rotation_angle = 10.0;

#endif
