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
	Command(Robot* commandingRobot, CommandType type, int repeatNumber, double destX, double destY, double destZ);
	Command(Camera* commandingCamera, CommandType type, int repeatNumber, double destX, double destY, double destZ);
	Command(Camera* commandingCamera, CommandType type, int repeatNumber, Model* modelToFollow);

	bool execute();

private:
	double x, y, z;
	int repeatingNumber;
	CommandType commandType;
	Robot* robot;
	Model* followingModel;
	Camera* camera;
};

