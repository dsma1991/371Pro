#include "Model.h"
#include "imageloader.h"

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
double distance = 150;
double vertAngle = 3*PI/4, horizAngle = PI/2;

GLUquadricObj * quadratic;
GLuint _skyboxTexture1;
float skyboxSize = 4000.0f;

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

	Image* skyboxTexture = loadBMP("starrySky.bmp");
	_skyboxTexture1 = loadTexture(skyboxTexture);
	delete(skyboxTexture);
}

void drawSkybox(){
	glPushMatrix();
		glPushAttrib(GL_ENABLE_BIT);
		glEnable(GL_TEXTURE_2D);
		glDisable(GL_DEPTH_TEST);
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
	
	   // Restore enable bits and matrix
		glPopAttrib();
	glPopMatrix();
}
Model temp = Model(0, 0, 0);
void display(void)
{	
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glLoadIdentity();
	gluLookAt(eyeX,eyeY,eyeZ,centerX,centerY,centerZ,0,1,0);
	//gluLookAt(0, 0, 50, 0, 0, 0, 0, 1, 0); //using this to test my stuff -Arteum

	temp.moveTo(20, 50, -20);

	glPushMatrix();
	//glColor3f(1.0f, 0.0f, 0.0f);
	drawSkybox();
	//glutSolidCube(20);
	glPopMatrix();

	glPushMatrix();
	glTranslated(20, 50, -20);
	glutSolidCube(5);
	glPopMatrix();
	temp.draw();
		
	glPopMatrix();
	
	

	glFlush();
	glutSwapBuffers();
}


void keyboard (unsigned char key, int x, int y)
{
	switch (key)
	{
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
	// Limiting camera movement
	if(distance < MIN_DISTANCE)
		distance = MIN_DISTANCE;
	else if(distance > MAX_DISTANCE)
		distance = MAX_DISTANCE;
	if(horizAngle > PI)
		horizAngle -= 2 * PI;
	else if(horizAngle < -PI)
		horizAngle += 2 * PI;
	if(vertAngle > PI - 0.2)
		vertAngle = PI - 0.2;
	else if(vertAngle < 0.2)
		vertAngle = 0.2;
	eyeX = distance * sin(vertAngle) * cos(horizAngle) + centerX;
	eyeZ = distance * sin(vertAngle) * sin(horizAngle) + centerZ;
	eyeY = distance * -cos(vertAngle);

	glutPostRedisplay();
	
}


int main(int argc, char** argv)
{
	// set window values
	win.width = 1600;
	win.height = 1000;
	win.title = "Robot Siege";
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
	/*glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat ambient[] = {1.0, 2.0, 3.0, 1.0};
	glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);*/

	glutIdleFunc(idleFunc);
	glutKeyboardFunc(keyboard);		// set window's key callback 
	glutSpecialFunc(specialKey);	// set window's to specialKey callback
	init ();
	glutMainLoop();
	return 0;
}