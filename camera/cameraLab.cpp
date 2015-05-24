//Lab: Camera Control

#include <iostream>
#include "cameraLab.h"


//<<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>>>
void myInit()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);

    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);

    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);  // background is black
    glColor3f(1.0f, 1.0f, 1.0f);    // drawing color is white

    // set the view volume shape ----
    cam.setShape(50.0f, 64.0f/48.0f, 0.5f, 200.0f);
    //---------------------------

    //make the initial camera
    cam.set(Point3(4, 4, 4), Point3(0, 0, 0), Vector3(0, 1, 0)); 
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
        teaX += 0.2;
        teaZ += 0.4;
        break;
    case 'W':
        teaX -= 0.2;
        teaZ -= 0.4;
        break;
    case 'e':
        teaAngle += 10;
        break;
    case 'E':
        teaAngle += 10;
        break;
    default:
        break;
    }
    glutPostRedisplay(); // draw it again
}

//<<<<<<<<<<<<<<<<<<<<<<< drawGrid  >>>>>>>>>>>>>>>>>>>>>>>>>>
void drawGrid()
{
    for (int i = -gridDim; i < gridDim; i++)
    {
        if (i % 10 == 0)
        {
            // draw red and bold
            glLineWidth(3);
            glColor3f(1.0f, 0.0f, 0.0f);

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
            //draw along the x axis
            glColor3f(0.0f, 1.0f, 0.0f);
            glBegin(GL_LINES);
                glVertex3f(i,0, gridDim);
                glVertex3f(i,0, -gridDim);
            glEnd();

            //draw along the z axis
            glColor3f(0.0f, 0.0f, 1.0f);
            glBegin(GL_LINES);
                glVertex3f( gridDim,0,i);
                glVertex3f( -gridDim,0,i);
            glEnd();
        }

    }
}

void drawTeapot()
{
    glColor3f(0.8f, 0.8f, 1.0f);

    glPushMatrix();
    glTranslated( teaX, teaY, teaZ);
    glRotated(teaAngle, 0, 1, 0);
    glutSolidTeapot(1.0); // draw the teapot
    glPopMatrix();
}


//<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>>>>>>>>>>
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawGrid();
    drawTeapot();

    glutSwapBuffers();
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
    glutKeyboardFunc(myKeyboard);
    glutSpecialFunc(mySpecialKeyboard);	
    glutDisplayFunc(myDisplay);

    myInit();

    glutMainLoop();

    return( 0 );
}
