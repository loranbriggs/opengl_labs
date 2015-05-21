#include <iostream>
#include "cube.h"

using namespace std;

Cube::Cube()
{
}

Cube::~Cube()
{
}

void Cube::setSide(double s)
{
	Side = s <= 0 ? 1 : s;
}

double Cube::getSide()
{
	return Side;
}

double Cube::Area()
{
	return 6 * Side * Side;
}

double Cube::Volume()
{
	return Side * Side * Side;
}

void Cube::Properties()
{
	cout << "Characteristics of this cube";
	cout << "\nSide   = " << getSide();
	cout << "\nArea   = " << Area();
	cout << "\nVolume = " << Volume() << "\n\n";
}