//Computer Graphics Lab : Drawing an object and changing world view


// windows headers
#ifdef _WIN32
#include <windows.h>
#include <gl/Gl.h>
#include <gl/glut.h>
#endif

// linux headers
#ifdef __linux__
#include <GL/freeglut.h>
#include <GL/gl.h>
#endif

// other headers
#include <ctime>
#include <iostream>
#include <math.h>

const int screenWidth = 500;
const int screenHeight = 500;
const float PI = 3.14159265359;
const int RESOLUTION = 100;

// left, right, bottom, top
float lt, rt, bt, tp, width, height;

struct GLintPoint {
    GLint x,y;
};

GLintPoint mouseStart;
GLint radius1;
GLint radius2;

bool leftDown;
bool connected = false;
int  thickness = 2;

void setWindow(float left, float right, float bottom, float top);

void myInit(void)
{
    glClearColor(1.0,1.0,1.0,0.0);       // background color is white
    glColor3f(0.0f, 0.0f, 0.0f);         // drawing color is black
    glMatrixMode(GL_PROJECTION); 	   // set "camera shape"
    glLoadIdentity();
    lt = -10;
    rt = 10;
    bt = -10;
    tp = 10;
    width = rt - lt;
    height = tp - bt;

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
        lt = -10;
        rt = 10;
        bt = -10;
        tp = 10;
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
        float dx = (mouseStart.x - x)*width/screenWidth;
        float dy = (mouseStart.y - y)*height/screenHeight;
        mouseStart.x = x;
        mouseStart.y = y;
        bt -= dy;
        tp -= dy;
        lt += dx;
        rt += dx;
    }
    glutPostRedisplay();
}

void myKeyboard(unsigned char theKey, int mouseX, int mouseY)
{
    switch(theKey) {
        case 'z':
            // zoom-in
            lt += 1;
            rt -= 1;
            bt += 1;
            tp -= 1;
            break;
        case 'Z':
            // zoom-out
            lt -= 1;
            rt += 1;
            bt -= 1;
            tp += 1;
            break;
        case 't':
        case 'T':
            connected = !connected;
            break;
        case '+':
            radius1 += 1;
            radius2 += 1;
            break;
        case '-':
            radius1 -= 1;
            radius2 -= 1;
            break;
        case 'b':
            thickness += 1;
            break;
        case 'B':
            thickness -= 1;
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
            // move the object to the top in a small amount
            bt -= 2;
            tp -= 2;
            break;
        case GLUT_KEY_DOWN:
            // move the object to the bottom in a small amount
            bt += 2;
            tp += 2;
            break;
        case GLUT_KEY_LEFT:
            // move the object to the left in a small amount
            lt += 2;
            rt += 2;
            break;
        case GLUT_KEY_RIGHT:
            // move the object to the right in a small amount
            lt -= 2;
            rt -= 2;
            break;
        default:
            break;		      // do nothing
    }
    glutPostRedisplay(); // implicitly call myDisplay
}

float ellipseX(float t)
{
    return radius1*cos(2*PI*t);
}

float ellipseY(float t)
{
    return radius2*sin(2*PI*t);
}

//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void)
{
    setWindow(lt, rt, bt, tp);
    glClear(GL_COLOR_BUFFER_BIT);     // clear the screen

    if (connected)
    {
        glLineWidth(thickness);
        glBegin(GL_LINE_LOOP);
    } else {
        glPointSize(thickness);
        glBegin(GL_POINTS);
    }
    for (int i = 0; i < RESOLUTION; i += 1)
    {
        float t = i*1.0/RESOLUTION;
        glVertex2f(ellipseX(t),ellipseY(t));
    }
    glEnd();

    //glFlush();
    glutSwapBuffers();
}

//--------------- get input ---------------------
void userInput()
{
    char selection;
    int cnt = 0;
    while (cnt < 100)
    {
        std::cout << "Choose which shape to draw:" << std::endl;
        std::cout << "\t1.Circle" << std::endl;
        std::cout << "\t2.Ellipse" << std::endl;
        std::cin  >> selection;
        if (selection == '1' || selection == '2') break;
    }

    if ( cnt > 99 )
    {
        std::cout << "stuck in endless loop" << std::endl;
        exit(1);
    }

    if (selection == '1')
    {
        std::cout << "Enter the radius of the circle: ";
        std::cin  >> radius1;
        radius2 = radius1;
    } else {
        std::cout << "Enter the width of the ellipse: ";
        std::cin  >> radius1;
        std::cout << "Enter the height of the ellipse: ";
        std::cin  >> radius2;
    }

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
    userInput();

    glutInit(&argc, argv);          // initialize the toolkit
    //glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set display mode
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // set display mode
    glutInitWindowSize(screenWidth, screenHeight); // set window size
    glutInitWindowPosition(100, 150); // set window position on screen
    glutCreateWindow("Computer Graphics - Lab 2"); // open the screen window

    glutDisplayFunc(myDisplay);     // register redraw function
    glutKeyboardFunc(myKeyboard);
    glutSpecialFunc(mySpecialKeyboard);
    glutMouseFunc(myMouse);
    glutMotionFunc(myMotion);

    myInit();

    glutMainLoop(); 		     // go into a perpetual loop
    return 0;
}
