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
        wireframe           = false;

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
    wireframe           = false;
}
