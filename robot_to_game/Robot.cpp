#include "Robot.h"

Robot::Robot()
{
        // dimensions
        width               =   1.3;
        x                   =     0;
        y                   =     0;
        z                   =     0;
        scaleX              =   1.5;
        scaleY              =   0.2;
        scaleZ              =     1;
        wheelRadius         =   0.3;
        shoulderRadius      = width*0.3;
        upperarmLength      = width*1.7;
        upperarmRadius      = shoulderRadius*0.4;
        elbowRadius         = shoulderRadius*0.8;
        forearmLength       = upperarmLength*0.8;
        forearmRadius       = elbowRadius*0.4;
        wristRadius         = elbowRadius*0.8;
        fingersLength       = forearmLength*0.4;
        fingersRadius       = forearmRadius*0.4;

        // Angles
        shoulderRotation    =   0;
        shoulderAngle       =  60;
        elbowAngle          = -25;
        wristAngle          =  35;
        fingersAngle        =  35;

        // min / max angles
        shoulderAngleMax    = 155;
        shoulderAngleMin    =  45;
        elbowAngleMax       =  85;
        elbowAngleMin       = -85;
        wristAngleMax       =  65;
        wristAngleMin       =  -5;
        fingersAngleMax     =  40;
        fingersAngleMin     =  25;

        // other
        numberOfFingers     = 5;
        activated           = true;
        quadric = gluNewQuadric();

}

void Robot::Reset()
{
    x                   =     0;
    y                   =     0;
    z                   =     0;
    shoulderRotation    =   0;
    shoulderAngle       =  60;
    elbowAngle          = -25;
    wristAngle          =  35;
    fingersAngle        =  35;

    activated           = true;
}

void Robot::drawWheels()
{
    Color::Black();
    for (int i = 0; i < 4; i++)
    {
        glPushMatrix();
        switch (i)
        {
            case 0:
                glTranslated( baseRadius(), 0, baseRadius() );
                break;
            case 1:
                glTranslated( baseRadius(), 0, -baseRadius() );
                break;
            case 2:
                glTranslated( -baseRadius(), 0, baseRadius() );
                break;
            case 3:
                glTranslated( -baseRadius(), 0, -baseRadius() );
                break;
        }
        glRotated( -x*80, 0, 0, 1);             // spin wheel
        glRotated( -z*80, 1, 0, 0);             // spin wheel
        glutSolidSphere( wheelRadius, 4, 4);
        glPopMatrix();
    }
}

void Robot::drawBase()
{
    Color::dkBlue();
    glTranslated(x,0,z);
    glPushMatrix();
    glScaled( scaleX, scaleY, scaleZ);
    glutSolidCube(width);
    glPopMatrix();
    drawWheels();
}

void Robot::drawShoulder()
{
    if (activated)
    {
        Color::Red();
    } else
    {
        Color::dkGray();
    }
    glTranslated(0,width/4,0);
    glRotated(shoulderRotation, 0, 1, 0);
    glRotated(-shoulderAngle, 1, 0, 0);
    glutSolidSphere(shoulderRadius, 10, 4);
}

void Robot::drawUpperarm()
{
    Color::dkBlue();
    gluCylinder(quadric, upperarmRadius, upperarmRadius, upperarmLength, 16, 16);
}

void Robot::drawElbow()
{
    if (activated)
    {
        Color::Red();
    } else
    {
        Color::dkGray();
    }
    glTranslated(0,0,upperarmLength);
    glRotated(-elbowAngle, 1, 0, 0);
    glutSolidSphere(elbowRadius, 10, 4);
}

void Robot::drawForearm()
{
    Color::dkBlue();
    gluCylinder(quadric, forearmRadius, forearmRadius, forearmLength, 8, 8);
}

void Robot::drawWrist()
{
    if (activated)
    {
        Color::Red();
    } else
    {
        Color::dkGray();
    }
    glTranslated(0,0,forearmLength);
    glRotated(-wristAngle, 1, 0, 0);
    glutSolidSphere(wristRadius, 10, 4);
}

void Robot::drawFingers()
{
    if (activated)
    {
        Color::dkPink();
    } else
    {
        Color::dkGray();
    }

    for (int f = 0; f < numberOfFingers; f++)
    {
        glPushMatrix();
        glRotated( (360.0/numberOfFingers)*f, 0, 1, 0);
        glRotated(fingersAngle*4, 1, 0, 0);
        gluCylinder(quadric, fingersRadius, fingersRadius, fingersLength, 4, 4);
        glPopMatrix();
    }

}

void Robot::draw()
{
    glPushMatrix();
    Robot::drawBase();
    Robot::drawShoulder();
    Robot::drawUpperarm();
    Robot::drawElbow();
    Robot::drawForearm();
    Robot::drawWrist();
    Robot::drawFingers();
    glPopMatrix();
}
