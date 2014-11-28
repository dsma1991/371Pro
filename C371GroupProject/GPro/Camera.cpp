#include "Camera.h"


//set to be at 0, 0, 0, looking down the -z axis
Camera::Camera(void)
{
	eyeX = 0;
	eyeY = 0;
	eyeZ = 0;
	lookAtX = 0;
	lookAtY = 0;
	lookAtZ = -1;
	upX = 0;
	upY = 1;
	upZ = 0;
	//rotation and movement speed
	rotationSpeed = DEFAULT_CAMERA_ROTATION_SPEED;
	movementSpeed = DEFAULT_CAMERA_MOVEMENT_SPEED;
	currentState = Idle;
	cameraMode = Pan;
	movementType = Smooth;
	distanceTolerance = movementSpeed * DEFAULT_CAMERA_DISTANCE_TOLERANCE_FACTOR;
	model = NULL;
}

Camera::Camera(double initialEyeX, double initialEyeY, double initialEyeZ,
			   double initialLookAtX, double initialLookAtY, double initialLookAtZ,
			   double initialUpX, double initialUpY, double initialUpZ){

				   eyeX = initialEyeX;
				   eyeY = initialEyeY;
				   eyeZ = initialEyeZ;
				   lookAtX = initialLookAtX;
				   lookAtY = initialLookAtY;
				   lookAtZ = initialLookAtZ;
				   upX = initialUpX;
				   upY = initialUpY;
				   upZ = initialUpZ;

				   //rotation and movement speed
				   rotationSpeed = DEFAULT_CAMERA_ROTATION_SPEED;
				   movementSpeed = DEFAULT_CAMERA_MOVEMENT_SPEED;

				   currentState = Idle;
				   cameraMode = Pan;
				   movementType = Smooth;
				   distanceTolerance = movementSpeed * DEFAULT_CAMERA_DISTANCE_TOLERANCE_FACTOR;
				   model = NULL;
}


Camera::~Camera(void)
{
}

 //Calls gluLookAt
void Camera::displayCamera(){

	gluLookAt(	eyeX, eyeY, eyeZ,
		lookAtX, lookAtY, lookAtZ,
		upX, upY, upZ);

}

// move camera to destination coordinates using the mode and move type specified
void Camera::cameraTo(double x, double y, double z, CameraMode mode, Movement moveType){ 

	if (currentState == Idle){
		model = NULL;
		cameraMode = mode;
		movementType = moveType;
		destX = x;
		destY = y;
		destZ = z;


		switch (moveType){

		case Snap:

			switch (mode){
			case Pan:snapPanCameraTo();
				break;
			case Rotate:snapRotateCameraTo();
				break;
			}

			break;
		case Smooth:currentState = Moving;
			break;

		}
	}
}

void Camera::snapPanCameraTo(){

	lookAtX += destX - eyeX;
	lookAtY += destY - eyeY;
	lookAtZ += destZ - eyeZ;

	eyeX = destX;
	eyeY = destY;
	eyeZ = destZ;
}

void Camera::snapRotateCameraTo(){
	eyeX = destX;
	eyeY = destY;
	eyeZ = destZ;
}

void Camera::movePanCameraTo(){


	Vector3d moveDirection = Vector3d(destX - eyeX, destY - eyeY, destZ - eyeZ);
	moveDirection.normalize();
	eyeX += movementSpeed * moveDirection[0];
	eyeY += movementSpeed * moveDirection[1];
	eyeZ += movementSpeed * moveDirection[2];

	lookAtX += movementSpeed * moveDirection[0];
	lookAtY += movementSpeed * moveDirection[1];
	lookAtZ += movementSpeed * moveDirection[2];

}

void Camera::moveRotateCameraTo(){
	Vector3d moveDirection = Vector3d(destX - eyeX, destY - eyeY, destZ - eyeZ);
	moveDirection.normalize();
	eyeX += movementSpeed * moveDirection.x();
	eyeY += movementSpeed * moveDirection.y();
	eyeZ += movementSpeed * moveDirection.z();
}

//determines camera's behaviour according to its class variables
void Camera::idle(){

	switch (currentState){

	case Idle:
		if (model != NULL){
			Vector3d coords = model->getCoordinates();
			lookAtX = coords[0];
			lookAtY = coords[1];
			lookAtZ = coords[2];
		}
		break;
	case Moving: moving();
		break;
	case Rotating: rotating();
		break;

	}

}

void Camera::moving(){
	//if movement is done, set to idle state

	double distance = Vector3d(destX - eyeX, destY - eyeY, destZ - eyeZ).norm();

	if (distance < distanceTolerance){//if the model is close enough to the destination

		currentState = Idle;

		eyeX = destX;
		eyeY = destY;
		eyeZ = destZ;

	}
	else
	{
		switch (cameraMode){
		case Pan:movePanCameraTo();
			break;
		case Rotate:moveRotateCameraTo();
			break;
		}
	}
}

//looks at a point using the move type specified
void Camera::lookAt(double x, double y, double z, Movement moveType){
	if (currentState == Idle){
		model = NULL;
		destLookAtX = x;
		destLookAtY = y;
		destLookAtZ = z;
		switch(moveType){
		case Snap: snapLookAt();
			break;
		case Smooth: currentState = Rotating;
			break;
		}
	}
}

void Camera::snapLookAt(){
	lookAtX = destLookAtX;
	lookAtY = destLookAtY;
	lookAtZ = destLookAtZ;
}

//set a model to continuously look at
void Camera::lookAt(Model* modelToLook){
	model = modelToLook;
}

Camera::State Camera::getState(){
	return currentState;
}

void Camera::rotating(){

	//if movement is done, set to idle state

	double distance = Vector3d(destLookAtX - lookAtX, destLookAtY - lookAtY, destLookAtZ - lookAtZ).norm();

	if (distance < distanceTolerance){//if the model is close enough to the destination

		currentState = Idle;

		lookAtX = destLookAtX;
		lookAtY = destLookAtY;
		lookAtZ = destLookAtZ;

	}else{//rotate

	Vector3d moveDirection = Vector3d(destLookAtX - lookAtX, destLookAtY - lookAtY, destLookAtZ - lookAtZ);
	moveDirection.normalize();
	lookAtX += rotationSpeed * moveDirection.x();
	lookAtY += rotationSpeed * moveDirection.y();
	lookAtZ += rotationSpeed * moveDirection.z();
	}
}