#include "Command.h"


Command::Command(void)
{
}


Command::~Command(void)
{
}

//moves robot to a position
Command::Command(Robot* commandingRobot, CommandType type, int repeatNumber, double destX, double destY, double destZ){
	robot = commandingRobot;
	camera = NULL;
	commandType = type;
	repeatingNumber = repeatNumber;
	x = destX; 
	y = destY;
	z = destZ;
	followingModel = NULL;
}

//moves camera to a position using the given command type
Command::Command(Camera* commandingCamera, CommandType type, int repeatNumber, double destX, double destY, double destZ){
	robot = NULL;
	camera = commandingCamera;
	commandType = type;
	repeatingNumber = repeatNumber;
	x = destX; 
	y = destY;
	z = destZ;
	followingModel = NULL;
}

//moves camera to follow a model
Command::Command(Camera* commandingCamera, CommandType type, int repeatNumber, Model* modelToFollow){
	robot = NULL;
	camera = commandingCamera;
	followingModel = modelToFollow;
	commandType = type;
	repeatingNumber = repeatNumber;
	x = 0; 
	y = 0;
	z = 0;
}

//performs the command, returns true if the command is to be repeated
bool Command::execute(){

	if(robot != NULL){ //execute model command
	
		switch(commandType){
		case ModelMove: robot->moveTo(x, z);
			break;
		case ModelFire://robot->fire();
			break;
		}

	} else{

		switch(commandType){
		case CameraMovePanSnap: camera->cameraTo(x, y, z, Camera::Pan, Camera::Snap);
			break;

		case CameraMovePanSmooth:camera->cameraTo(x, y, z, Camera::Pan, Camera::Smooth);
			break;

		case CameraMoveRotateSnap: camera->cameraTo(x, y, z, Camera::Rotate, Camera::Snap);
			break;

		case CameraMoveRotateSmooth: camera->cameraTo(x, y, z, Camera::Rotate, Camera::Smooth);
			break;

		case CameraFollow: camera->lookAt(followingModel);
			break;

		case CameraLookAtSnap:camera->lookAt(x, y, z, Camera::Snap);
			break;

		case CameraLookAtSmooth: camera->lookAt(x, y, z, Camera::Smooth);
			break;

		}
	}

	return repeatingNumber--;
}