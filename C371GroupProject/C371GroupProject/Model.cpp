#include "Model.h"

//default constructor
Model::Model(void)
{
	x = 0;
	y = 0;
	z = 0;
	orientation = Quaternion<double>(0, 0, 0, 1);
	initialOrientation = orientation;
	currentState = Idle;
	distanceTolerance = 0.02;//must be higher than movementSpeed
	forward = Vector3d(0, 0, 1);
	forward.normalize();
	rotationSpeed = 0.001;
	movementSpeed = 0.001;
	t = 0;
}

//parameterized constructor, starts the model at the given coordinates in idle state
Model::Model(double startX, double startY, double startZ){
	x = startX;
	y = startY;
	z = startZ;
	orientation = Quaternion<double>(0, 0, 0, 1);
	initialOrientation = orientation;
	currentState = Idle;
	distanceTolerance = 0.02; //must be higher than movementSpeed
	forward = Vector3d(0, 0, 1);
	forward.normalize();
	rotationSpeed = 0.001;
	movementSpeed = 0.001;
	t = 0;
}


Model::~Model(void)
{
}


void Model::draw(){


	glPushMatrix();
	glTranslatef(x, y, z);

	//obtain the rotation matrix
	orientation.normalize();
	Matrix3d rotationMatrix = orientation.toRotationMatrix();
	
	GLdouble m[] = {	rotationMatrix(0, 0), rotationMatrix(0, 1), rotationMatrix(0, 2), 0,
						rotationMatrix(1, 0), rotationMatrix(1, 1), rotationMatrix(1, 2), 0,
						rotationMatrix(2, 0), rotationMatrix(2, 1), rotationMatrix(2, 2), 0,
						0, 0, 0, 1
	};

	//perform the rotation
	glMultMatrixd(m);

	//replace the cube with the actual model
	//glutSolidCube(1);
	//glutSolidTeapot(5);
	glutSolidCone(1, 10, 20, 20);
	glPopMatrix();
}

void Model::moveTo(double destX, double destY, double destZ){

	//if the model is close enough to the destination
	if (x <= destX + distanceTolerance && x >= destX - distanceTolerance &&
		y <= destY + distanceTolerance && y >= destY - distanceTolerance &&
		z <= destZ + distanceTolerance && z >= destZ - distanceTolerance){

		currentState = Idle;
		t = 0;

	}
	else{//if it's too far
		currentState = Moving;
		
		//if rotation is required
		if (t <= 1){
			//find the quaternion that converts the model's forward vector to the destination
			Quaternion<double> destOrientation = initialOrientation;
			Vector3d modelLookAt = Vector3d(destX - x, destY - y, destZ - z);
			modelLookAt.normalize();
			destOrientation = destOrientation.setFromTwoVectors(forward, modelLookAt);
			destOrientation.normalize();

			//set current orientation to gradually become the destination orientation
			t += rotationSpeed;

			//if rotation is done, set up for translation
			if (t > 1){
				//orientation = destOrientation;
				//orientation = initialOrientation.slerp(1, destOrientation);
				//orientation = destOrientation.slerp(1, initialOrientation);
				initialOrientation = orientation;
				forward = orientation._transformVector(forward);
				//forward = modelLookAt;
				std::cout << orientation.toRotationMatrix() << std::endl;
				std::cout << forward << std::endl;
			}
			else{//else update orientation
				orientation = initialOrientation.slerp(t, destOrientation);
				orientation.normalize();
			}

		}
		else{//rotation is not required, start translating
			x += movementSpeed * forward[0];
			y += movementSpeed * forward[1];
			z += movementSpeed * forward[2];
		}
	}
}