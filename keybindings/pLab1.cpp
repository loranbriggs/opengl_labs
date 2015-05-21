//Computer Graphics Lab : Drawing an object and changing world view


// windows headers
/*
#include <windows.h>
#include <gl/Gl.h>
#include <gl/glut.h>
*/

// linux headers
#include <GL/freeglut.h>
#include <GL/gl.h>

// other headers
#include <ctime>
#include <iostream>
#include <math.h>

const int screenWidth = 500;
const int screenHeight = 500;
const float dragSpeed = 0.1;

// left, right, bottom, top
float lt, rt, bt, tp;

struct GLintPoint {
    GLint x,y;
};

GLintPoint mouseStart;

bool leftDown;

void setWindow(float left, float right, float bottom, float top);

void myInit(void)
{
    glClearColor(1.0,1.0,1.0,0.0);       // background color is white
    glColor3f(0.0f, 0.0f, 0.0f);         // drawing color is black
    glMatrixMode(GL_PROJECTION); 	   // set "camera shape"
    glLoadIdentity();
    lt = 0;
    rt = 20;
    bt = 0;
    tp = 20;
    gluOrtho2D(lt, rt, bt, tp);	// set the world window
}

void myMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        leftDown = true;
        mouseStart.x = x;
        mouseStart.y = y;
    } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        lt = 0;
        rt = 20;
        bt = 0;
        tp = 20;
    } else
    {
        leftDown = false;
    }
    glutPostRedisplay();
}

void myMotion(int x, int y)
{
    if (leftDown)
    {
        int dx = mouseStart.x - x;
        int dy = mouseStart.y - y;
        mouseStart.x = x;
        mouseStart.y = y;
        bt -= dy*dragSpeed;
        tp -= dy*dragSpeed;
        lt += dx*dragSpeed;
        rt += dx*dragSpeed;
    }
    glutPostRedisplay();
}

void myKeyboard(unsigned char theKey, int mouseX, int mouseY)
{
    switch(theKey) {
        case 'z':
            // zoom-in
            std::cout << "zoom-in" << std::endl;
            lt += 1;
            rt -= 1;
            bt += 1;
            tp -= 1;
            break;
        case 'Z':
            // zoom-out
            std::cout << "zoom-out" << std::endl;
            lt -= 1;
            rt += 1;
            bt -= 1;
            tp += 1;
            break;
        default:
            break;		      // do nothing
    }
    glutPostRedisplay(); // implicitly call myDisplay
}

void mySpecialKeyboard(int theKey, int mouseX, int mouseY)
{
    switch(theKey) {
        case GLUT_KEY_UP:
            std::cout << "up!" << std::endl;
            // move the object to the top in a small amount
            bt -= 2;
            tp -= 2;
            break;
        case GLUT_KEY_DOWN:
            std::cout << "down!" << std::endl;
            // move the object to the bottom in a small amount
            bt += 2;
            tp += 2;
            break;
        case GLUT_KEY_LEFT:
            std::cout << "left!" << std::endl;
            // move the object to the left in a small amount
            lt -= 2;
            rt -= 2;
            break;
        case GLUT_KEY_RIGHT:
            std::cout << "right!" << std::endl;
            // move the object to the right in a small amount
            lt += 2;
            rt += 2;
            break;
        default:
            break;		      // do nothing
    }
    glutPostRedisplay(); // implicitly call myDisplay
}

//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void)
{
    setWindow(lt, rt, bt, tp);
    glClear(GL_COLOR_BUFFER_BIT);     // clear the screen

    glBegin(GL_LINE_LOOP);
        glVertex2i(6.5,0);
        glVertex2i(9,5);
        glVertex2i(14,5.5);
        glVertex2i(10.5,9);
        glVertex2i(12,14);
        glVertex2i(6.5,11.5);
        glVertex2i(2,14);
        glVertex2i(3.5,9);
        glVertex2i(0,5.5);
        glVertex2i(5,5);
    glEnd();

    //glFlush();
    glutSwapBuffers();
}


//--------------- setWindow ---------------------
void setWindow(float left, float right, float bottom, float top)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(left, right, bottom, top);
}

//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char** argv)
{
    glutInit(&argc, argv);          // initialize the toolkit
    //glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set display mode
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // set display mode
    glutInitWindowSize(screenWidth, screenHeight); // set window size
    glutInitWindowPosition(100, 150); // set window position on screen
    glutCreateWindow("Computer Graphics - Practice Lab 1"); // open the screen window

    glutDisplayFunc(myDisplay);     // register redraw function
    glutKeyboardFunc(myKeyboard);
    glutSpecialFunc(mySpecialKeyboard);
    glutMouseFunc(myMouse);
    glutMotionFunc(myMotion);

    myInit();

    glutMainLoop(); 		     // go into a perpetual loop
    return 0;
}
