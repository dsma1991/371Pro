#pragma once
#include "Model.h"
class Robot :
	public Model
{
public:
	Robot(void);
	~Robot(void);

	//Constructor also loads in the correct model
	//y coordinate is set to the "ground"
	Robot(double startX, double startZ, double startY = -56);

	//draws the correct model
	void draw();

	//determines robot's behaviour according to its class variables
	bool idle();

	//moves to given coordinates
	void moveTo(double destX, double destZ);

	ModelLoader robotModel;
};