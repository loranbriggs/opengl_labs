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
        static void Black();
        static void White();
        static void dkGray();
        static void Brown();
        static void dkBrown();
        static void Red();
        static void dkRed();
        static void dkGreen();
        static void dkBlue();
        static void Blue();
        static void dkYellow();
        static void dkPurple();
        static void dkPink();
};

#endif
