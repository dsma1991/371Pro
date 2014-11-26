#pragma once
#include "Model.h"
class Robot :
	public Model
{
public:
	Robot(void);
	~Robot(void);

	Robot(double startX, double startZ, double startY = -56);



	void draw();
	bool idle();

	void moveTo(double destX, double destZ);

	ModelLoader robotModel;

	

protected:
	
	
};