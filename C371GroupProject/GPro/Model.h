#pragma once
#include "includeHeader.h"
#include "ModelLoader.h"

#define DEFAULT_MODEL_MOVEMENT_SPEED 40
#define DEFAULT_MODEL_ROTATION_SPEED 2
#define DEFAULT_MODEL_DISTANCE_TOLERANCE_FACTOR 0.1

class Model
{
public:
	Model(void);
	Model(double startX, double startY, double startZ);
	~Model(void);
	void virtual draw();
	bool virtual idle();
	bool checkCollision(double collisionX, double collisionY, double collisionZ);
	void virtual moveTo(double destX, double destY, double destZ);
	Vector3d getCoordinates();

	//void virtual fire();

	enum State
	{
		Idle,
		Moving,
		Dying,
	};


	State getState();


protected:
	//world coordinates of the model
	double x, y, z;
	//destination coordinates
	double moveToX, moveToY, moveToZ;
	//how close can the model be for it to be considered at destination when using moveTo
	double distanceTolerance;
	//Forward vector of model
	Vector3d forward, modelLookAt;
	//rotation and movement speed
	double rotationSpeed, movementSpeed;
	//angle of model on the y-axis
	double angle, angleBetween, traversedAngle;

	State currentState;
	//std::vector<Model> missiles;
	//bool lightAvailability[4]; // true if that light available, false otherwise -- if needed

	void moving();
};

