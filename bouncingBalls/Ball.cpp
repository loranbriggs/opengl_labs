#include <iostream>
#include "Ball.h"

using namespace std;

Ball::Ball()
{
    radius = 8;
    center.x = 0;
    center.y = 0;
    velocity.x = 1;
    velocity.y = 1;
    freeze = false;
    filled = true;
}

Ball::Ball(float r, float x, float y)
{
    radius = r;
    center.x = x;
    center.y = y;
    velocity.x = 1;
    velocity.y = 1;
    freeze = false;
    filled = true;
}

Ball::Ball(float r, float x, float y, float dx, float dy)
{
    radius = r;
    center.x = x;
    center.y = y;
    velocity.x = dx;
    velocity.y = dy;
    freeze = false;
    filled = true;
}

Ball::~Ball()
{
}

float Ball::Area()
{
	return 4 * PI * radius * radius;
}

float Ball::Volume()
{
	return (4.0/3) * PI * radius * radius * radius;
}

void Ball::Properties()
{
	cout << "Characteristics of this ball";
	cout << "\nRadius   = " << radius;
	cout << "\nArea   = " << Area();
	cout << "\nVolume = " << Volume() << "\n\n";
}
