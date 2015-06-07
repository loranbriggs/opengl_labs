//Robot Game

#include "robotgame.h"


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
    cam.setShape(80.0f, screenWidth/screenHeight, 0.5f, 200.0f);
    //---------------------------
    //
    // set initial variables (called again on reset)

    camBehind = -5.0;
    camAhead = 2.0;
    camLoc = Point3( robot.pos.x + 0 , 3, robot.pos.z + camBehind );
    camLook= Point3( robot.pos.x + 0 , 0, robot.pos.z + camAhead );

    things[0] = Thing("teapot", 0.2, 4.2, 5, 7.2);
    things[1] = Thing("sphere", 0.2, 3.8, 5, 6.8);
    things[2] = Thing("sphere", 0.2, -4.2, 5, 7.2);
    things[3] = Thing("cube", 0.2, -3.8, 5, 6.8);

    table1 = Thing("table", 2, 4, 0, 7);
    table2 = Thing("table", 2, -4, 0, 7);

    robot = Robot();
    baddy1 = Baddy(1, 5, 2, 5);
    baddy2 = Baddy(1, -5, 2, 5);

    //make the initial camera
    cam.set(camLoc, camLook, Vector3(0, 1, 0)); 
    updateCam();
}

//<<<<<<<<<<<<<<<<<<<<<<<< mySpecialKeyboardDown >>>>>>>>>>>>>>>>>>>>>>
void mySpecialKeyboardDown(int theKey, int mouseX, int mouseY)
{
    switch(theKey)
    {
        case GLUT_KEY_LEFT:
            leftPressed = true;
            break;
        case GLUT_KEY_RIGHT:
            rightPressed = true;
            break;
        case GLUT_KEY_UP:
            upPressed = true;
            break;
        case GLUT_KEY_DOWN:
            downPressed = true;
            break;
        default:
            break;
    }
    glutPostRedisplay(); // draw it again
}

//<<<<<<<<<<<<<<<<<<<<<<<< mySpecialKeyboardDown >>>>>>>>>>>>>>>>>>>>>>
void mySpecialKeyboardUp(int theKey, int mouseX, int mouseY)
{
    switch(theKey)
    {
        case GLUT_KEY_LEFT:
            leftPressed = false;
            break;
        case GLUT_KEY_RIGHT:
            rightPressed = false;
            break;
        case GLUT_KEY_UP:
            upPressed = false;
            break;
        case GLUT_KEY_DOWN:
            downPressed = false;
            break;
        default:
            break;
    }
    glutPostRedisplay(); // draw it again
}

//<<<<<<<<<<<<<<<<<<<<<<<< myKeyboardDown >>>>>>>>>>>>>>>>>>>>>>
void myKeyboardDown(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 'w':
            keyPressed['w'] = true;
            break;
        case 's':
            keyPressed['s'] = true;
            break;
        case 'a':
            keyPressed['a'] = true;
            break;
        case 'd':
            keyPressed['d'] = true;
            break;
        case 'v':
            inverseCam = (inverseCam > 0) ? -1 : 1;
            break;
        case 32:
            // spacebar
            if (robot.clawState == OPENED) robot.clawState = CLOSING;
            if (robot.clawState == CLOSED) robot.clawState = OPENING;
            if (robot.clawState == HOLDING) robot.clawState = OPENING;
            break;
        case 27:
            // escape
            myInit();
            break;
        default:
            break;
    }
    glutPostRedisplay(); // draw it again
}

//<<<<<<<<<<<<<<<<<<<<<<<< myKeyboardUp >>>>>>>>>>>>>>>>>>>>>>
void myKeyboardUp(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 'w':
            keyPressed['w'] = false;
            break;
        case 's':
            keyPressed['s'] = false;
            break;
        case 'a':
            keyPressed['a'] = false;
            break;
        case 'd':
            keyPressed['d'] = false;
            break;
        default:
            break;
    }
    glutPostRedisplay(); // draw it again
}

bool blockRobotMove()
{
    robot.updateClawPos();

    // robot base and wall
    if (robot.pos.x + (robot.width/2 + robot.wheelRadius) > gridDim) return true;
    if (robot.pos.x - (robot.width/2 + robot.wheelRadius) < -gridDim) return true;
    if (robot.pos.z + (robot.width/2 + robot.wheelRadius) > gridDim) return true;
    if (robot.pos.z - (robot.width/2 + robot.wheelRadius) < -gridDim) return true;

    // robot claw and wall
    if (robot.clawPos.x + (robot.wristRadius) > gridDim) return true;
    if (robot.clawPos.x - (robot.wristRadius) < -gridDim) return true;
    if (robot.clawPos.z + (robot.wristRadius) > gridDim) return true;
    if (robot.clawPos.z - (robot.wristRadius) < -gridDim) return true;

    // robot base and tables
    if (robot.pos.dist(table1.pos) < table1.size*.75 ) return true;
    if (robot.pos.dist(table2.pos) < table1.size*.75 ) return true;

    // robot claw and tables
    if (robot.clawPos.distInXzPlane(table1.pos) < table1.size*.75
            && robot.clawPos.y < table1.size*.5) return true;
    if (robot.clawPos.distInXzPlane(table2.pos) < table2.size*.75
            && robot.clawPos.y < table1.size*.5) return true;

    return false;

}

bool blockBaddy1Move()
{
    // baddy and table
    if (baddy1.pos.dist(table1.pos) < table1.size) return true;
    if (baddy1.pos.dist(table2.pos) < table1.size) return true;

    // keep above ground
    if (baddy1.pos.y < baddy1.size*1.25)
    {
        baddy1.vel.add( Vector3(0, baddy1.size, 0) );
    }

    // prevent hitting each other
    if (baddy1.health > 0 && baddy2.health > 0)
    {
        if (baddy1.pos.dist(baddy2.pos) < baddy1.size + baddy2.size)
        {
            baddy1.pos.set( VectorPoint3::pointPlusVector(baddy1.pos,Vector3(baddy1.vel.x + 0.5, baddy1.vel.y, baddy1.vel.z ) ) );
        }
    }

    return false;
}

bool blockBaddy2Move()
{
    // baddy and table
    if (baddy2.pos.dist(table1.pos) < table1.size) return true;
    if (baddy2.pos.dist(table2.pos) < table1.size) return true;

    // keep above ground
    if (baddy2.pos.y < baddy2.size*1.25)
    {
        baddy2.vel.add( Vector3(0, baddy2.size, 0) );
    }


    // prevent hitting each other
    if (baddy1.health > 0 && baddy2.health > 0)
    {
        if (baddy2.pos.dist(baddy1.pos) < baddy2.size + baddy1.size)
        {
            baddy2.pos.set( VectorPoint3::pointPlusVector(baddy2.pos,Vector3(baddy2.vel.x - 0.5, baddy2.vel.y, baddy2.vel.z ) ) );
        }
    }

    return false;
}

//<<<<<<<<<<<<<<<<<<<<<<<< myIdle >>>>>>>>>>>>>>>>>>>>>>
void myIdle()
{
    mySleep(100);


    if (leftPressed)
    {
        if (robot.activated && robot.health > 0)
        {
            robot.shoulderRotation += 5;
            if (blockRobotMove())
            {
                robot.shoulderRotation -= 5;
            }
        }
    }

    if (rightPressed)
    {
        if (robot.activated && robot.health > 0)
        {
            robot.shoulderRotation -= 5;
            if (blockRobotMove())
            {
                robot.shoulderRotation += 5;
            }
        }
    }

    if (upPressed)
    {
        if ( robot.activated && robot.health > 0 )
        {
            if (robot.elbowAngle < robot.elbowAngleMax)
            {
                robot.elbowAngle +=5;
                if (blockRobotMove())
                {
                    robot.elbowAngle -=5;
                }
            } else if ( robot.shoulderAngle < robot.shoulderAngleMax )
            {
                robot.shoulderAngle += 5;
                if (blockRobotMove())
                {
                    robot.shoulderAngle -= 5;
                }
            }
        }
    }

    if (downPressed)
    {
        if ( robot.activated && robot.health > 0 )
        {
            if ( robot.shoulderAngle > robot.shoulderAngleMin )
            {
                robot.shoulderAngle -= 5;
                if (blockRobotMove())
                {
                    robot.shoulderAngle += 5;
                }
            } else if (robot.elbowAngle > robot.elbowAngleMin )
            {
                robot.elbowAngle -= 5;
                if (blockRobotMove())
                {
                    robot.elbowAngle += 5;
                }
            }
        }
    }

    if ( keyPressed['w'] )
    {
        if (robot.activated && robot.health > 0)
        {
            robot.pos.z += 0.1;
            if (blockRobotMove())
            {
                robot.pos.z -= 0.1;
            }
        }
    }

    if ( keyPressed['s'] )
    {
        if (robot.activated && robot.health > 0)
        {
            robot.pos.z -= 0.1;
            if (blockRobotMove())
            {
                robot.pos.z += 0.1;
            }
        }
    }

    if ( keyPressed['a'] )
    {
        if (robot.activated && robot.health > 0)
        {
            robot.pos.x += 0.1;
            if (blockRobotMove())
            {
                robot.pos.x -= 0.1;
            }
        }
    }

    if ( keyPressed['d'] )
    {
        if (robot.activated && robot.health > 0)
        {
            robot.pos.x -= 0.1;
            if (blockRobotMove())
            {
                robot.pos.x += 0.1;
            }
        }
    }

    if (robot.clawState == OPENED)
    {
        robot.fingersAngle = robot.fingersAngleMax;
        robot.objectInClaw = -1;
    }

    if (robot.clawState == OPENING)
    {
        if (robot.fingersAngle < robot.fingersAngleMax)
        {
            robot.fingersAngle += 1;
        } else
        {
            robot.clawState = OPENED;
        }

        if (robot.objectInClaw >= 0)
        {
            // drop object
            things[robot.objectInClaw].gravity = true;
            robot.objectInClaw = -1;
        }
    }

    if (robot.clawState == CLOSED)
    {
        robot.clawState == OPENING;
    }

    if (robot.clawState == HOLDING)
    {
        if (robot.fingersAngle > robot.fingersAngleHolding)
        {
            robot.fingersAngle -= 1;
        } else
        {
            robot.fingersAngle = robot.fingersAngleHolding;
        }
    }

    if (robot.clawState == CLOSING)
    {
        if (robot.fingersAngle > robot.fingersAngleMin)
        {
            robot.fingersAngle -= 1;
        } else
        {
            robot.clawState = CLOSED;
        }

        for (int i = 0; i < NUM_THINGS; i++)
        {
            float dist = robot.clawPos.dist( things[i].pos );
            if (dist < 0.3)
            {
                // pickup object
                things[i].gravity = false;
                robot.objectInClaw = i;
                robot.clawState = HOLDING;
                break;
            }
        }
    }

    // handle things position
    for (int i = 0; i < NUM_THINGS; i++)
    {
        if (things[i].gravity)
        {
            // object not being held, fall to ground if not already
            if ( table1.aboveTable(things[i].pos)
                    || table2.aboveTable(things[i].pos) )
            {
                // near table
                if (things[i].pos.y > ( (table1.size*.5) + (things[i].size*.8) ) )
                {
                    // above table
                    things[i].pos.dy(-0.2);
                }
            } else
            {
                // away from table
                if (things[i].pos.y > things[i].size*.8)
                {
                    things[i].pos.dy(-0.2);
                }
            }
        } else
        {
            // in robots claw, match position
            things[i].pos.set(
                    robot.clawPos.x,
                    robot.clawPos.y - things[i].size,
                    robot.clawPos.z);
            things[i].ry = robot.shoulderRotation;
        }
    }

    // move baddys
    if (baddy1.health > 0 && robot.health > 0)
    {
        baddy1.vel.add( Vector3::diffPoints(robot.pos,baddy1.pos) );
        baddy1.vel.normalize();
        baddy1.vel.scale(0.08);
        baddy1.move();
        if (blockBaddy1Move())
        {
            baddy1.unmove();
        }
    }

    if (baddy2.health > 0 && robot.health > 0)
    {
        baddy2.vel.add( Vector3::diffPoints(robot.pos,baddy2.pos) );
        baddy2.vel.normalize();
        baddy2.vel.scale(0.08);
        baddy2.move();
        if (blockBaddy2Move())
        {
            baddy2.unmove();
        }
    }

    // claw hits baddy
    if (baddy1.health > 0 && baddy1.pointWithin(robot.clawPos))
    {
        baddy1.vel.set( -baddy1.vel.x, baddy1.vel.y, -baddy1.vel.z);
        baddy1.vel.normalize();
        baddy1.vel.scale(2.0);
        baddy1.move();
        baddy1.health -= 1;
        baddy1.damageFlash = 5;
    }

    if (baddy2.health > 0 && baddy2.pointWithin(robot.clawPos))
    {
        baddy2.vel.set( -baddy2.vel.x, baddy2.vel.y, -baddy2.vel.z);
        baddy2.vel.normalize();
        baddy2.vel.scale(2.0);
        baddy2.move();
        baddy2.health -= 1;
        baddy2.damageFlash = 5;
    }

    // baddy hits robot
    if (baddy1.health > 0 && baddy1.pos.dist(robot.pos) < baddy1.size + robot.width )
    {
        baddy1.vel.set( -baddy1.vel.x, baddy1.vel.y, -baddy1.vel.z);
        baddy1.vel.normalize();
        baddy1.vel.scale(2.0);
        baddy1.move();
        robot.health -= 1;
        damageFlash = true;
    }

    if (baddy2.health > 0 && baddy2.pos.dist(robot.pos) < baddy2.size + robot.width )
    {
        baddy2.vel.set( -baddy2.vel.x, baddy2.vel.y, -baddy2.vel.z);
        baddy2.vel.normalize();
        baddy2.vel.scale(2.0);
        baddy2.move();
        robot.health -= 1;
        damageFlash = true;
    }

    // check win
    if ( table1.aboveTable(things[2].pos)
                    && table1.aboveTable(things[3].pos) )
    {
        table1Flash = true;
    }

    if ( table2.aboveTable(things[0].pos)
                    && table2.aboveTable(things[1].pos) )
    {
        table2Flash = true;
    }
    flashOn = !flashOn;

    updateCam();
    glutPostRedisplay();
}

void drawLighting()
{
    glLightfv(GL_LIGHT0, GL_POSITION, lightingPosition);
}

//<<<<<<<<<<<<<<<<<<<<<<< drawGrid  >>>>>>>>>>>>>>>>>>>>>>>>>>
void drawGrid()
{
    // draw floor
    for (int i = -gridDim; i < gridDim; i++)
    {
        if (i % 10 == 0)
        {
            glLineWidth(3);
            Material::Ruby();
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
            Material::Turquoise();
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

    // walls
    glLineWidth(1);
    Material::Ruby();
    for (int i = 0; i < 10; i++)
    {
        glBegin(GL_LINES);
            glVertex3f(-gridDim, (i*1.0)/2, -gridDim);
            glVertex3f(-gridDim, (i*1.0)/2, gridDim);

            glVertex3f(-gridDim, (i*1.0)/2, gridDim);
            glVertex3f(gridDim, (i*1.0)/2, gridDim);

            glVertex3f(gridDim, (i*1.0)/2, gridDim);
            glVertex3f(gridDim, (i*1.0)/2, -gridDim);

            glVertex3f(gridDim, (i*1.0)/2, -gridDim);
            glVertex3f(-gridDim, (i*1.0)/2, -gridDim);
        glEnd();
    }
}

//<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>>>>>>>>>>
void myDisplay(void)
{
    if (damageFlash)
    {
        glClearColor(1.0f, 0.0f, 0.0f, 0.0f);  // background is black
        damageFlash = false;
    } else
    {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);  // background is black
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    cam.set(camLoc, camLook, Vector3(0, 1, 0));

    drawLighting();
    glEnable(GL_LIGHT0);

    Material::Gold();
    things[0].draw();
    things[1].draw();
    Material::Silver();
    things[2].draw();
    things[3].draw();

    if (table1Flash && flashOn)
    {
        Material::Ruby();
    } else {
        Material::Silver();
    }
    table1.draw();
    if (table2Flash && flashOn)
    {
        Material::Ruby();
    } else {
        Material::Gold();
    }
    table2.draw();

    if (baddy1.health > 0) baddy1.draw();
    if (baddy2.health > 0) baddy2.draw();

    if (robot.health  > 0) robot.draw();


    glDisable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    drawGrid();
    glDisable(GL_LIGHT1);

    glutSwapBuffers();
}


//<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
    glutInit(&argc, argv);          // initialize the toolkit
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // set display mode
    glutInitWindowSize(screenWidth, screenHeight); // set window size
    glutInitWindowPosition(100, 100); // set window position on screen
    glutCreateWindow("Robot Game"); // open the screen window

    // register callback functions
    glutIdleFunc(myIdle);
    glutKeyboardFunc(myKeyboardDown);
    glutKeyboardUpFunc(myKeyboardUp);
    glutSpecialFunc(mySpecialKeyboardDown);
    glutSpecialUpFunc(mySpecialKeyboardUp);
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

void updateCam()
{
    camLoc = Point3( robot.pos.x + camBehind*sin( inverseCam*(PI/180)*robot.shoulderRotation) , 3, robot.pos.z + camBehind*cos( (PI/180)*robot.shoulderRotation) );
    camLook= Point3( robot.pos.x + camAhead*sin( inverseCam*(PI/180)*robot.shoulderRotation) , 0, robot.pos.z + camAhead*cos( (PI/180)*robot.shoulderRotation) );

    lightingPosition[0] = camLoc.x;
    lightingPosition[1] = camLoc.y;
    lightingPosition[2] = camLoc.z;
}
