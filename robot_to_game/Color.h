#ifndef COLOR
#define COLOR

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

class Color
{
    public:
        static void Black(){glColor3f(0.3f, 0.3f, 0.3f);}
        static void White(){glColor3f(1.0f, 0.960784f, 0.933333f);}
        static void dkGray(){glColor3f(0.5f, 0.5f, 0.5f);}
        static void Brown(){glColor3f(0.545098f, 0.270588f, 0.0745098f);}
        static void dkBrown(){glColor3f(0.445098f, 0.170588f, 0.0745098f);}
        static void Red(){glColor3f(0.9f, 0.0f, 0.0f);}
        static void dkRed(){glColor3f(0.4f, 0.0f, 0.0f);}
        static void dkGreen(){glColor3f(0.0f, 0.4f, 0.0f);}
        static void dkBlue(){glColor3f(0.0880392, 0.0880392, 0.339216);}
        static void Blue(){glColor3f(0.0880392, 0.0880392, 0.639216);}
        static void dkYellow(){glColor3f(0.4f, 0.4f, 0.0f);}
        static void dkPurple(){glColor3f(0.4f, 0.0f, 0.4f);}
        static void dkPink(){glColor3f(1.0f, 0.07f, 0.57f);}
};

#endif
