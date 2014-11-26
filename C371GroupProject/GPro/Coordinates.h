#pragma once

class Coordinates
{
public:
	Coordinates()
	{
		x=0;
		y=0;
		z=0;
	}
	Coordinates(double startX, double startY, double startZ)
	{
		x = startX;
		y = startY;
		z = startZ;
	}
	double x;
	double y;
	double z;
};