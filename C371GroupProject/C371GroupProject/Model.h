#pragma once
#include "includeHeader.h"

using namespace Eigen;

class Model
{
public:
	Model(void);
	Model(double startX, double startY, double startZ);
	~Model(void);
	void draw();
	void idle();
	void moveTo();

	enum State
	{
		Idle,
		Moving,
		Dying,
	};


private:
	double x, y, z;
	Quaternion<double> orientation;
	State currentState;

	//model variable however it's done

	bool lightAvailability[4]; // true if that light available, false otherwise -- if needed
};

