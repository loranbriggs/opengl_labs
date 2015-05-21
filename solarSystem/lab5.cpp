#include "lab5.h"

void myInit(int shadingChoice, int colorChoice)
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);

    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);

    if(shadingChoice == 0) {
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    }
    else if(shadingChoice == 1) {
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

    }

    if(colorChoice == 1) {
        glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
        glEnable(GL_COLOR_MATERIAL);
    }


    glClearColor(1.0f, 1.0f, 1.0f,0.0f);  // background is white

    glMatrixMode(GL_PROJECTION); // set the view volume shape
    glLoadIdentity();
    glOrtho(-3.5*worldWidth/worldHeight, 3.5*worldWidth/worldHeight, -3.5, 3.5, 0.1, 100);
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
    glBegin(GL_LINES);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0,0,0);
        glVertex3f(0,0,100);
    glEnd();
    glPushMatrix();
        glTranslatef(0, -0.5, 4);
        glScalef(0.01, 0.01, 0.01);
        glutStrokeCharacter(GLUT_STROKE_ROMAN, 'z');
    glPopMatrix();

}

void drawSun()
{
    // Sun
    glColor3f(1.0f, 0.5f, 0.0f);            // sun is orange
    glPushMatrix();
    glRotated(sunRotateScale, 0, 1, 0);     // spin abouts its axis
    glutSolidSphere(0.5, 20, 16);           // locate the sun at the origin
    glPopMatrix();
}

void drawMercury()
{
    // Mercury
    glColor3f(1.0f, 1.0f, 0.0f);            // mercury is yellow 
    glPushMatrix();
    glRotated(mercuryOrbitScale, 0, 1, 0);  //rotate about sun
    glTranslated(0,0,mercuryAxis);          // move out from sun
    glRotated(mercuryRotateScale, 0, 1, 0); // spin abouts its axis
    glutSolidSphere(0.08, 10, 4);           // create sphere radius 0.08
    glPopMatrix();
}

void drawVenus()
{
    // Venus
    glColor3f(0.8f, 0.3f, 0.0f);            // venus is dark orange
    glPushMatrix();
    glRotated(venusOrbitScale, 0, 1, 0);    //rotate about sun
    glTranslated(0,0,venusAxis);            // move out from sun
    glRotated(venusRotateScale, 0, 1, 0);   // spin abouts its axis
    glutSolidSphere(0.15, 10, 4);           // create sphere radius 0.15
    glPopMatrix();
}

void drawEarthOrbit()
{
    glLineWidth(2);
    glColor3f(0.0f, 1.0f, 0.0f);            // earth is green
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < RESOLUTION; i += 1)
    {
        float t = i*1.0/RESOLUTION;
        glVertex3f(
                earthMinorAxis * cos(2*PI*t),
                0,
                earthMajorAxis * sin(2*PI*t)
        );
    }
    glEnd();
}

void drawEarthAndMoon()
{
    // Earth
    glColor3f(0.0f, 1.0f, 0.0f);            // earth is green
    glPushMatrix();
    glRotated(earthOrbitScale, 0, 1, 0);    //rotate about sun

    glTranslated(0,0,earthRadius);          // move out from sun 2 units

    glRotated(earthRotateScale, 0, 1, 0);   //rotate about axis
    glutSolidSphere(0.2, 10, 4);            // create sphere radius 0.2
    glPopMatrix();

    // Moon
    glColor3f(0.5f, 0.5f, 0.5f);
    glPushMatrix();
    glRotated(earthOrbitScale, 0, 1, 0);    // rotate about sun w/ earth
    glTranslated(0,0,earthRadius);                    // move out from sun w/ earth
    glRotated(moonOrbitScale, 0, 1, 0);     // rotate about earth
    glTranslated(0,0,0.3);                  // move out from earth
    glRotated(moonRotateScale, 0, 1, 0);    // rotate about axis
    glutSolidSphere(0.05, 5, 4);            // radius 0.05
    glPopMatrix();
}

void drawMars()
{
    // Mars
    glColor3f(1.0f, 0.0f, 0.0f);
    glPushMatrix();
    glRotated(marsOrbitScale, 0, 1, 0);     //rotate about sun
    glTranslated(0,0,marsAxis);             // move out from sun
    glRotated(marsRotateScale, 0, 1, 0);    //rotate about axis
    glutSolidSphere(0.15, 10, 4);           // radius 0.15
    glPopMatrix();
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<< displayWire >>>>>>>>>>>>>>>>>>>>>>
void displaySolarSystem()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // clear the screen
    glMatrixMode(GL_MODELVIEW); // position and aim the camera
    glLoadIdentity();
    gluLookAt(eyex, eyey, eyez, lookx, looky, lookz, 0.0, 1.0, 0.0);

    drawAxes();
    drawSun();
    drawMercury();
    drawVenus();
    drawEarthOrbit();
    drawEarthAndMoon();
    drawMars();

    glutSwapBuffers();
}

void myIdle()
{
    mySleep(1);
    scale += 100.0;
    sunRotateScale = scale / 25;
    mercuryRotateScale = scale / 58;
    venusRotateScale = scale / 243;
    earthRotateScale = scale;
    moonRotateScale = scale / 27;
    marsRotateScale = scale;
    mercuryOrbitScale = scale / 88;
    venusOrbitScale = scale / 224;
    earthOrbitScale = scale / 365;
    moonOrbitScale = scale / 27;
    marsOrbitScale = scale / 687;

    earthX = earthMinorAxis * cos(earthOrbitScale * PI / 180.0);
    earthZ = earthMajorAxis * sin(earthOrbitScale * PI / 180.0);
    earthRadius = (earthMajorAxis*earthMinorAxis) /
        ( sqrt( pow(earthX,2) + pow(earthZ,2) ) );

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
                eyex=25;
                eyey=0;
                eyez=0;
            }
            else if(view == 2) {
                eyex=0;
                eyey=25;
                eyez=25;
            }
            break;
        default:
            break;
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
    glutCreateWindow("Inner Solar System"); // open the screen window


    int shadingChoice=1;
    int colorChoice = 1;
    std::cout << "Enter Shading Choice (0 for Diffuse, 1 for Specular):\n" ;
    std::cin >> shadingChoice;

    std::cout << "Enter Color Option (0 for No Color, 1 for Color):\n" ;
    std::cin >> colorChoice;

    glutIdleFunc(myIdle);
    myInit(shadingChoice, colorChoice);

    glutDisplayFunc(displaySolarSystem);
    glutKeyboardFunc(myKeyboard);

    glutMainLoop();

    return( 0 );
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
