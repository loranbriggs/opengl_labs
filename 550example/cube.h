#ifndef CUBE_H
#define CUBE_H

class Cube
{
public:
	Cube();
	~Cube();
	void setSide(double s);
	double getSide();
	double Area();
	double Volume();
	void Properties();
private:
	double Side;
};

#endif