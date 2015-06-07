#include "Thing.h"

Thing::Thing()
{

}

Thing::Thing(std::string dtype, GLdouble dsize,
        GLdouble dx, GLdouble dy, GLdouble dz)
{
        // dimensions
        size                =  dsize;
        pos.set( dx, dy, dz );
        rx                  =    0;
        ry                  =    0;
        rz                  =    0;
        type                =  dtype;
        gravity             = true;
        quadric = gluNewQuadric();
}

void Thing::draw()
{
    glPushMatrix();
    // move whole object based on location
    glTranslated( pos.x, pos.y, pos.z);
    glRotated( rx, 1, 0, 0 );
    glRotated( ry, 0, 1, 0 );
    glRotated( rz, 0, 0, 1 );
    // draw type of object
    if (type == "teapot")
    {
        glutSolidTeapot(size);
    } else if (type == "cylinder")
    {
        gluCylinder( quadric, size, size, size, 8, 8);
    } else if (type == "cube")
    {
        glPushMatrix();
        glutSolidCube(size);
        glPopMatrix();
    } else if (type == "table")
    {
        glPushMatrix();
        // leg1
        glTranslated(size/3, size/3, 0);
        glRotated( 90, 1, 0, 0 );
        gluCylinder( quadric, size/15, size/15, size/3, 8, 8);
        glPopMatrix();

        // leg2
        glPushMatrix();
        glTranslated(-size/3, size/3, 0);
        glRotated( 90, 1, 0, 0 );
        gluCylinder( quadric, size/15, size/15, size/3, 8, 8);
        glPopMatrix();

        // table top
        glPushMatrix();
        glTranslated(0,size/3,0);
        glScaled( 1 , size/20, 1);
        glutSolidCube(size);
        glPopMatrix();
    } else {
        glutSolidSphere(size, 20, 20);
    }
    glPopMatrix();
}

bool Thing::aboveTable(Point3 center)
{
    return (center.x < (pos.x + size))
        && (center.x > (pos.x - size))
        && (center.z < (pos.z + size/2))
        && (center.z > (pos.z - size/2));
}
