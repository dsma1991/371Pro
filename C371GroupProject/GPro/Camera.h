#pragma once
#include "includeHeader.h"
#include "Model.h"

#define DEFAULT_CAMERA_MOVEMENT_SPEED 5
#define DEFAULT_CAMERA_ROTATION_SPEED 5
#define DEFAULT_CAMERA_DISTANCE_TOLERANCE_FACTOR 1

class Camera
{
public:
	Camera(void);
	Camera(double initialEyeX, double initialEyeY, double initialEyeZ, 
		double initialLookAtX, double initialLookAtY, double initialLookAtZ,
		double initialUpX = 0, double initialUpY = 1, double initialUpZ = 0);
	~Camera(void);

	enum CameraMode
	{
		Pan,
		Rotate,
	};

	enum Movement
	{
		Snap,
		Smooth,
	};


	enum State
	{
		Idle,
		Moving, //moving eye coordinates
		Rotating, //moving only lookAt coordinates
	};

	// move camera to destination coordinates using the mode and move type specified
	void cameraTo(double x, double y, double z, CameraMode mode, Movement moveType); 

	 //Calls gluLookAt
	void displayCamera();

	//determines camera's behaviour according to its class variables
	void idle();

	//looks at a point using the move type specified
	void lookAt(double x, double y, double z, Movement moveType);

	//set a model to continuously look at
	void lookAt(Model* modelToLook);

	State getState();

private:
	double eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, upX, upY, upZ;
	double destX, destY, destZ, destLookAtX, destLookAtY, destLookAtZ;

	//rotation and movement speed
	double rotationSpeed, movementSpeed;

	//used for rotating to destination
	State currentState;
	CameraMode cameraMode;
	Movement movementType;

	//how close can the camera be for it to be considered at destination when using moveTo
	double distanceTolerance;

	//model to look at
	Model* model; 

	//helper methods to perform correct movements
	void snapPanCameraTo();
	void snapRotateCameraTo();
	void movePanCameraTo();
	void moveRotateCameraTo();
	void moving();
	void rotating();
	void snapLookAt();
};

