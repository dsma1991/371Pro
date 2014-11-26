#pragma once
#include "Robot.h"
#include "imageloader.h"
#include "Terrain.h"
#include "ParticleSystem.h"
#include "Camera.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Command.h"
#include <queue>

#define SKYBOX_ROTATE_SPEED 2

typedef struct {
	int width;
	int height;
	char* title;

	float field_of_view_angle;
	float z_near;
	float z_far;
}

glutWindow;

glutWindow win;

const double PI  = 3.141592653589793238463;
const int MIN_DISTANCE = 0, MAX_DISTANCE = 500;

double eyeX, eyeY, eyeZ, centerX = 50 , centerY = 0, centerZ = 50;
double distance = 200;
double vertAngle = 3*PI/4, horizAngle = PI/2;

GLUquadricObj * quadratic;
//Camera
Camera camera; 
int cameraOrder = 0;
//Skybox
GLuint _skyboxTexture1;
float skyboxSize = 4000.0f;
float skyboxRotate = 0.0;

//Terrain 
GLuint _terrainTexture1;
Terrain terrainObject;

//Dalek
GLuint _dalekTexture;
//Wall
GLuint _wallTexture;
//GUARDIAN
GLuint _guardianTexture;

//MATERIALS
GLfloat whiteDiffuseMAT[] = {1.0, 1.0, 1.0};
GLfloat whiteSpecularMat[] = {1.0, 1.0, 1.0};
GLfloat blankMAT[] = {0.0, 0.0, 0.0};
GLfloat shinyMAT[] = {128};
GLfloat noShinyMAT[] = {0};
GLfloat emissionLight[] = {0.0, 0.0, 0.0};

//Lighting
GLfloat whiteLight[] = {1.0f, 1.0f, 1.0f};
GLfloat yellowLight[] = {1.2f, 1.2f, 1.0f};
GLfloat greenLight[] = {0.0, 1.0, 0.0};
GLfloat light0Position[] = {50.0, 100.0, 20.0, 0.0};

GLfloat movingLightDirection[] = {0.0, 0.0, 1.0};
float spotlightCutOff = 25.0;
float movingLightAngle = 0.0;

//Particle System
ParticleSystem particleSys;
GLuint LoadTextureRAW(const char * filename, int width, int height);
void FreeTexture(GLuint texturez);
GLfloat particleTexture[10];
float zoom = -60.0;

//all the robot models in the scene
std::vector<Robot> robots;
//camera commands
std::queue<Command> cameraCommands;
//robot commands
std::vector<std::queue<Command>> robotCommands;

//Titan
/*
std::vector<Coordinates> titanVertices;
std::vector<Coordinates> titanNormals;
std::vector<Coordinates> titanTextures;
std::vector<std::vector<std::vector<int>>> titanFaceVertex;
std::vector<std::vector<std::vector<int>>> titanFaceNormal;
std::vector<std::vector<std::vector<int>>> titanFaceTexture;
std::vector<std::string> texNames;*/

std::vector<Coordinates> WallVertices;
std::vector<Coordinates> WallNormals;
std::vector<Coordinates> WallTextures;
std::vector<std::vector<std::vector<int>>> WallFaceVertex;
std::vector<std::vector<std::vector<int>>> WallFaceNormal;
std::vector<std::vector<std::vector<int>>> WallFaceTexture;
std::vector<std::string> wallTexNames;

std::vector<Coordinates> GuardianVertices;
std::vector<Coordinates> GuardianNormals;
std::vector<Coordinates> GuardianTextures;
std::vector<std::vector<std::vector<int>>> GuardianFaceVertex;
std::vector<std::vector<std::vector<int>>> GuardianFaceNormal;
std::vector<std::vector<std::vector<int>>> GuardianFaceTexture;
std::vector<std::string> GuardianTexNames;


void readInModel(std::string filename, std::vector<std::string> *textureNames, std::vector<Coordinates> *vertices, std::vector<Coordinates> *normals, std::vector<Coordinates> *textures, 
				 std::vector<std::vector<std::vector<int>>> *faceVertex, std::vector<std::vector<std::vector<int>>> *faceNormal, std::vector<std::vector<std::vector<int>>> *faceTexture)
{
	std::ifstream fin(filename.c_str());

	std::vector<std::vector<int>> faceTempV;
	std::vector<std::vector<int>> faceTempT;
	std::vector<std::vector<int>> faceTempN;


	char input;
	while(fin>>input)
	{
		if(input=='v')
		{
			input = fin.peek();
			if(input=='n')
			{
				fin>>input;
				Coordinates temp;
				fin>>temp.x;
				fin>>temp.y;
				fin>>temp.z;
				normals->push_back(temp);
			}
			else if(input=='t')
			{
				fin>>input;
				Coordinates temp;
				fin>>temp.x;
				fin>>temp.y;
				textures->push_back(temp);
			}
			else // if input==' '
			{
				Coordinates temp;
				fin>>temp.x;
				fin>>temp.y;
				fin>>temp.z;
				vertices->push_back(temp);
			}
		}
		else if(input=='f')
		{
			std::stringstream stream;
			int temp;
			int next;
			std::string faceLine;
			std::getline(fin,faceLine); //?
			stream << faceLine;

			std::vector<int> tempVectorV;
			std::vector<int> tempVectorN;
			std::vector<int> tempVectorT;
			while(stream >> next) // ?
			{
				tempVectorV.push_back(next);
				stream>>input; // to get rid of the /
				stream>>next;
				tempVectorT.push_back(next);
				stream>>input; // to get rid of the /
				stream>>next;
				tempVectorN.push_back(next);
			}
			faceTempV.push_back(tempVectorV);
			faceTempT.push_back(tempVectorT);
			faceTempN.push_back(tempVectorN);
		}
		else if(input == 'u')
		{
			fin>>input;//s
			fin>>input;//e
			fin>>input;//m
			fin>>input;//t
			fin>>input;//l
			std::string tempName;
			fin>>tempName;
			textureNames->push_back(tempName);
			if(faceTempV.size() != 0)
			{
				faceVertex->push_back(faceTempV);
				faceNormal->push_back(faceTempN);
				faceTexture->push_back(faceTempT);
			}
			faceTempV.clear();
			faceTempT.clear();
			faceTempN.clear();
		}
		else
		{
			std::string garbage;
			std::getline(fin,garbage);
		}
	}
	faceVertex->push_back(faceTempV);
	faceNormal->push_back(faceTempN);
	faceTexture->push_back(faceTempT);
	fin.close();
}


void drawModel(std::vector<Coordinates> *vertices, std::vector<Coordinates> *normals, std::vector<Coordinates> *textures, 
			   std::vector<std::vector<std::vector<int>>> *faceVertex, std::vector<std::vector<std::vector<int>>> *faceNormal, std::vector<std::vector<std::vector<int>>> *faceTexture)
{
	// also need to have texture reading and whatever
	for(int k = 0; k < faceVertex->size(); ++k)
		for(int i = 0; i < (*faceVertex)[k].size(); ++i)
		{
			glBegin(GL_POLYGON);
			for(int j = 0; j < (*faceVertex)[k][i].size(); ++j)
			{
				Coordinates tempTex = (*textures)[(*faceTexture)[k][i][j]-1];
				Coordinates tempNorm = (*normals)[(*faceNormal)[k][i][j]-1];
				Coordinates tempVert= (*vertices)[(*faceVertex)[k][i][j]-1];
				glTexCoord2d(tempTex.x,tempTex.y);
				glNormal3d(tempNorm.x,tempNorm.y,tempNorm.z);
				glVertex3d(tempVert.x,tempVert.y,tempVert.z);
			}
			glEnd();
		}
}

double lightHeight = 40;
void SpotLights(){
	//First Spotlight
	GLfloat mov_position[] = { 0.0, lightHeight, 0.0, 1.0 };
	GLfloat mov_diffuse[] = {1.0, 0.0, 0.0};
	GLfloat mov_specular[]  = {1.0, 0.0, 0.0};
	GLfloat directionVec[] = {0.0, -1.0, 0.0};
	float cutoff = 40.0;
	glLightfv(GL_LIGHT1, GL_POSITION, mov_position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, mov_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, mov_specular);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, directionVec);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, cutoff);
}

//Load image into texture
GLuint loadTexture(Image* image){
	GLuint textureID;
	glGenTextures(1, &textureID); // make room for texture
	glBindTexture(GL_TEXTURE_2D, textureID); //tell opengl which texture to edit
	glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_RGB, //format for image
		image->width, image->height,
		0,
		GL_RGB,
		GL_UNSIGNED_BYTE,
		image->pixels);
	return textureID;
}

// Initiliaze the OpenGL window
void init(void)
{
	double x = 0.0;
	double y = 40.0;
	double z = 1000; 
	double lookAtX = 0.0;
	double lookAtY = 0.0;
	double lookAtZ = 0.0;

	camera = Camera(0.0, -45.0, 500.0, 0.0, -56.0, 250.0);
	//camera = Camera(0.0, 50.0, 0.0, 0.0, -56.0, 250.0);

	glMatrixMode(GL_PROJECTION);												// select projection matrix
	glViewport(0, 0, win.width, win.height);									// set the viewport
	glMatrixMode(GL_PROJECTION);												// set matrix mode
	glLoadIdentity();															// reset projection matrix
	GLfloat aspect = (GLfloat) win.width / win.height;
	gluPerspective(win.field_of_view_angle, aspect, win.z_near, win.z_far);		// set up a perspective projection matrix
	glMatrixMode(GL_MODELVIEW);										// specify which matrix is the current matrix
	glShadeModel( GL_SMOOTH );
	glClearDepth( 1.0f );														// specify the clear value for the depth buffer
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LEQUAL );
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );						// specify implementation-specific hints
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	//Textures
	Image* skyboxTexture = loadBMP("starrySky.bmp");
	_skyboxTexture1 = loadTexture(skyboxTexture);
	delete(skyboxTexture);

	Image* terrainTexture = loadBMP("terrainTexture.bmp");
	_terrainTexture1 = loadTexture(terrainTexture);
	delete(terrainTexture);

	Image* dalekTexture1 = loadBMP("mech.bmp");
	_dalekTexture = loadTexture(dalekTexture1);
	delete(dalekTexture1);

	Image* wallimg = loadBMP("WallTexture.bmp");
	_wallTexture = loadTexture(wallimg);
	delete(wallimg);

	Image* guardianimg = loadBMP("guardian_texture.bmp");
	_guardianTexture = loadTexture(guardianimg);
	delete(guardianimg);

	//Lighting
	glEnable(GL_LIGHTING);

	//Particle Systems
	glEnable(GL_TEXTURE_2D);
	zoom = -60.0f;
	particleSys.setParticleSystemType(4); //Fire with smoke
	particleSys.createParticles();
	particleTexture[0] = LoadTextureRAW("particle_mask.raw", 256, 256); //load alpha for texture
	particleTexture[1] = LoadTextureRAW("particle.raw", 256, 256); //load texture
	glDisable(GL_TEXTURE_2D);

	//CULLING
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);// hide all CCW Faces

	//Model
	//readInModel("mech.obj", &texNames, &titanVertices, &titanNormals, &titanTextures, &titanFaceVertex, &titanFaceNormal, &titanFaceTexture);

	readInModel("Wall.obj", &wallTexNames, &WallVertices, &WallNormals, &WallTextures, &WallFaceVertex, &WallFaceNormal, &WallFaceTexture);

	readInModel("guardian.obj", &GuardianTexNames, &GuardianVertices, &GuardianNormals, &GuardianTextures, &GuardianFaceVertex, &GuardianFaceNormal, &GuardianFaceTexture);

	//attacking force
	robots.push_back(Robot(450, 450)); //robot 1
	robots.push_back(Robot(400, 480));//robot 2
	robots.push_back(Robot(0, 233));//robot 3

	//defending force
	robots.push_back(Robot(-200, 25));//robot 4
	robots.push_back(Robot(200, 25));//robot 5

	//extra attackers
	robots.push_back(Robot(-450, 450));//robot 6
	robots.push_back(Robot(-400, 480));//robot 7

	#pragma region RobotCommands
	
	//robot 1
	std::queue<Command> temp;
	temp.push(Command((Robot*)&robots[0], Command::ModelMove, 0, 300, -56.0, 175));
	temp.push(Command((Robot*)&robots[0], Command::ModelMove, 0, 200, -56.0, 150));
	temp.push(Command((Robot*)&robots[0], Command::ModelMove, 0, 150, -56.0, 125));
	robotCommands.push_back(temp);

	//robot 2
	std::queue<Command> temp1;
	temp1.push(Command((Robot*)&robots[1], Command::ModelMove, 0, 400, -56.0, 200));
	robotCommands.push_back(temp1);

	//robot 3
	std::queue<Command> temp2;
	temp2.push(Command((Robot*)&robots[2], Command::ModelMove, 0, 0, -56.0, 125));
	robotCommands.push_back(temp2);

	//robot 4
	std::queue<Command> temp3;
	temp3.push(Command((Robot*)&robots[3], Command::ModelMove, -1, -20, -56.0, 25));
	temp3.push(Command((Robot*)&robots[3], Command::ModelMove, -1, -200, -56.0, 25));
	robotCommands.push_back(temp3);

	//robot 5
	std::queue<Command> temp4;
	temp4.push(Command((Robot*)&robots[4], Command::ModelMove, -1, 20, -56.0, 25));
	temp4.push(Command((Robot*)&robots[4], Command::ModelMove, -1, 200, -56.0, 25));
	robotCommands.push_back(temp4);

	//robot 6
	std::queue<Command> temp5;
	temp5.push(Command((Robot*)&robots[5], Command::ModelMove, 0, -300, -56.0, 175));
	temp5.push(Command((Robot*)&robots[5], Command::ModelMove, 0, -200, -56.0, 150));
	temp5.push(Command((Robot*)&robots[5], Command::ModelMove, 0, -150, -56.0, 125));
	robotCommands.push_back(temp5);

	//robot 7
	std::queue<Command> temp6;
	temp6.push(Command((Robot*)&robots[6], Command::ModelMove, 0, -400, -56.0, 200));
	robotCommands.push_back(temp6);



	#pragma endregion


	#pragma region CameraCommands
	cameraCommands.push(Command(&camera, Command::CameraMoveRotateSmooth, 0, -77*2, -45.0, 487));
	cameraCommands.push(Command(&camera, Command::CameraMoveRotateSmooth, 0, -146*2, -45.0, 452.0));
	cameraCommands.push(Command(&camera, Command::CameraMoveRotateSmooth, 0, -202*2, -45.0, 397.0));
	cameraCommands.push(Command(&camera, Command::CameraMoveRotateSmooth, 0, -258*2, -45.0, 327.0));
	cameraCommands.push(Command(&camera, Command::CameraMoveRotateSmooth, 0, -250*2, -45.0, 250.0));
	cameraCommands.push(Command(&camera, Command::CameraMoveRotateSmooth, 0, -475, -45.0, 173));
	cameraCommands.push(Command(&camera, Command::CameraMoveRotateSmooth, 0, -404, -45.0, 103));
	cameraCommands.push(Command(&camera, Command::CameraMoveRotateSmooth, 0, -294, -45.0, 47));
	cameraCommands.push(Command(&camera, Command::CameraMoveRotateSmooth, 0, -154, -45.0, 12));
	cameraCommands.push(Command(&camera, Command::CameraMoveRotateSmooth, 0, 0, -45.0, 0));
	cameraCommands.push(Command(&camera, Command::CameraLookAtSmooth, 0, 25, -45.0, -150/2));
	cameraCommands.push(Command(&camera, Command::CameraLookAtSmooth, 0, 0.0, -45.0, -150));
	cameraCommands.push(Command(&camera, Command::CameraMovePanSmooth, 0, 0.0, 135.0, 0.0)); //middle point
	cameraCommands.push(Command(&camera, Command::CameraLookAtSmooth, 0, 0.0, -56.0, 125));
	cameraCommands.push(Command(&camera, Command::CameraMoveRotateSmooth, 0, 0, 135.0, 0));
	cameraCommands.push(Command(&camera, Command::CameraMoveRotateSmooth, 0, 78,  135.0, 1.5));
	cameraCommands.push(Command(&camera, Command::CameraMoveRotateSmooth, 0, 154, 135.0, 6));
	cameraCommands.push(Command(&camera, Command::CameraMoveRotateSmooth, 0, 227, 135.0, 13));
	cameraCommands.push(Command(&camera, Command::CameraMoveRotateSmooth, 0, 293, 135.0, 23));
	cameraCommands.push(Command(&camera, Command::CameraMoveRotateSmooth, 0, 353, 135.0, 36));
	cameraCommands.push(Command(&camera, Command::CameraMoveRotateSmooth, 0, 404, 135.0, 51));
	cameraCommands.push(Command(&camera, Command::CameraMoveRotateSmooth, 0, 445, 135.0, 68));
	cameraCommands.push(Command(&camera, Command::CameraMoveRotateSmooth, 0, 475, 135.0, 86));
	cameraCommands.push(Command(&camera, Command::CameraMoveRotateSmooth, 0, 493, 135.0, 105));
	cameraCommands.push(Command(&camera, Command::CameraMoveRotateSmooth, 0, 500, 135.0, 125));
	cameraCommands.push(Command(&camera, Command::CameraMoveRotateSmooth, 0, 493, 135.0, 144));
	cameraCommands.push(Command(&camera, Command::CameraMoveRotateSmooth, 0, 475, 135.0, 163));
	cameraCommands.push(Command(&camera, Command::CameraMoveRotateSmooth, 0, 445, 135.0, 181));
	cameraCommands.push(Command(&camera, Command::CameraMoveRotateSmooth, 0, 404, 135.0, 198));
	cameraCommands.push(Command(&camera, Command::CameraMoveRotateSmooth, 0, 353, 135.0, 213));
	cameraCommands.push(Command(&camera, Command::CameraMoveRotateSmooth, 0, 293, 135.0, 226));
	cameraCommands.push(Command(&camera, Command::CameraMoveRotateSmooth, 0, 226, 135.0, 236));
	cameraCommands.push(Command(&camera, Command::CameraMoveRotateSmooth, 0, 154,  135.0, 243));
	cameraCommands.push(Command(&camera, Command::CameraMoveRotateSmooth, 0, 78, 135.0, 248));
	cameraCommands.push(Command(&camera, Command::CameraMoveRotateSmooth, 0, 0, 135.0, 250));
	cameraCommands.push(Command(&camera, Command::CameraMoveRotateSmooth, 0, 0, -45, 250));
	cameraCommands.push(Command(&camera, Command::CameraLookAtSmooth, 0, 0.0, -10, 0));
	cameraCommands.push(Command(&camera, Command::CameraMoveRotateSmooth, -1, -300, 100, -50));
	cameraCommands.push(Command(&camera, Command::CameraMoveRotateSmooth, -1, -300, 100, 400));
	cameraCommands.push(Command(&camera, Command::CameraMoveRotateSmooth, -1, 300, 100, 400));
	cameraCommands.push(Command(&camera, Command::CameraMoveRotateSmooth, -1, 300, 100, -50));
	//cameraCommands.push(Command(&camera, Command::CameraMoveRotateSmooth, -1, 50, -45, 250));
	//cameraCommands.push(Command(&camera, Command::CameraMoveRotateSmooth, -1, -50, -45, 250));
#pragma endregion

}

void Sunlight(){
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light0Position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, whiteLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, whiteLight);
}

void DrawParticles (void)
{
	int i;
	for (i = 1; i < particleSys.getNumOfParticles(); i++)
	{
		glPushMatrix();
		// set color and fade value (alpha) of current particle
		glColor4f(particleSys.getR(i), particleSys.getG(i), particleSys.getB(i), particleSys.getAlpha(i));
		// move the current particle to its new position
		glTranslatef(particleSys.getXPos(i), particleSys.getYPos(i), particleSys.getZPos(i) + zoom);
		// rotate the particle (this is proof of concept for when proper smoke texture is added)
		glRotatef (particleSys.getDirection(i) - 90, 0, 0, 1);
		// scale the current particle (only used for smoke)
		glScalef(particleSys.getScale(i), particleSys.getScale(i), particleSys.getScale(i));

		glEnable (GL_DEPTH_TEST);
		glEnable (GL_BLEND);

		glBlendFunc (GL_DST_COLOR, GL_ZERO);
		glBindTexture (GL_TEXTURE_2D, particleTexture[0]);

		glBegin (GL_QUADS);
		glTexCoord2d (0, 0);  glVertex3f (-1, -1, 0);
		glTexCoord2d (1, 0);  glVertex3f (1, -1, 0);
		glTexCoord2d (1, 1);  glVertex3f (1, 1, 0);
		glTexCoord2d (0, 1);  glVertex3f (-1, 1, 0);
		glEnd();

		glBlendFunc (GL_ONE, GL_ONE);
		glBindTexture (GL_TEXTURE_2D, particleTexture[1]);

		glBegin (GL_QUADS);
		glTexCoord2d (0, 0);  glVertex3f (-1, -1, 0);
		glTexCoord2d (1, 0);  glVertex3f (1, -1, 0);
		glTexCoord2d (1, 1);  glVertex3f (1, 1, 0);
		glTexCoord2d (0, 1);  glVertex3f (-1, 1, 0);
		glEnd();

		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);

		glPopMatrix();
	}
}

void drawSkybox(){
	glPushMatrix();
	glPushAttrib(GL_ENABLE_BIT);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);

	//Set all vertices to white
	glColor4f(1,1,1,1);

	//Render Front Quad
	glBindTexture(GL_TEXTURE_2D, _skyboxTexture1); //Texture 1
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(  skyboxSize, -skyboxSize, -skyboxSize );
	glTexCoord2f(1, 0); glVertex3f( -skyboxSize, -skyboxSize, -skyboxSize );
	glTexCoord2f(1, 1); glVertex3f( -skyboxSize,  skyboxSize, -skyboxSize );
	glTexCoord2f(0, 1); glVertex3f(  skyboxSize,  skyboxSize, -skyboxSize );
	glEnd();


	// Render the left quad
	glBindTexture(GL_TEXTURE_2D, _skyboxTexture1); //Texture 1
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBegin(GL_QUADS);
	glColor4f(1,1,1,1);
	glTexCoord2f(0, 0); glVertex3f(  skyboxSize, -skyboxSize,  skyboxSize );
	glTexCoord2f(1, 0); glVertex3f(  skyboxSize, -skyboxSize, -skyboxSize );
	glTexCoord2f(1, 1); glVertex3f(  skyboxSize,  skyboxSize, -skyboxSize );
	glTexCoord2f(0, 1); glVertex3f(  skyboxSize,  skyboxSize,  skyboxSize );
	glEnd();

	// Render the back quad
	glBindTexture(GL_TEXTURE_2D, _skyboxTexture1); //Texture 1
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f( -skyboxSize, -skyboxSize,  skyboxSize );
	glTexCoord2f(1, 0); glVertex3f(  skyboxSize, -skyboxSize,  skyboxSize );
	glTexCoord2f(1, 1); glVertex3f(  skyboxSize,  skyboxSize,  skyboxSize );
	glTexCoord2f(0, 1); glVertex3f( -skyboxSize,  skyboxSize,  skyboxSize );
	glEnd();

	// Render the right quad
	glBindTexture(GL_TEXTURE_2D, _skyboxTexture1); //Texture 1
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f( -skyboxSize, -skyboxSize, -skyboxSize );
	glTexCoord2f(1, 0); glVertex3f( -skyboxSize, -skyboxSize,  skyboxSize );
	glTexCoord2f(1, 1); glVertex3f( -skyboxSize,  skyboxSize,  skyboxSize );
	glTexCoord2f(0, 1); glVertex3f( -skyboxSize,  skyboxSize, -skyboxSize );
	glEnd();

	// Render the top quad
	glBindTexture(GL_TEXTURE_2D, _skyboxTexture1); //Texture 1
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex3f( -skyboxSize,  skyboxSize, -skyboxSize );
	glTexCoord2f(0, 0); glVertex3f( -skyboxSize,  skyboxSize,  skyboxSize );
	glTexCoord2f(1, 0); glVertex3f(  skyboxSize,  skyboxSize,  skyboxSize );
	glTexCoord2f(1, 1); glVertex3f(  skyboxSize,  skyboxSize, -skyboxSize );
	glEnd();

	// Render the bottom quad
	glBindTexture(GL_TEXTURE_2D, _skyboxTexture1); //Texture 1
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f( -skyboxSize, -skyboxSize, -skyboxSize );
	glTexCoord2f(0, 1); glVertex3f( -skyboxSize, -skyboxSize,  skyboxSize );
	glTexCoord2f(1, 1); glVertex3f(  skyboxSize, -skyboxSize,  skyboxSize );
	glTexCoord2f(1, 0); glVertex3f(  skyboxSize, -skyboxSize, -skyboxSize );
	glEnd();

	glDisable(GL_TEXTURE_2D);
	// Restore enable bits and matrix
	glPopAttrib();
	glPopMatrix();
}

void drawTransparentObject(){
	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _guardianTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glScaled(50.0,50.0,50.0);
	glMaterialfv(GL_FRONT, GL_EMISSION, emissionLight);
	drawModel(&GuardianVertices, &GuardianNormals, &GuardianTextures, &GuardianFaceVertex, &GuardianFaceNormal, &GuardianFaceTexture);
	glMaterialfv(GL_FRONT, GL_EMISSION, blankMAT);
	glDisable(GL_BLEND);
	glPopMatrix();
}

void display(void)
{	
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//	glPushMatrix();
	glLoadIdentity();
	camera.displayCamera();

	glPushMatrix();
	glDisable(GL_CULL_FACE);
	drawSkybox();
	glEnable(GL_CULL_FACE);
	glPopMatrix();


	glPushMatrix();
	//Terrain
	glBindTexture(GL_TEXTURE_2D, _terrainTexture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	terrainObject.DrawTerrain();
	glPopMatrix();

	glPushMatrix();
	//Spotlight
	SpotLights();
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _dalekTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, greenLight);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shinyMAT);

	for(int i = 0; i < robots.size(); ++i){
		robots[i].draw();
	}

	glTranslatef(0.0,-56.0,250.0);
	//drawModel(&titanVertices, &titanNormals, &titanTextures, &titanFaceVertex, &titanFaceNormal, &titanFaceTexture);
	glTranslatef(50.0, 0.0, 0.0);
	//	drawModel(&titanVertices, &titanNormals, &titanTextures, &titanFaceVertex, &titanFaceNormal, &titanFaceTexture);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _wallTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, whiteDiffuseMAT);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, blankMAT);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,noShinyMAT); 
	glTranslatef(0.0, 0.0, -150.0);
	glScaled(10,10,5);
	glRotated(90, 0.0, -1.0, 0.0);
	drawModel(&WallVertices, &WallNormals, &WallTextures, &WallFaceVertex, &WallFaceNormal, &WallFaceTexture);
	glPushMatrix();
	for(int i= 0; i <= 4; i++){
		glTranslatef(0.0, 0.0, 30.5);
		drawModel(&WallVertices, &WallNormals, &WallTextures, &WallFaceVertex, &WallFaceNormal, &WallFaceTexture);
	}
	glPopMatrix();
	glPushMatrix();
	for(int i= 0; i <= 4; i++){
		glTranslatef(0.0, 0.0, -30.5);
		drawModel(&WallVertices, &WallNormals, &WallTextures, &WallFaceVertex, &WallFaceNormal, &WallFaceTexture);
	}
	glPopMatrix();
	glEnable(GL_CULL_FACE);
	glPopMatrix();

	glPushMatrix();
	glTranslated(20, 10, -20);
	glDisable(GL_CULL_FACE);
	glDisable(GL_LIGHTING);
	glTranslatef(-20.0, -70.0, -10);
	DrawParticles();
	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);

	glTranslatef(0.0, 60, -100.0);
	drawTransparentObject();
	glDisable(GL_TEXTURE_2D);
	//____________________Don't Draw After this comment___________________________________//
	glPopMatrix();

	//	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

int WireFrame = 0;			// Flag for wire frame mode

void toggleWireFrames(){
	WireFrame = 1-WireFrame;
	if (WireFrame)
		glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);		// Wireframes
	else 
		glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);		// Solid
	glutPostRedisplay();
}

void Night(){
	glDisable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	emissionLight[2] = 0.2;
}

void Daytime(){
	glDisable(GL_LIGHT1);
	glEnable(GL_LIGHT0);
	emissionLight[2] = 0.0;
}

void keyboard (unsigned char key, int x, int y)
{
	switch (key)
	{
	case '0':
		//robots[0].fire();
		break;
	case 'i':
		//WIREFRAMES
		toggleWireFrames();
		break;
		break;
	case 'p':
		lightHeight+=0.5;
		std::cout<<lightHeight<<std::endl;
		break;
	case 'o':
		lightHeight-=0.5;
		std::cout<<lightHeight<<std::endl;
		break;
	case ']':
		distance -= 5;
		break;
	case '\\':
		distance += 5;
		break;
	case 'w':
		centerX -= cos(horizAngle)*3;
		centerZ -= sin(horizAngle)*3;
		break;
	case 's':
		centerX += cos(horizAngle)*3;
		centerZ += sin(horizAngle)*3;
		break;
	case 'a':
		centerX -= sin(horizAngle)*3;
		centerZ -= -cos(horizAngle)*3;
		break;
	case 'd':
		centerX += sin(horizAngle)*3;
		centerZ += -cos(horizAngle)*3;
		break;
	case 'f':
		zoom = -40.0f;
		particleSys.setParticleSystemType(3);
		particleSys.createParticles();
		break;
	case 'F':
		zoom = -40.0f;
		particleSys.setParticleSystemType(4);
		particleSys.createParticles();
		break;
	case 'l':
		Daytime();
		break;
	case 'L':
		Night();
		break;
	case 27:
		exit(0);			
	}
	glutPostRedisplay();	// Redraw the scene
}


void specialKey(int key, int x, int y) { 

	// The keys below are using the gluLookAt() function for navigation
	// Check which key is pressed
	switch(key)
	{
	case GLUT_KEY_LEFT :    // Rotate on x axis
		horizAngle += 0.1;
		break;
	case GLUT_KEY_RIGHT :	// Rotate on x axis (opposite)
		horizAngle -= 0.1;
		break;
	case GLUT_KEY_UP :		// Rotate on y axis 
		vertAngle += 0.1;
		break;
	case GLUT_KEY_DOWN :	// Rotate on y axis (opposite)
		vertAngle -= 0.1;
		break;
	}



	// look at 2-d/3-d transformations of models for possible transformations of camera, maybe they also apply?
	glutPostRedisplay();		// Redraw the scene
}


void idleFunc()
{
	if(camera.getState() == Camera::Idle){
		if(!cameraCommands.empty()){
			Command tempCommand = cameraCommands.front();
			cameraCommands.pop();

			if(tempCommand.execute()){//repeat command if required
				cameraCommands.push(tempCommand);
			}
		}
	}

	for(int i = 0; i < robotCommands.size(); ++i)
	{
		if(robots[i].getState() == Model::Idle){
			if(!robotCommands[i].empty()){
				Command tempCommand = robotCommands[i].front();
				robotCommands[i].pop();

				if(tempCommand.execute()){//repeat command if required
					robotCommands[i].push(tempCommand);
				}
			}
		}
	}

	camera.idle();

	for(int i = 0; i < robots.size(); ++i){
		robots[i].idle();
	}

	//Rotate Skybox
	if ( skyboxRotate > 360.0 ) {
		skyboxRotate -= 360.0*floor(skyboxRotate/360.0);   // Don't allow overflow
	}

	skyboxRotate += SKYBOX_ROTATE_SPEED;	

	//Particle System
	particleSys.updateParticles();

	glutPostRedisplay();

}


int main(int argc, char** argv)
{
	// set window values
	win.width = 1600;
	win.height = 1000;
	win.title = "Pixr - Robot Siege";
	win.field_of_view_angle = 45;
	win.z_near = 1.0f;
	win.z_far = 9000.0f;



	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);		// Setup display mode to double buffer and RGB color
	glutInitWindowSize (win.width,win.height);						// Set the screen size
	glutCreateWindow(win.title);	
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	//glutReshapeFunc(reshape);		
	glutDisplayFunc(display);

	Sunlight();

	glutIdleFunc(idleFunc);
	glutKeyboardFunc(keyboard);		// set window's key callback 
	glutSpecialFunc(specialKey);	// set window's to specialKey callback
	init ();
	glutMainLoop();
	return 0;
}

// Functions to load RAW files
// We did not write the following functions.
// They are from the OpenGL tutorials at http://www.swiftless.com
GLuint LoadTextureRAW( const char * filename, int width, int height )
{
	GLuint texture;
	unsigned char * data;
	FILE * file;
	file = fopen( filename, "rb" );
	if ( file == NULL ) return 0;
	data = (unsigned char *)malloc( width * height * 3 );
	fread( data, width * height * 3, 1, file );
	fclose( file );
	glGenTextures(1, &texture );
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
	free( data );
	return texture;
}

void FreeTexture( GLuint texture )
{
	glDeleteTextures( 1, &texture );
}
