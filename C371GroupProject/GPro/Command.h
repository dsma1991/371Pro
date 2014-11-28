#pragma once
#include "includeHeader.h"
#include "Robot.h"
#include "Camera.h"
class Command
{
public:

	enum CommandType
	{
		CameraMovePanSnap,
		CameraMovePanSmooth,
		CameraMoveRotateSnap,
		CameraMoveRotateSmooth,
		ModelMove,
		ModelFire,
		CameraFollow,
		CameraLookAtSnap,
		CameraLookAtSmooth,
	};

	Command(void);
	~Command(void);

	//moves robot to a position
	Command(Robot* commandingRobot, CommandType type, int repeatNumber, double destX, double destY, double destZ);

	//moves camera to a position using the given command type
	Command(Camera* commandingCamera, CommandType type, int repeatNumber, double destX, double destY, double destZ);

	//moves camera to follow a model
	Command(Camera* commandingCamera, CommandType type, int repeatNumber, Model* modelToFollow);

	//performs the command, returns true if the command is to be repeated
	bool execute();

private:
	double x, y, z;
	int repeatingNumber;
	CommandType commandType;
	Robot* robot;
	Model* followingModel;
	Camera* camera;
};

