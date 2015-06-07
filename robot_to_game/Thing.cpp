#include "Thing.h"

Thing::Thing(std::string dtype, GLdouble dsize,
        GLdouble dx, GLdouble dy, GLdouble dz,
        GLdouble drx, GLdouble dry, GLdouble drz)
{
        // dimensions
        size                =  dsize;
        x                   =     dx;
        y                   =     dy;
        z                   =     dz;
        rx                  =    drx;
        ry                  =    dry;
        rz                  =    drz;
        type                =  dtype;
        quadric = gluNewQuadric();
}

void Thing::draw()
{
    glPushMatrix();
    glTranslated( x, y, z);
    glRotated( rx, 1, 0, 0 );
    glRotated( ry, 0, 1, 0 );
    glRotated( rz, 0, 0, 1 );
    if (type == "teapot")
    {
        glutSolidTeapot(size);
    } else if (type == "cylinder")
    {
        gluCylinder( quadric, size, size, size, 8, 8);
    } else {
        glutSolidSphere(size, 20, 20);
    }
    glPopMatrix();
}
