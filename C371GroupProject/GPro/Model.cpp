#include "Model.h"

//default constructor
Model::Model(void)
{
	x = 0;
	y = 0;
	z = 0;
	moveToX = 0;
	moveToY = 0;
	moveToZ = 0;
	currentState = Idle;
	
	forward =  Vector3d(0, 0, 1);
	rotationSpeed = DEFAULT_MODEL_ROTATION_SPEED;
	movementSpeed = DEFAULT_MODEL_MOVEMENT_SPEED;
	distanceTolerance = movementSpeed * DEFAULT_MODEL_DISTANCE_TOLERANCE_FACTOR;
	angle = 0;
	angleBetween = 0;
	modelLookAt = forward;
	traversedAngle = 0;
}

//parameterized constructor, starts the model at the given coordinates in idle state
Model::Model(double startX, double startY, double startZ){
	x = startX;
	y = startY;
	z = startZ;
	moveToX = 0;
	moveToY = 0;
	moveToZ = 0;
	currentState = Idle;
	
	forward =  Vector3d(0, 0, 1);
	rotationSpeed = DEFAULT_MODEL_ROTATION_SPEED;
	movementSpeed = DEFAULT_MODEL_MOVEMENT_SPEED;
	distanceTolerance = movementSpeed * DEFAULT_MODEL_DISTANCE_TOLERANCE_FACTOR;
	angle = 0;
	angleBetween = 0;
	modelLookAt = forward;
	traversedAngle = 0;
}


Model::~Model(void)
{
}

//called by child classes
void Model::draw(){
	
	glTranslated(x, y, z);
	
	glRotated(angle, 0, 1, 0);

}

void Model::moveTo(double destX, double destY, double destZ){
	if(currentState == Idle){
	currentState = Moving;
	moveToX = destX;
	moveToY = destY;
	moveToZ = destZ;
	traversedAngle = 0;
	}
}

void Model::moving(){
	
	double distance = Vector3d(moveToX - x, moveToY - y, moveToZ - z).norm();

	if (distance < distanceTolerance){//if the model is close enough to the destination

		currentState = Idle;

		x = moveToX;
		y = moveToY;
		z = moveToZ;

	}
	else{//if it's too far

		modelLookAt = Vector3d(moveToX - x, moveToY - y, moveToZ - z);
		modelLookAt.normalize();
		double dotProduct = forward.dot(modelLookAt);
		double multMagnitude = forward.norm() * modelLookAt.norm();
		double cosAngle = dotProduct / multMagnitude;
		angleBetween = acos(cosAngle) * 180.0 / M_PI;
		//calculate cross product
		Vector3d crossProduct = forward.cross(modelLookAt);
		crossProduct.normalize();
		//dot product of cross product vector and the normal of the X-Z plane
		double crossDot = crossProduct.dot(Vector3d(0, 1, 0));

		//if rotation is required

		if (traversedAngle < angleBetween){
			if(crossDot >= 0 ){//rotate rightwards
				//keeping the angle under 360
				if (angle + rotationSpeed < 360){
					angle += rotationSpeed;
				}
				else {
					angle = angle + rotationSpeed - 360;
				}

			}else{//rotate leftwards
				//keeping the angle over 0
				if (angle - rotationSpeed > 0){
					angle -= rotationSpeed;
				}
				else {
					angle = angle - rotationSpeed + 360;
				}
			}
			traversedAngle += rotationSpeed;

			if (traversedAngle >= angleBetween){//done rotating
				forward = modelLookAt;
				forward.normalize();
			}
		}
		else{//rotation is not required, start translating
			x += movementSpeed * forward[0];
			y += movementSpeed * forward[1];
			z += movementSpeed * forward[2];
		}
	}
}

Model::State Model::getState(){
	return currentState;
}

bool Model::idle(){

	switch (currentState){

	case Idle:

		break;
	case Moving: moving();
		break;
	case Dying:

		break;

	}
	return true;
}

Vector3d Model::getCoordinates(){
	return Vector3d(x, y, z);
}

bool Model::checkCollision(double collisionX, double collisionY, double collisionZ)
{
	return (collisionX>x-5 && collisionX<x+5 && collisionY>y-5 && collisionY<y+5 && collisionZ>z-5 && collisionZ<z+5);
}