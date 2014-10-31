#pragma once
#include "model.h"
class Robot :
	public Model
{
public:
	Robot(void);
	~Robot(void);

	void fire();



private:
	//vector<Laser> lasersShot; 
};

