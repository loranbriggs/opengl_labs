#include "robotarm.h"

void myInit()
{

    quad = gluNewQuadric();
    cup.size = 0.2;
    cup.rx = 90;

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

    glClearColor(1.0f, 1.0f, 1.0f,0.0f);  // background is white

    glMatrixMode(GL_PROJECTION); // set the view volume shape
    glLoadIdentity();
    glOrtho(-9.5*worldWidth/worldHeight, 9.5*worldWidth/worldHeight, -9.5, 9.5, 0.1, 100);
}


void drawAxes()
{
    //x
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
        glVertex3f(0,0,0);
        glVertex3f(100,0,0);
    glEnd();
    glPushMatrix();
        glTranslatef(4, 0, 0);
        glScalef(0.01, 0.01, 0.01);
        glutStrokeCharacter(GLUT_STROKE_ROMAN, 'x');
    glPopMatrix();

    //y
    glColor3f(1.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
        glVertex3f(0,0,0);
        glVertex3f(0,100,0);
    glEnd();
    glPushMatrix();
        glTranslatef(0, 4, 0);
        glScalef(0.01, 0.01, 0.01);
        glutStrokeCharacter(GLUT_STROKE_ROMAN, 'y');
    glPopMatrix();

    //z
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
        glVertex3f(0,0,0);
        glVertex3f(0,0,100);
    glEnd();
    glPushMatrix();
        glTranslatef(-0.5, 0, 4);
        glScalef(0.01, 0.01, 0.01);
        glutStrokeCharacter(GLUT_STROKE_ROMAN, 'z');
    glPopMatrix();

}

void drawWheels()
{
    Color::Black();
    for (int i = 0; i < 4; i++)
    {
        glPushMatrix();
        switch (i)
        {
            case 0:
                glTranslated( robot.baseRadius(), 0, robot.baseRadius() );
                break;
            case 1:
                glTranslated( robot.baseRadius(), 0, -robot.baseRadius() );
                break;
            case 2:
                glTranslated( -robot.baseRadius(), 0, robot.baseRadius() );
                break;
            case 3:
                glTranslated( -robot.baseRadius(), 0, -robot.baseRadius() );
                break;
        }
        glRotated( -robot.x*80, 0, 0, 1);             // spin wheel
        glRotated( -robot.z*80, 1, 0, 0);             // spin wheel
        glutSolidSphere( robot.wheelRadius, 4, 4);
        glPopMatrix();
    }
}

void drawGround()
{
    Color::dkBrown();
    glPushMatrix();
    glTranslated( 4, -0.4, 4);
    glScaled( 1, 0.01, 1);
    glutSolidCube( 18 );
    glPopMatrix();
}

void drawBase()
{
    Color::dkBlue();
    glTranslated(robot.x,0,robot.z);
    glPushMatrix();
    glScaled( robot.scaleX, robot.scaleY, robot.scaleZ);
    glutSolidCube(robot.width);
    glPopMatrix();
    drawWheels();
}

void drawShoulder()
{
    if (robot.activated)
    {
        Color::Red();
    } else
    {
        Color::dkGray();
    }
    glTranslated(0,robot.width/4,0);
    glRotated(robot.shoulderRotation, 0, 1, 0);
    glRotated(-robot.shoulderAngle, 1, 0, 0);
    glutSolidSphere(robot.shoulderRadius, 10, 4);
}

void drawUpperarm()
{
    Color::dkBlue();
    gluCylinder(quad, robot.upperarmRadius, robot.upperarmRadius, robot.upperarmLength, 16, 16);
}

void drawElbow()
{
    if (robot.activated)
    {
        Color::Red();
    } else
    {
        Color::dkGray();
    }
    glTranslated(0,0,robot.upperarmLength);
    glRotated(-robot.elbowAngle, 1, 0, 0);
    glutSolidSphere(robot.elbowRadius, 10, 4);
}

void drawForearm()
{
    Color::dkBlue();
    gluCylinder(quad, robot.forearmRadius, robot.forearmRadius, robot.forearmLength, 8, 8);
}

void drawWrist()
{
    if (robot.activated)
    {
        Color::Red();
    } else
    {
        Color::dkGray();
    }
    glTranslated(0,0,robot.forearmLength);
    glRotated(-robot.wristAngle, 1, 0, 0);
    glutSolidSphere(robot.wristRadius, 10, 4);
}

void drawFingers()
{
    if (robot.activated)
    {
        Color::dkPink();
    } else
    {
        Color::dkGray();
    }

    for (int f = 0; f < robot.numberOfFingers; f++)
    {
        glPushMatrix();
        glRotated( (360.0/robot.numberOfFingers)*f, 0, 1, 0);
        glRotated(robot.fingersAngle*4, 1, 0, 0);
        gluCylinder(quad, robot.fingersRadius, robot.fingersRadius, robot.fingersLength, 4, 4);
        glPopMatrix();
    }

}

void drawTeapot()
{
    Color::dkGreen();
    glPushMatrix();
    glTranslated( teapot.x, teapot.y, teapot.z);
    glRotated( teapot.rx, 1, 0, 0 );
    glRotated( teapot.ry, 0, 1, 0 );
    glRotated( teapot.rz, 0, 0, 1 );
    glutSolidTeapot( teapot.size );
    glPopMatrix();
}

void drawCup()
{
    Color::White();
    glPushMatrix();
    glTranslated( cup.x, cup.y, cup.z);
    glRotated( cup.rx, 1, 0, 0 );
    glRotated( cup.ry, 0, 1, 0 );
    glRotated( cup.rz, 0, 0, 1 );
    gluCylinder( quad, cup.size*1.4, cup.size, cup.size*2.5, 8, 8);
    glPopMatrix();
}

void drawWater()
{
    Color::Brown();
    glPushMatrix();
    glTranslated( water.x, water.y, water.z);
    glutSolidSphere(water.size, 10, 4);
    glPopMatrix();
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<< displayWire >>>>>>>>>>>>>>>>>>>>>>
void displayRobot()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // clear the screen
    glMatrixMode(GL_MODELVIEW); // position and aim the camera
    glLoadIdentity();
    gluLookAt(eyex, eyey, eyez, lookx, looky, lookz, 0.0, 1.0, 0.0);

    if (displayAxis) drawAxes();
    
    if (robot.wireframe)
    {
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    } else
    {
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    }

    glPushMatrix();
    drawGround();
    drawBase();
    drawShoulder();
    drawUpperarm();
    drawElbow();
    drawForearm();
    drawWrist();
    drawFingers();
    glPopMatrix();

    drawTeapot();
    drawWater();
    drawCup();

    glutSwapBuffers();
}

void myIdle()
{
    mySleep(10);

    if (moveCamera)
    {
        cameraCounter += 0.005;
        eyex = 35*cos(cameraCounter);
        eyez = 55*sin(cameraCounter);
    }


    if (animate && robot.activated)
    {
        cnt += 1;
        if (cnt > animationSmoothness)
        {
            cnt = 0;
            if (frame < frames-2)
            {
                frame += 1;
            } else
            {
                frame = 0;
            }
        }
        t = (cnt*1.0)/animationSmoothness;

        robot.x = lerp( animX[frame], animX[frame+1], t );
        //robot.y = lerp( animY[frame], animY[frame+1], t );
        robot.z = lerp( animZ[frame], animZ[frame+1], t );
        robot.shoulderRotation = lerp( animSR[frame], animSR[frame+1], t );
        robot.shoulderAngle = lerp( animSA[frame], animSA[frame+1], t );
        robot.elbowAngle = lerp( animEA[frame], animEA[frame+1], t );
        robot.wristAngle = lerp( animWA[frame], animWA[frame+1], t );
        robot.fingersAngle = lerp( animFA[frame], animFA[frame+1], t );

        teapot.x = lerp( animTX[frame], animTX[frame+1], t );
        teapot.y = lerp( animTY[frame], animTY[frame+1], t );
        teapot.z = lerp( animTZ[frame], animTZ[frame+1], t );
        teapot.rx = lerp( animTrX[frame], animTrX[frame+1], t );
        teapot.ry = lerp( animTrY[frame], animTrY[frame+1], t );
        teapot.rz = lerp( animTrZ[frame], animTrZ[frame+1], t );

        cup.x = lerp( animCX[frame], animCX[frame+1], t );
        cup.y = lerp( animCY[frame], animCY[frame+1], t );
        cup.z = lerp( animCZ[frame], animCZ[frame+1], t );

        water.x = lerp( animWX[frame], animWX[frame+1], t );
        water.y = lerp( animWY[frame], animWY[frame+1], t );
        water.z = lerp( animWZ[frame], animWZ[frame+1], t );
        water.size = animWS[frame];
    }

    glutPostRedisplay();
}

void myKeyboard(unsigned char key, int x, int y)
{
    switch(key) {
        case 'v':
            view++;
            view %= 3;
            if(view == 0) {
                eyex=25;
                eyey=25;
                eyez=25;
            }
            else if(view == 1) {
                eyex=15;
                eyey=5;
                eyez=65;
            }
            else if(view == 2) {
                eyex=15;
                eyey=65;
                eyez=15;
            }
            break;
        case 'I':
            if ( robot.activated && robot.shoulderAngle < robot.shoulderAngleMax ) robot.shoulderAngle += 5;
            break;
        case 'i':
            if ( robot.activated && robot.shoulderAngle > robot.shoulderAngleMin ) robot.shoulderAngle -= 5;
            break;
        case 'J':
            if ( robot.activated && robot.elbowAngle < robot.elbowAngleMax ) robot.elbowAngle += 5;
            break;
        case 'j':
            if ( robot.activated && robot.elbowAngle > robot.elbowAngleMin ) robot.elbowAngle -= 5;
            break;
        case 'n':
            if ( robot.activated && robot.wristAngle < robot.wristAngleMax ) robot.wristAngle += 5;
            break;
        case 'N':
            if ( robot.activated && robot.wristAngle > robot.wristAngleMin ) robot.wristAngle -= 5;
            break;
        case 'm':
            if ( robot.activated && robot.fingersAngle > robot.fingersAngleMin ) robot.fingersAngle -= 1;
            break;
        case 'M':
            if ( robot.activated && robot.fingersAngle < robot.fingersAngleMax ) robot.fingersAngle += 1;
            break;
        case 'r':
            if (robot.activated) robot.shoulderRotation += 5;
            break;
        case 'R':
            if (robot.activated) robot.shoulderRotation -= 5;
            break;
        case 'o':
            robot.activated = !robot.activated;
            break;
        case 'u':
            robot.wireframe = !robot.wireframe;
            break;
        case 'c':
            displayAxis = !displayAxis;
            break;
        case 'a':
            // animate
            animate = !animate;
            break;
        case 's':
            moveCamera = !moveCamera;
            break;
        case 27:
            // escape
            frame = 0;
            cnt   = 0;

            teapot.Reset();
            cup.Reset();
            water.Reset();
            robot.Reset();

            break;
        case 'q':
        case 'Q':
            std::cout << "Goodbye!" << std::endl;
            exit(0);
            break;
        default:
            break;
    }
    /*
    std::cout << "shoulderRotation " << robot.shoulderRotation << std::endl;
    std::cout << "shoulderAngle " << robot.shoulderAngle << std::endl;
    std::cout << "elbowAngle " << robot.elbowAngle << std::endl;
    std::cout << "wristAngle " << robot.wristAngle << std::endl;
    std::cout << "fingersAngle " << robot.fingersAngle << std::endl;
    */
    glutPostRedisplay();
}

void mySpecialKeyboard(int theKey, int mouseX, int mouseY)
{
    switch(theKey) {
        case GLUT_KEY_UP:
            if (robot.activated) robot.x += 0.1;
            break;
        case GLUT_KEY_DOWN:
            if (robot.activated) robot.x -= 0.1;
            break;
        case GLUT_KEY_LEFT:
            if (robot.activated) robot.z += 0.1;
            break;
        case GLUT_KEY_RIGHT:
            if (robot.activated) robot.z -= 0.1;
            break;
        default:
            break;
    }
    std::cout << "x " << robot.x << " z " << robot.z << std::endl;
    glutPostRedisplay();
}

//<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
    glutInit(&argc, argv);          // initialize the toolkit
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // set display mode
    glutInitWindowSize(screenWidth, screenHeight); // set window size
    glutInitWindowPosition(100, 100); // set window position on screen
    glutCreateWindow("Robot Arm"); // open the screen window


    glutIdleFunc(myIdle);
    myInit();

    glutDisplayFunc(displayRobot);
    glutSpecialFunc(mySpecialKeyboard);
    glutKeyboardFunc(myKeyboard);

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

float lerp(float a, float b, float t)
{
    return a + (b - a) * t;
}
