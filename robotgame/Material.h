#ifndef MATERIAL_H
#define MATERIAL_H

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

class Material
{
    public:
        static void Gold()
        {
            GLfloat ambient[]   = {0.24725f ,0.1995f  ,0.0745f  , 1.0f};
            GLfloat diffuse[]   = {0.75164f ,0.60648f ,0.22648f , 1.0f};
            GLfloat specular[]  = {0.628281f,0.555802f,0.366065f, 1.0f};
            GLfloat shininess   =  0.4f;

            glMaterialfv(GL_FRONT, GL_AMBIENT  , ambient);
            glMaterialfv(GL_FRONT, GL_DIFFUSE  , diffuse);
            glMaterialfv(GL_FRONT, GL_SPECULAR , specular);
            glMaterialf( GL_FRONT, GL_SHININESS, shininess * 128.0);
        }
        static void Silver()
        {
            GLfloat ambient[]   = {0.19225f ,0.19225f ,0.19225f , 1.0f};
            GLfloat diffuse[]   = {0.50754f ,0.50754f ,0.50754f , 1.0f};
            GLfloat specular[]  = {0.508273f,0.508273f,0.508273f, 1.0f};
            GLfloat shininess   =  0.4f;

            glMaterialfv(GL_FRONT, GL_AMBIENT  , ambient);
            glMaterialfv(GL_FRONT, GL_DIFFUSE  , diffuse);
            glMaterialfv(GL_FRONT, GL_SPECULAR , specular);
            glMaterialf( GL_FRONT, GL_SHININESS, shininess * 128.0);
        }
        static void Ruby()
        {
            GLfloat ambient[]   = {0.3745f  ,0.01175f ,0.01175f , 1.0f};
            GLfloat diffuse[]   = {0.61424f ,0.04136f ,0.04136f , 1.0f};
            GLfloat specular[]  = {0.727811f,0.626959f,0.626959f, 1.0f};
            GLfloat shininess   =  0.6f;

            glMaterialfv(GL_FRONT, GL_AMBIENT  , ambient);
            glMaterialfv(GL_FRONT, GL_DIFFUSE  , diffuse);
            glMaterialfv(GL_FRONT, GL_SPECULAR , specular);
            glMaterialf( GL_FRONT, GL_SHININESS, shininess * 128.0);
        }
        static void Turquoise()
        {
            GLfloat ambient[]   = {0.1f     ,0.38725f,0.3745f  , 1.0f};
            GLfloat diffuse[]   = {0.396f   ,0.74151f,0.69102f , 1.0f};
            GLfloat specular[]  = {0.297254f,0.30829f,0.306678f, 1.0f};
            GLfloat shininess   =  0.1f;

            glMaterialfv(GL_FRONT, GL_AMBIENT  , ambient);
            glMaterialfv(GL_FRONT, GL_DIFFUSE  , diffuse);
            glMaterialfv(GL_FRONT, GL_SPECULAR , specular);
            glMaterialf( GL_FRONT, GL_SHININESS, shininess * 128.0);
        }

        static void Obsidian()
        {
            GLfloat ambient[]   = {0.05375f     ,0.05f,0.06625f  , 1.0f};
            GLfloat diffuse[]   = {0.18275f   ,0.17f,0.22525f , 1.0f};
            GLfloat specular[]  = {0.332741f,0.328634f,0.346435f, 1.0f};
            GLfloat shininess   =  0.3f;

            glMaterialfv(GL_FRONT, GL_AMBIENT  , ambient);
            glMaterialfv(GL_FRONT, GL_DIFFUSE  , diffuse);
            glMaterialfv(GL_FRONT, GL_SPECULAR , specular);
            glMaterialf( GL_FRONT, GL_SHININESS, shininess * 128.0);
        }

        static void Pearl()
        {
            GLfloat ambient[]   = {0.25f,0.20725f,0.20725f  , 1.0f};
            GLfloat diffuse[]   = {1.0f,0.829f,0.829f , 1.0f};
            GLfloat specular[]  = {0.296648f,0.296648f,0.296648f, 1.0f};
            GLfloat shininess   =  0.088f;

            glMaterialfv(GL_FRONT, GL_AMBIENT  , ambient);
            glMaterialfv(GL_FRONT, GL_DIFFUSE  , diffuse);
            glMaterialfv(GL_FRONT, GL_SPECULAR , specular);
            glMaterialf( GL_FRONT, GL_SHININESS, shininess * 128.0);
        }

        static void Copper()
        {
            GLfloat ambient[]   = {0.19125f, 0.0735f,0.0225f  , 1.0f};
            GLfloat diffuse[]   = {0.7038f,0.27048f,0.0828f , 1.0f};
            GLfloat specular[]  = {0.256777f, 0.137622f, 0.086014f, 1.0f};
            GLfloat shininess   =  0.1f;

            glMaterialfv(GL_FRONT, GL_AMBIENT  , ambient);
            glMaterialfv(GL_FRONT, GL_DIFFUSE  , diffuse);
            glMaterialfv(GL_FRONT, GL_SPECULAR , specular);
            glMaterialf( GL_FRONT, GL_SHININESS, shininess * 128.0);
        }

};

#endif
