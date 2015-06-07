#include "Robot.h"

Robot::Robot()
{
        // dimensions
        width               =   1.0;
        length               =  1.0;
        height               =  0.5;
        wheelRadius         = width*.25;
        pos.set(0,0,0);
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
        shoulderAngleMin    =  35;
        elbowAngleMax       = -15;
        elbowAngleMin       = -85;
        wristAngleMax       =  65;
        wristAngleMin       =  -5;
        fingersAngleMax     =  40;
        fingersAngleMin     =  25;
        fingersAngleHolding =  31;

        // other
        numberOfFingers     = 5;
        activated           = true;
        quadric = gluNewQuadric();
        objectInClaw        = -1;
        clawState           = OPENED;
        health              = 10;
}

void Robot::Reset()
{
    pos.set(0,0,0);
    shoulderAngle       =  60;
    elbowAngle          = -25;
    wristAngle          =  35;
    fingersAngle        =  35;

    activated           = true;
}

void Robot::drawWheels()
{
    Material::Obsidian();
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
        glRotated( -pos.x*80, 0, 0, 1);             // spin wheel
        glRotated( pos.z*80, 1, 0, 0);             // spin wheel
        glutSolidSphere( wheelRadius, 4, 4);
        glPopMatrix();
    }
}

void Robot::drawBase()
{
    Material::Turquoise();
    glTranslated(pos.x,height/2,pos.z);
    glPushMatrix();
    glScaled( length/width , height/width, 1);
    glutSolidCube(width);
    glPopMatrix();
    drawWheels();
}

void Robot::drawShoulder()
{
    if (activated)
    {
        Material::Ruby();
    } else
    {
        Material::Silver();
    }
    glTranslated(0,height/2,0);
    glRotated(shoulderRotation, 0, 1, 0);
    glRotated(-shoulderAngle, 1, 0, 0);
    glutSolidSphere(shoulderRadius, 10, 4);
}

void Robot::drawUpperarm()
{
    Material::Turquoise();
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glLineWidth(0.75);
    gluCylinder(quadric, upperarmRadius, upperarmRadius, upperarmLength, 8, 8);
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}

void Robot::drawElbow()
{
    if (activated)
    {
        Material::Ruby();
    } else
    {
        Material::Silver();
    }
    glTranslated(0,0,upperarmLength);
    glRotated(-elbowAngle, 1, 0, 0);
    glutSolidSphere(elbowRadius, 10, 4);
}

void Robot::drawForearm()
{
    Material::Turquoise();
    gluCylinder(quadric, forearmRadius, forearmRadius, forearmLength, 8, 8);
}

void Robot::drawWrist()
{
    if (activated)
    {
        Material::Ruby();
    } else
    {
        Material::Silver();
    }
    glTranslated(0,0,forearmLength);
    glRotated(-wristAngle, 1, 0, 0);
    glutSolidSphere(wristRadius, 10, 4);
}

void Robot::drawFingers()
{
    if (activated)
    {
        Material::Ruby();
    } else
    {
        Material::Silver();
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

void Robot::updateClawPos()
{

    elbowPos.set(
            // x elbow
            pos.x + upperarmLength*sin( RADS*(90-shoulderAngle) )*sin( RADS*shoulderRotation),
            // y elbow
            height + upperarmLength*cos( RADS*(90-shoulderAngle) ),
            // z elbow
            pos.z + upperarmLength*sin( RADS*(90-shoulderAngle) )*cos( RADS*shoulderRotation)
            );

    clawPos.set(
            // x wrist
            elbowPos.x + forearmLength*sin( RADS*(90 - shoulderAngle - elbowAngle ) )*sin( RADS*shoulderRotation),
            // y wrist
            elbowPos.y + forearmLength*cos( RADS*(90 - shoulderAngle - elbowAngle) ),
            // z wrist
            elbowPos.z + forearmLength*sin( RADS*(90 - shoulderAngle - elbowAngle) )*cos( RADS*shoulderRotation)
            );
}
