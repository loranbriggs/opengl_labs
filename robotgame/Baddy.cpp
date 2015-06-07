#include "Baddy.h"

Baddy::Baddy()
{
}

Baddy::Baddy(GLdouble dsize,
        GLdouble dx, GLdouble dy, GLdouble dz)
{
        // dimensions
        size                =  dsize;
        pos.set( dx, dy, dz );
        vel = Vector3();
        health = 2;
        quadric = gluNewQuadric();
}

void Baddy::draw()
{
    glPushMatrix();
    // move whole object based on location
    glTranslated( pos.x, pos.y, pos.z);
    //glRotated( facing.x, 1, 0, 0 );
    GLdouble theta = DEGS*atan2(vel.x,vel.z);
    theta = theta+360 % 360;
    glRotated( theta, 0, 1, 0 );
    //glRotated( facing.z, 0, 0, 1 );

    glPushMatrix();
        glTranslated( 0, 0, size*.2);
        Material::Obsidian();
        glutSolidSphere(size*.9, 20, 20);
    glPopMatrix();
    if (damageFlash > 0 && damageFlash % 2 == 1)
    {
        Material::Pearl();
        damageFlash -= 1;
    } else
    {
        Material::Ruby();
    }
    glutSolidSphere(size, 20, 20);

    glPopMatrix();
}

void Baddy::move()
{
    pos.set( VectorPoint3::pointPlusVector(pos,vel) );
}

void Baddy::unmove()
{
    vel.set( -vel.x, vel.y, -vel.z);
    pos.set( VectorPoint3::pointPlusVector(pos,vel) );
}

bool Baddy::pointWithin(Point3 p)
{
    if (pos.dist(p) < size)
    {
        return true;
    } else
    {
        return false;
    }
}
