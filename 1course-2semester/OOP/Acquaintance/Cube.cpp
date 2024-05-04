#include "Cube.h"
#include <math.h>

double Cube::calcVolume()
{
	return pow(lenght, 3);
}

double Cube::calcSurface()
{
	return (pow(lenght, 2) * 6);
}

double Cube::getLenght()
{
	return lenght;
}

void Cube::setLength(double len)
{
	lenght = len;
}
