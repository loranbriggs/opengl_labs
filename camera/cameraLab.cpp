//Lab: Camera Control

#include <iostream>
#include "cameraLab.h"


//<<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>>>
void myInit()
{
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity0);
    glLightfv(GL_LIGHT1, GL_AMBIENT, lightIntensity1);
    

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);  // background is black
    glColor3f(1.0f, 1.0f, 1.0f);    // drawing color is white

    // set the view volume shape ----
    cam.setShape(50.0f, 64.0f/48.0f, 0.5f, 200.0f);
    //---------------------------

    //make the initial camera
    cam.set(Point3(5, 5, 5), Point3(0, 0, 0), Vector3(0, 1, 0)); 
}

//<<<<<<<<<<<<<<<<<<<<<<<< myMouse >>>>>>>>>>>>>>>>>>>>>>
void myMouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN)
    {
        mouse.updatePosition( x, -y );
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        mouse.leftDown = true;
    } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        mouse.rightDown = true;
    } else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
    {
        mouse.middleDown = true;
    } else
    {
        mouse.leftDown = false;
        mouse.rightDown = false;
        mouse.middleDown = false;
    }
    glutPostRedisplay();
}

//<<<<<<<<<<<<<<<<<<<<<<<< myMotion >>>>>>>>>>>>>>>>>>>>>>
void myMotion(int x, int y)
{
    if (mouse.leftDown || mouse.rightDown || mouse.middleDown)
    {
        mouse.updatePosition( x, -y );
        mouse.updateDiff();
    }

    if (mouse.leftDown)
    {
        // adjust pitch and roll
        cam.pitch( mouse.getDiff().y / 4 );
        cam.yaw(   mouse.getDiff().x / 4 );
    }

    if (mouse.rightDown)
    {
        // adjust pitch and roll
        cam.slide(
                mouse.getDiff().x / (screenWidth / 4 ),
                mouse.getDiff().y / (screenHeight / 4 ),
                0 );
    }


    glutPostRedisplay();
}

//<<<<<<<<<<<<<<<<<<<<<<<< myKeyboard >>>>>>>>>>>>>>>>>>>>>>
void mySpecialKeyboard(int theKey, int mouseX, int mouseY)
{
    switch(theKey)
    {
    case GLUT_KEY_LEFT:
        std::cout << "Camera move left" << std::endl;
        cam.slide(-0.2,0,0);
        break; 
    case GLUT_KEY_RIGHT:
        std::cout << "Camera move right" << std::endl;
        cam.slide(0.2,0,0);
        break;
    case GLUT_KEY_UP:
        std::cout << "Camera move up" << std::endl;
        cam.slide(0,0.2,0);
        break;
    case GLUT_KEY_DOWN:
        std::cout << "Camera move down" << std::endl;
        cam.slide(0,-0.2,0);
        break;
    case GLUT_KEY_PAGE_UP:
        // slide camera forward
        std::cout << "Camera zoom-in" << std::endl;
        cam.zoom(-0.5);
        break;
    case GLUT_KEY_PAGE_DOWN:
        // slide camera backward
        std::cout << "Camera zoom-out" << std::endl;
        cam.zoom(0.5);
        break;
    default:
        break;
    }
    glutPostRedisplay(); // draw it again
}

void myKeyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
    case 'r':
        std::cout << "Camera roll counter clock-wise " << std::endl;
        cam.roll(1.0);
        break; // roll the camera
    case 'R':
        std::cout << "Camera roll clock-wise" << std::endl;
        cam.roll(-1.0);
        break; // roll the camera back	
    case 'p':
        std::cout << "Camera pitch up" << std::endl;
        cam.pitch(1.0);
        break;
    case 'P':
        std::cout << "Camera pitch down" << std::endl;
        cam.pitch(-1.0);
        break;
    case 'y':
        std::cout << "Camera yaw left" << std::endl;
        cam.yaw(1.0);
        break;
    case 'Y':
        std::cout << "Camera yaw right" << std::endl;
        cam.yaw(-1.0);
        break;
    case 'w':
        tea1X += 0.2;
        tea1Z += 0.4;
        tea2X += 0.2;
        tea2Z += 0.4;
        break;
    case 'W':
        tea1X -= 0.2;
        tea1Z -= 0.4;
        tea2X -= 0.2;
        tea2Z -= 0.4;
        break;
    case 'e':
        teaAngle += 10;
        break;
    case 'E':
        teaAngle += 10;
        break;
    case 'a':
        // animate
        animate = !animate;
        break;
    default:
        break;
    }
    glutPostRedisplay(); // draw it again
}

void drawLighting()
{
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

//<<<<<<<<<<<<<<<<<<<<<<< drawGrid  >>>>>>>>>>>>>>>>>>>>>>>>>>
void drawGrid()
{
    for (int i = -gridDim; i < gridDim; i++)
    {
        if (i % 10 == 0)
        {
            glLineWidth(3);
            GLfloat ambient[]   = {0.3745f  ,0.01175f ,0.01175f , 1.0f};
            GLfloat diffuse[]   = {0.61424f ,0.04136f ,0.04136f , 1.0f};
            GLfloat specular[]  = {0.727811f,0.626959f,0.626959f, 1.0f};
            GLfloat shininess   =  0.6f;

            glMaterialfv(GL_FRONT, GL_AMBIENT  , ambient);
            glMaterialfv(GL_FRONT, GL_DIFFUSE  , diffuse);
            glMaterialfv(GL_FRONT, GL_SPECULAR , specular);
            glMaterialf( GL_FRONT, GL_SHININESS, shininess * 128.0);

            //draw along the x axis
            glBegin(GL_LINES);
                glVertex3f(i,0, gridDim);
                glVertex3f(i,0,-gridDim);
            glEnd();

            //draw along the z axis
            glBegin(GL_LINES);
                glVertex3f( gridDim,0,i);
                glVertex3f( -gridDim,0,i);
            glEnd();
        } else
        {
            glLineWidth(1);
            GLfloat ambient[]   = {0.1f     ,0.38725f,0.3745f  , 1.0f};
            GLfloat diffuse[]   = {0.396f   ,0.74151f,0.69102f , 1.0f};
            GLfloat specular[]  = {0.297254f,0.30829f,0.306678f, 1.0f};
            GLfloat shininess   =  0.1f;

            glMaterialfv(GL_FRONT, GL_AMBIENT  , ambient);
            glMaterialfv(GL_FRONT, GL_DIFFUSE  , diffuse);
            glMaterialfv(GL_FRONT, GL_SPECULAR , specular);
            glMaterialf( GL_FRONT, GL_SHININESS, shininess * 128.0);

            //draw along the x axis
            glBegin(GL_LINES);
                glVertex3f(i,0, gridDim);
                glVertex3f(i,0, -gridDim);
            glEnd();

            //draw along the z axis
            glBegin(GL_LINES);
                glVertex3f( gridDim,0,i);
                glVertex3f( -gridDim,0,i);
            glEnd();
        }

    }
}

void drawTeapot1()
{
    GLfloat ambient[]   = {0.24725f ,0.1995f  ,0.0745f  , 1.0f};
    GLfloat diffuse[]   = {0.75164f ,0.60648f ,0.22648f , 1.0f};
    GLfloat specular[]  = {0.628281f,0.555802f,0.366065f, 1.0f};
    GLfloat shininess   =  0.4f;

    glMaterialfv(GL_FRONT, GL_AMBIENT  , ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE  , diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR , specular);
    glMaterialf( GL_FRONT, GL_SHININESS, shininess * 128.0);

    glPushMatrix();
    glTranslated( tea1X, tea1Y, tea1Z);
    glRotated(teaAngle, 0, 1, 0);
    glutSolidTeapot(1.0); // draw the teapot
    glPopMatrix();
}

void drawTeapot2()
{
    GLfloat ambient[]   = {0.19225f ,0.19225f ,0.19225f , 1.0f};
    GLfloat diffuse[]   = {0.50754f ,0.50754f ,0.50754f , 1.0f};
    GLfloat specular[]  = {0.508273f,0.508273f,0.508273f, 1.0f};
    GLfloat shininess   =  0.4f;

    glMaterialfv(GL_FRONT, GL_AMBIENT  , ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE  , diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR , specular);
    glMaterialf( GL_FRONT, GL_SHININESS, shininess * 128.0);

    glPushMatrix();
    glTranslated( tea2X, tea2Y, tea2Z);
    glRotated(teaAngle, 0, 1, 0);
    glutSolidTeapot(1.0); // draw the teapot
    glPopMatrix();
}

//<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>>>>>>>>>>
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    drawLighting();
    glEnable(GL_LIGHT0);
    drawTeapot1();
    drawTeapot2();
    glDisable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    drawGrid();
    glDisable(GL_LIGHT1);

    glutSwapBuffers();
}

void myIdle()
{
    mySleep(100);

    if (animate)
    {
        cnt += 1;
        if (cnt > intervals)
        {
            cnt = 0;
        }
        t = (cnt*1.0)/intervals;
        position[0] = 4*cos(t*2*PI);
        position[1] = 2+ 4*cos(t*2*PI);
        position[2] = 4*sin(t*2*PI);
    }

    glutPostRedisplay();
}

//<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
    glutInit(&argc, argv);          // initialize the toolkit
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // set display mode
    glutInitWindowSize(screenWidth, screenHeight); // set window size
    glutInitWindowPosition(100, 100); // set window position on screen
    glutCreateWindow("Lab - Manipulate a camera around a teapot"); // open the screen window

    // register callback functions
    glutMouseFunc(myMouse);
    glutMotionFunc(myMotion);
    glutIdleFunc(myIdle);
    glutKeyboardFunc(myKeyboard);
    glutSpecialFunc(mySpecialKeyboard);	
    glutDisplayFunc(myDisplay);

    myInit();

    glutMainLoop();

    return( 0 );
}

void mySleep(int sleepMs)
{
#ifdef __linux__
    usleep(sleepMs * 1000);   // usleep takes sleep time in us (1 millionth of a second)
#endif
#if defined(_WIN32) || defined(_WIN64)
    Sleep(sleepMs);
#endif
}
