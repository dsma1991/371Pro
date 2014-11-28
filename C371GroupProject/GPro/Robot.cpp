#include "Robot.h"

Robot::Robot(void)
{

}

Robot::Robot(double startX, double startZ, double startY): Model(startX, startY, startZ)
{
	rotationSpeed = 5;
	movementSpeed = 0.5;

	robotModel = ModelLoader();
	robotModel.readInModel("mech.obj");
	
}



Robot::~Robot(void)
{
}

//draws the correct model
void Robot::draw()
{
	glPushMatrix();
	Model::draw();
	robotModel.drawModel();
	glPopMatrix();
}

//determines robot's behaviour according to its class variables
bool Robot::idle(){
	Model::idle();
	/*for(std::vector<Model>::iterator it = missiles.begin(); it != missiles.end();++it)
	{
		if(it->idle(models))
		{
			missiles.erase(it);
			it = missiles.begin();
			if(missiles.empty())
				break;
		}
	}*/
	return true;
}

//moves to given coordinates
void Robot::moveTo(double destX, double destZ){
	Model::moveTo(destX, y, destZ);
}

//void Model::fire()
//{
//	Missile temp(x,y,z,forward);
//	
//	missiles.push_back(temp);
//}