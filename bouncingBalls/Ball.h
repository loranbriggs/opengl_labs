#ifndef BALL_H
#define BALL_H

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

struct GLintVec2 {
    GLint x, y;
};

struct GLfloatVec2 {
    GLfloat x,y;
};

class Ball
{
public:
    Ball();
    Ball(float r, float x, float y);
    Ball(float r, float x, float y, float dx, float dy);
    ~Ball();
    float radius;
    GLfloatVec2 center;
    GLfloatVec2 velocity;
    bool freeze;
    bool filled;
    float Area();
    float Volume();
    void Properties();
private:
};

#endif
