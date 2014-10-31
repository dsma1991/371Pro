#pragma once
#include "model.h"
class Plane :
	public Model
{
public:
	Plane(void);
	~Plane(void);

	void fire();


private:
	//vector<Missiles> missilesShot; //vector containing the missiles shot
};

