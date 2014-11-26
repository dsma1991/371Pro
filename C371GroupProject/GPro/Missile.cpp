//#include "Missile.h"
//
//Missile::Missile(void)
//{
//}
//
//Missile::Missile(double newx, double newy, double newz, Vector3d robotForward)
//{
//	x=newx;
//	y=newy;
//	z=newz;
//	moveToX = 0;
//	moveToY = 0;
//	moveToZ = 0;
//	currentState = Idle;
//	
//	forward =  robotForward;
//	rotationSpeed = DEFAULT_MODEL_ROTATION_SPEED;
//	movementSpeed = DEFAULT_MODEL_MOVEMENT_SPEED;
//	distanceTolerance = movementSpeed * DEFAULT_MODEL_DISTANCE_TOLERANCE_FACTOR;
//	angle = 0;
//	angleBetween = 0;
//	modelLookAt = forward;
//	traversedAngle = 0;
//}
//
//
//Missile::~Missile(void)
//{
//}
//
//bool Missile::idle(std::vector<Model> models)
//{
//	x += movementSpeed * forward[0];
//	y += movementSpeed * forward[1];
//	z += movementSpeed * forward[2];
//
//	for(int i = 0; i < models.size(); ++i)
//	{
//		if(models[i].checkCollision(x,y,z))
//			return true;
//
//	}
//	return false;
//}