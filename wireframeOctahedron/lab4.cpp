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

#include <cmath>
#include <iostream>
#include "lab4.h"

using namespace std;

void genOctahedron()
{
    GLfloat v[][3] =
        {{-1.0,0.0,1.0}, {1.0,0.0,1.0}, {1.0,0.0,-1.0}, {-1.0,0.0,-1.0}, {0.0,1.5,0.0}, {0.0,-1.5,0.0}};

    for(int i = 0; i < 8; i++) {
        octahedron[i].vertices[0] = v[i][0];
        octahedron[i].vertices[1] = v[i][1];
        octahedron[i].vertices[2] = v[i][2];
    }
}

void drawTriangle(int a, int b, int c)
{
    glBegin(GL_LINE_LOOP);
        // glVertex3fv(octahedron[a].vertices) is same as
        // glVertex3f(octahedron[a].vertices[0],octahedron[a].vertices[1],octahedron[a].vertices[2])
        glVertex3fv(octahedron[a].vertices);
        glVertex3fv(octahedron[b].vertices);
        glVertex3fv(octahedron[c].vertices);
    glEnd();
}

void drawOctahedron()
{
    drawTriangle(4,0,1);
    drawTriangle(4,1,2);
    drawTriangle(4,2,3);
    drawTriangle(4,3,0);
    drawTriangle(5,0,1);
    drawTriangle(5,1,2);
    drawTriangle(5,2,3);
    drawTriangle(5,3,0);
}

void myInit(void)
{
    glClearColor(1.0,1.0,1.0,0.0);  // background color is white
    glColor3f(0.0f, 0.0f, 0.0f);    // drawing color is black

    glMatrixMode(GL_PROJECTION);    // set "camera shape"
    glLoadIdentity();

    // notice that this is not gluOrtho2D() anymore
    glOrtho(-10.0,10.0,-10.0, 10.0, 10.0, 40.0);

    // Assign points for octahedron
    genOctahedron();
}




void myKeyboard(unsigned char key, int x, int y)
{

    switch (key) {
        //
        // do what you need to do for each key stroke here
        //

        case '+':
            // up-scale
            scale *= 1.05;
            break;

        case '-':
            // down-scale
            scale *= 0.95;
            break;

        case 'y':
            // rotate around y-axis 10 degrees
            ry += 10.0;
            break;

        case 'Y':
            // rotate around y-axis -10 degrees
            ry += -10.0;
            break;

        case 'x':
            // rotate around x-axis 10 degrees
            rx += 10.0;
            break;

        case 'X':
            // rotate around x-axis -10 degrees
            rx += -10.0;
            break;

        case 'z':
            // rotate around x-axis 10 degrees
            rz += 10.0;
            break;

        case 'Z':
            // rotate around z-axis -10 degrees
            rz += -10.0;
            break;

        case 'L':
            // relect around y-axis
            tx *= -1.0;
            tz *= -1.0;
            break;

        case 'l':
            // relect around x-axis
            ty *= -1.0;
            tz *= -1.0;
            break;
        // Other cases here

        default:
            break;
    }
    glutPostRedisplay();
}

void mySpecialKeyboard(int key, int x, int y)
{
    switch (key) {

        case GLUT_KEY_UP :
            // translate positive y direction
            ty += 0.1;
            break;

        case GLUT_KEY_DOWN:
            // translate negative y direction
            ty -= 0.1;
            break;

        case GLUT_KEY_LEFT:
            // translae in negative x direction
            tx -= 0.1;
            break;

        case GLUT_KEY_RIGHT:
            // translae in positive x direction
            tx += 0.1;
            break;

        case GLUT_KEY_PAGE_UP:
            // translate positive z direction
            tz += 0.1;
            break;

        case GLUT_KEY_PAGE_DOWN:
            // translate negative z direction
            tz -= 0.1;
            break;

        case GLUT_KEY_HOME:
            // resest variables to initial values
            scale=1.0;
            tx=0.0, ty=0.0, tz=0.0;
            rx=0.0, ry=0.0, rz=0.0;
            break;

        default:
            break;
    }
    glutPostRedisplay();
}


//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);     // clear the screen

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // set the camera location and orientation
    // for Lab5, do not touch this line
    gluLookAt(10.0,10.0,15.0,0.0,0.0,0.0,0.0,1.0,0.0);

    // apply your own transformations accordingly here
    glTranslated (tx, ty, tz);
    glScalef(scale, scale, scale);
    // y rotation
    glRotated(ry, 0, 1, 0);
    // x rotation
    glRotated(rx, 1, 0, 0);
    // z rotation
    glRotated(rz, 0, 0, 1);

    // draw octahedron
    drawOctahedron();
    glFlush();		   // send all output to display

}

//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char** argv)
{
    glutInit(&argc, argv);          // initialize the toolkit
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set display mode
    glutInitWindowSize(screenWidth, screenHeight); // set window size
    glutInitWindowPosition(100, 150); // set window position on screen
    glutCreateWindow("Lab-Wireframe Octahedron"); // open the screen window

    glutDisplayFunc(myDisplay);     // register redraw function
    glutKeyboardFunc(myKeyboard);
    glutSpecialFunc(mySpecialKeyboard);
    myInit();
    glutMainLoop(); 		     // go into a perpetual loop

    return 0;
}
