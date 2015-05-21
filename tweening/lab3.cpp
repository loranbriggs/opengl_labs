//Computer Graphics Lab - Animation
//
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

#include "lab3.h"

using namespace std;

void myInit(void)
{
    glClearColor(1.0,1.0,1.0,0.0);      // background color is white
    glColor3f(0.0f, 0.0f, 1.0f);        // drawing color is blue
    setWindow(-worldWidth/2, worldWidth/2, -worldHeight/2, worldHeight/2); // replaces the following three lines

    //glMatrixMode(GL_PROJECTION); 	    // set "camera shape"
    //glLoadIdentity();
    //gluOrtho2D(-worldWidth,worldWidth,-worldHeight, worldHeight);


    line[0].x = 0;
    line[0].y = 0;
    line[1].x = 100;
    line[1].y = 0;
    lineLength = computeLineLength(line[0], line[1]);

    pent[0].x =    0;
    pent[0].y = -200;
    pent[1].x =    0;
    pent[1].y = -200;
    pent[2].x = -190;
    pent[2].y =  -62;
    pent[3].x = -190;
    pent[3].y =  -62;
    pent[4].x = -118;
    pent[4].y =  162;
    pent[5].x = -118;
    pent[5].y =  162;
    pent[6].x =  118;
    pent[6].y =  162;
    pent[7].x =  118;
    pent[7].y =  162;
    pent[8].x =  190;
    pent[8].y =  -62;
    pent[9].x =  190;
    pent[9].y =  -62;

    star[0].x =    0;
    star[0].y = -100;
    star[1].x =  -25;
    star[1].y =  -25;
    star[2].x = -100;
    star[2].y =  -25;
    star[3].x =  -25;
    star[3].y =   25;
    star[4].x =  -50;
    star[4].y =  100;
    star[5].x =    0;
    star[5].y =   50;
    star[6].x =   50;
    star[6].y =  100;
    star[7].x =   25;
    star[7].y =   25;
    star[8].x =  100;
    star[8].y =  -25;
    star[9].x =   25;
    star[9].y =  -25;

    glLineWidth(3);
}

void myIdle()
{
    //this function will be invoked when idle

    res += 1;
    if(res > RESOLUTION ) res=0;
    t = (res*1.0)/RESOLUTION;


    line[1].x = lineLength * cos(2*PI*t);
    line[1].y = lineLength * sin(2*PI*t);

    for (int i = 0; i < 10; i++)
    {
        // pent to star lerp
        draw1[i].x = lerp(pent[i].x, star[i].x, t);
        draw1[i].y = lerp(pent[i].y, star[i].y, t);
    }

    float th;
    int s;
    for (int i = 0; i < RESOLUTION; i++)
    {
        // pent to circle lerp
        th = (i*1.0)/(RESOLUTION*1.0);
        s = i/(RESOLUTION/10);
        draw2[i].x = lerp(pent[s].x, 250*cos(-th*2*PI), t);
        draw2[i].y = lerp(pent[s].y, 250*sin(-th*2*PI), t);
    }

    /*
    float d;
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < RESOLUTION; i++)
    {
        d = (i*1.0)/RESOLUTION;
        glVertex2f(250* cos(d*2*PI), 250*sin(d*2*PI));
    }
    glEnd();
    */


    glutPostRedisplay();
}


//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void)
{
    mySleep(1);
    glClear(GL_COLOR_BUFFER_BIT);     // clear the screen
    glBegin(GL_LINES);
    //draw shape here
        glVertex2f(line[0].x, line[0].y);
        glVertex2f(line[1].x, line[1].y);
    glEnd();

    glPointSize(4.0);

    glLineWidth(4.0);

    // draw pentagon
    /*
    glColor3f(1.0f, 0.0f, 0.0f);        // drawing color is blue
    glBegin(GL_POINTS);
    for (int i = 0; i < 10; i++)
    {
        glVertex2f(pent[i].x, pent[i].y);
    }
    glEnd();
    glColor3f(0.0f, 0.0f, 1.0f);        // drawing color is blue
    */

    // draw star
    /*
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 10; i++)
    {
        glVertex2f(star[i].x, star[i].y);
    }
    glEnd();
    */

    // draw circle
    /*
    float d;
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 500; i++)
    {
        d = (i*1.0)/RESOLUTION;
        glVertex2f(250* cos(d*2*PI), 250*sin(d*2*PI));
    }
    glEnd();
    */

    // draw lerp between pent and star
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 10; i++)
    {
        glVertex2f(draw1[i].x, draw1[i].y);
    }
    glEnd();

    // draw lerp between pent and circle
    glColor3f(0.0f, 1.0f, 0.0f);        // drawing color is blue
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < RESOLUTION; i++)
    {
        glVertex2f(draw2[i].x, draw2[i].y);
    }
    glEnd();
    glColor3f(0.0f, 0.0f, 1.0f);        // drawing color is blue

    glutSwapBuffers();	// send all output to display
}

//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char** argv)
{
    glutInit(&argc, argv);          // initialize the toolkit
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // set display mode
    glutInitWindowSize(screenWidth, screenHeight); // set window size
    glutInitWindowPosition(100, 150); // set window position on screen
    glutCreateWindow("Computer Graphics Lab - Animation"); // open the screen window

    glutDisplayFunc(myDisplay);     // register redraw callback function
    glutIdleFunc(myIdle);			// register idle callback function

    myInit();
    glutMainLoop(); 		     // go into a perpetual loop
    return 0;
}


//--------------- setWindow ---------------------
void setWindow(float left, float right, float bottom, float top)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(left, right, bottom, top);
}

float computeLineLength(GLfloatPoint2D p1, GLfloatPoint2D p2)
{
    return sqrt((p2.x-p1.x)*(p2.x-p1.x)+(p2.y-p1.y)*(p2.y-p1.y));
}

float lerp(float a, float b, float t)
{
    return a + (b - a) * t;
}

void mySleep(int sleepMs)
{
#ifdef __linux__
    usleep(sleepMs * 1000);   // usleep takes sleep time in us (1 millionth of a second)
#endif
#ifdef WINDOWS
    Sleep(sleepMs);
#endif
}
