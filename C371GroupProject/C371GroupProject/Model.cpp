#include "Model.h"

//default constructor
Model::Model(void)
{
	x = 0;
	y = 0;
	z = 0;
	orientation = Quaternion<double>(1, 0, 0, 0);
	orientation.normalize();
	currentState = Idle;
}

//parameterized constructor, starts the model at the given coordinates in idle state
Model::Model(double startX, double startY, double startZ){
	x = startX;
	y = startY;
	z = startZ;
	orientation = Quaternion<double>(1, 0, 0, 0);
	currentState = Idle;
}


Model::~Model(void)
{
}


void Model::draw(){


	glPushMatrix();
	glTranslatef(x, y, z);

	//obtain the rotation matrix
	Matrix3d rotationMatrix = orientation.toRotationMatrix();

	GLdouble m[] = {	rotationMatrix(0, 0), rotationMatrix(0, 1), rotationMatrix(0, 2), 0,
						rotationMatrix(1, 0), rotationMatrix(1, 1), rotationMatrix(1, 2), 0,
						rotationMatrix(2, 0), rotationMatrix(2, 1), rotationMatrix(2, 2), 0,
						0, 0, 0, 1
	};
	//perform the rotation
	glMultMatrixd(m);

	//replace the cube with the actual model
	glutSolidCube(1);
	glPopMatrix();
}