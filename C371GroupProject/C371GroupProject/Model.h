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
	void moveTo(double destX, double destY, double destZ);

	enum State
	{
		Idle,
		Moving,
		Dying,
	};


private:
	//world coordinates of the model
	double x, y, z;
	//how close can the model be for it to be considered at destination when using moveTo
	double distanceTolerance;
	//world orientation of the model, as a quaternion
	Quaternion<double> orientation, initialOrientation;
	//Forward vector of model
	Vector3d forward;
	//rotation and movement speed
	double rotationSpeed, movementSpeed;
	//used for rotating to destination
	double t;

	State currentState;

	//model variable however it's done

	bool lightAvailability[4]; // true if that light available, false otherwise -- if needed
};

