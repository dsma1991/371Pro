#include <stdlib.h>
#include <GL/glut.h>   
#include <math.h>

typedef struct {
	int width;
	int height;
	char* title;

	float field_of_view_angle;
	float z_near;
	float z_far;
} glutWindow;

glutWindow win;

const double PI  = 3.141592653589793238463;
const int MIN_DISTANCE = 0, MAX_DISTANCE = 500;

double eyeX, eyeY, eyeZ, centerX = 50 , centerY = 0, centerZ = 50;
double distance = 150;
double vertAngle = 3*PI/4, horizAngle = PI/2;

GLUquadricObj * quadratic;

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


}

void display(void)
{	
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glLoadIdentity();
	gluLookAt(eyeX,eyeY,eyeZ,centerX,centerY,centerZ,0,1,0);

	glutSolidCube(20);

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
	win.width = 640;
	win.height = 480;
	win.title = "Da project is here!!!11!!!one!!!1!!";
	win.field_of_view_angle = 45;
	win.z_near = 1.0f;
	win.z_far = 500.0f;

	

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