#pragma once

class Cube
{
public:
	double calcVolume();
	double calcSurface();
	double getLenght();
	void setLength(double len);

private:
	double lenght;
};

