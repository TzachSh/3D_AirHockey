// Created by Tzachi Sheratzky //

#include<stdio.h>
#include<math.h>
#include"GL/glut.h" 

#define N 2

//Variables to control the position of the camera and points
int rot = 0, points = 0, rotY = 0, flagMoving = 0;
// Strucs for defining cubes and sticks
typedef struct {
	float x, y, z, r, g, b;
	int FlagZ, MovZ;
}Stick;
typedef struct {
	float x, y, z, r, g, b, v;
	int Status, FlagX, FlagZ, MovX, MovZ, StickIndex;
}Cube;
// Declaration for the objects
Cube C[N];
Stick S[N];
//If both cubes are out the func will return true
int CheckEnd()
{
	return C[0].Status == 0 && C[1].Status == 0;
}
//Showing scores
void showScore()
{
	char strScore[20] = "0";
	sprintf(strScore, "Score: %d", points);
	glColor3f(0.0, 1.0, 0.0);
	glRasterPos3f(4.5, 8.5, 0);
	char *str = strScore;
	do {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *str);
	} while (*(++str));


}
//Check if any of the cubes are colliding with one of the sticks
void CheckStickCollision(int iCube) {

	for (int i = 0; i < N; i++)
		//check the X axis
		if (C[iCube].StickIndex != i) // If we still didn't hit the next stick
			if (fabs(S[i].x - C[iCube].x) <= 0.5)
			{
				//check the Z axis
				if (fabs(S[i].z - C[iCube].z) <= 2)
				{
					C[iCube].MovX = !C[iCube].MovX;
					C[iCube].StickIndex = i; // Update the current stick's hit
					points++;
					C[i].v += 0.001;
				}
			}
}
//Drawing the stick object
void drawStick()
{
	glBegin(GL_QUADS);
	// Front	
	glNormal3f(0, 0, 0.5);
	glVertex3f(-0.25, 0, 2);
	glVertex3f(-0.25, 0.5, 2);
	glVertex3f(0.25, 0.5, 2);
	glVertex3f(0.25, 0, 2);

	// Back
	glNormal3f(0, 0, -0.5);
	glVertex3f(-0.25, 0, -2);
	glVertex3f(0.25, 0, -2);
	glVertex3f(0.25, 0.5, -2);
	glVertex3f(-0.25, 0.5, -2);

	// Left side
	glNormal3f(-0.25, 0, 0);
	glVertex3f(-0.25, 0, 2);
	glVertex3f(-0.25, 0.5, 2);
	glVertex3f(-0.25, 0.5, -2);
	glVertex3f(-0.25, 0, -2);

	// Right side
	glNormal3f(0.25, 0, 0);
	glVertex3f(0.25, 0, 2);
	glVertex3f(0.25, 0, -2);
	glVertex3f(0.25, 0.5, -2);
	glVertex3f(0.25, 0.5, 2);

	// Top side
	glNormal3f(0.5, 0, 0);
	glVertex3f(0.25, 0.5, 2);
	glVertex3f(0.25, 0.5, -2);
	glVertex3f(-0.25, 0.5, -2);
	glVertex3f(-0.25, 0.5, 2);

	glEnd();
}
//Drawing the cube object
void drawCube() {
	glBegin(GL_QUADS);
	// Front	
	glNormal3f(0, 0, 0.5);
	glVertex3f(-0.25, 0, 0.25);
	glVertex3f(-0.25, 0.5, 0.25);
	glVertex3f(0.25, 0.5, 0.25);
	glVertex3f(0.25, 0, 0.25);

	// Back
	glNormal3f(0, 0, -0.5);
	glVertex3f(-0.25, 0, -0.25);
	glVertex3f(0.25, 0, -0.25);
	glVertex3f(0.25, 0.5, -0.25);
	glVertex3f(-0.25, 0.5, -0.25);

	// Left side
	glNormal3f(-0.25, 0, 0);
	glVertex3f(-0.25, 0, 0.25);
	glVertex3f(-0.25, 0.5, 0.25);
	glVertex3f(-0.25, 0.5, -0.25);
	glVertex3f(-0.25, 0, -0.25);

	// Right side
	glNormal3f(0.5, 0, 0);
	glVertex3f(0.25, 0, 0.25);
	glVertex3f(0.25, 0, -0.25);
	glVertex3f(0.25, 0.5, -0.25);
	glVertex3f(0.25, 0.5, 0.25);

	// Top side
	glNormal3f(0.5, 0, 0);
	glVertex3f(0.25, 0.5, 0.25);
	glVertex3f(0.25, 0.5, -0.25);
	glVertex3f(-0.25, 0.5, -0.25);
	glVertex3f(-0.25, 0.5, 0.25);

	glEnd();
}
//Init sticks
void initSticks() {

	S[0].x = -5;
	S[1].x = 5;
	S[0].y = S[1].y = S[0].z = S[1].z = 0;
	S[0].b = S[0].r = S[1].b = S[1].r = S[1].g = S[0].g = 0;
	S[0].MovZ = S[1].MovZ = -1;
	S[0].FlagZ = S[1].FlagZ = 0;
}
//Init cubes
void initCubes()
{
	C[0].x = -2;
	C[0].y = 0;
	C[0].z = 2;
	C[0].r = 1.0;
	C[0].g = C[0].b = 0.0;
	C[0].MovX = C[0].MovZ = 1;
	C[0].FlagZ = 1;
	C[0].Status = C[0].FlagX = 1;
	C[0].v = C[1].v = 0.001;
	C[1].MovX = 0;
	C[1].StickIndex = 1;
	C[1].x = 2;
	C[1].y = 0;
	C[1].z = -2;
	C[1].r = 0.6;
	C[1].g = 0.0;
	C[1].b = 0.6;
	C[1].MovZ = C[1].FlagZ = 1;
	C[1].Status = C[1].FlagX = 1;
}
//Keboard handling
void keyboard(unsigned char key, int x, int y)
{
	if (key == 27) exit(1);
	if (key == 'o')
	{
		rot += 2;
		rot %= 360;
	}
	if (key == 'p') {
		rot -= 2;
		rot %= 360;
	}
	if (key == 'k')
	{
		rotY += 2;
		rot %= 360;
	}
	if (key == 'l') {
		rotY -= 2;
		rot %= 360;
	}
	switch (key)
	{
	case ' ':
		flagMoving = !flagMoving;
		break;
	case 'w':
		if (!flagMoving) {
			S[0].FlagZ = 1;
			S[0].MovZ = 1;
		}
		break;
	case 's':
		if (!flagMoving) {
			S[0].FlagZ = 1;
			S[0].MovZ = 0;
		}
		break;
	case 'y':
		if (!flagMoving) {
			S[1].FlagZ = 1;
			S[1].MovZ = 0;
		}
		break;
	case 'h':
		if (!flagMoving) {
			S[1].FlagZ = 1;
			S[1].MovZ = 1;
		}
		break;
	default:
		break;
	}

	glutPostRedisplay();
}
//Draw Bench floor
void drawFloor() {
	glBegin(GL_QUADS);
	glColor3f(0.2, 0.2, 0.8);
	glNormal3f(0, 1, 0);	// normal straight up
	glVertex3f(-5, 0, -5);
	glVertex3f(5, 0, -5);
	glVertex3f(5, 0, 5);
	glVertex3f(-5, 0, 5);
	glEnd();
}
//Show cubes positions over the table
void showCubes()
{
	for (int i = 0; i < N; i++)
	{
		glColor3f(C[i].r, C[i].g, C[i].b);
		glTranslatef(C[i].x, C[i].y, C[i].z);
		drawCube();
		glTranslatef(-C[i].x, -C[i].y, -C[i].z);
	}
}
//Show sticks positions over the table
void showStickes()
{
	for (int i = 0; i < N; i++)
	{
		glColor3f(S[i].r, S[i].g, S[i].b);
		glTranslatef(S[i].x, S[i].y, S[i].z);
		drawStick();
		glTranslatef(-S[i].x, -S[i].y, -S[i].z);
	}
}
//Move cube all over the table
void moveCube()
{
	for (int i = 0; i < N; i++)
	{
		glColor3f(C[i].r, C[i].g, C[i].b);
		glTranslatef(C[i].x, C[i].y, C[i].z);
		drawCube();
		glTranslatef(-C[i].x, -C[i].y, -C[i].z);

	}

}
//Draw leg of a table
void drawLeg()
{
	/************************************************************/
	glBegin(GL_QUADS);
	// Front
	glColor3f(0.3, 0.5, 0.4);
	glNormal3f(0, 0, 1);
	glVertex3f(-1, 0, 1);
	glVertex3f(-1, 2, 1);
	glVertex3f(1, 2, 1);
	glVertex3f(1, 0, 1);

	// Back
	glNormal3f(0, 0, -1);
	glVertex3f(-1, 0, -1);
	glVertex3f(-1, 2, -1);
	glVertex3f(1, 2, -1);
	glVertex3f(1, 0, -1);

	// Left side
	glNormal3f(-1, 0, 0);
	glVertex3f(-1, 0, 1);
	glVertex3f(-1, 2, 1);
	glVertex3f(-1, 2, -1);
	glVertex3f(-1, 0, -1);

	// Right side
	glNormal3f(1, 0, 0);
	glVertex3f(1, 0, 1);
	glVertex3f(1, 0, -1);
	glVertex3f(1, 2, -1);
	glVertex3f(1, 2, 1);
	glEnd();

}
//Draw a limit for the side of the table
void drawBlock()
{
	glBegin(GL_QUADS);
	// Front
	glColor3f(0.3, 0.5, 0.4);
	glNormal3f(0, 0, 1);
	glVertex3f(-5, 0, 0.5);
	glVertex3f(-5, 0.5, 0.5);
	glVertex3f(5, 0.5, 0.5);
	glVertex3f(5, 0, 0.5);

	//Top 
	glColor3f(0.3, 0.5, 0.4);
	glNormal3f(0, 1, 0);
	glVertex3f(-5, 0.5, 0.5);
	glVertex3f(-5, 0.5, -0.5);
	glVertex3f(5, 0.5, -0.5);
	glVertex3f(5, 0.5, 0.5);

	// Back
	glNormal3f(0, 0, -0.5);
	glVertex3f(-5, 0, -0.5);
	glVertex3f(5, 0, -0.5);
	glVertex3f(5, 0.5, -0.5);
	glVertex3f(-5, 0.5, -0.5);

	// Left side
	glNormal3f(-1, 0, 0);
	glVertex3f(-5, 0, 0.5);
	glVertex3f(-5, 0.5, 0.5);
	glVertex3f(-5, 0.5, -0.5);
	glVertex3f(-5, 0, -0.5);

	// Right side
	glNormal3f(1, 0, 0);
	glVertex3f(5, 0, 0.5);
	glVertex3f(5, 0, -0.5);
	glVertex3f(5, 0.5, -0.5);
	glVertex3f(5, 0.5, 0.5);
	glEnd();
}
//Draw the bench object
void drawBench()
{

	glTranslatef(-4, -2, 4);
	drawLeg();
	glTranslatef(0, 0, -8);
	drawLeg();
	glTranslatef(8, 0, 0);
	drawLeg();
	glTranslatef(0, 0, 8);
	drawLeg();
	glTranslatef(-4, 2, -4);

	glTranslatef(0, 0, -4.5);
	drawBlock();
	glTranslatef(0, 0, 9);
	drawBlock();
	glTranslatef(0, 0, -4.5);
}
//Draw the floor area under the table
void drawBase()
{
	glBegin(GL_QUADS);
	glColor3f(0.6, 0.5, 0.0);
	glNormal3f(0, 1, 0);	// normal straight up
	glVertex3f(-7, -2, -7);
	glVertex3f(7, -2, -7);
	glVertex3f(7, -2, 7);
	glVertex3f(-7, -2, 7);
	glEnd();
}
//Configure lights
void Lightning()
{
	// Lighting parameters

	GLfloat mat_ambdif[] = { 0.2, 0.2, 0.2, 0.2 };
	GLfloat mat_diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 1.0 };
	GLfloat light_position[] = { 20.0, 5.0, 3.0, 1.0 };
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambdif);	// set both amb and diff components
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);		// set specular
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);		// set shininess
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);		// set light "position", in this case direction
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);		// active material changes by glColor3f(..)


	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_DEPTH_TEST);
}
//Draw all the objects 
void draw()
{
	glClear(GL_COLOR_BUFFER_BIT |
		GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0, 0, -17);
	showScore();
	glRotatef(90, 1, 0, 0);
	glRotatef(rot, 1, 0, 0);
	glRotatef(rotY, 0, 1, 0);
	/************************************************************/
	drawFloor();
	Lightning();
	drawBase();
	showCubes();
	showStickes();
	moveCube();
	drawBench();
	glutSwapBuffers();			// display the output

}
// Check if the cubes hit each other
void CheckHit(int iHit)
{
	for (int i = 0; i < N; i++)
		if (i != iHit)
			//check the X axis
			if (fabs(C[i].x - C[iHit].x) <= 0.5)
			{
				//check the Z axis
				if (fabs(C[i].z - C[iHit].z) <= 0.5)
				{
					C[i].MovX = !C[i].MovX;
					C[i].MovZ = !C[i].MovZ;
					C[i].StickIndex = !C[i].StickIndex;
				}
			}
}
//Make the cube fall out of the game to the base floor
void Fall(int iFall)
{

	if (C[iFall].y >= -2) {
		C[iFall].y -= 0.001;
	}
	else
		C[iFall].Status = 0;

}
//Turn off the lights
void EndLight()
{
	// Lighting parameters

	GLfloat mat_ambdif[] = { 0.0, 0.0, 0.0, 0.0 };
	GLfloat mat_diffuseLight[] = { 0.0f, 0.0f, 0.0, 0.0f };
	GLfloat mat_specular[] = { 0.0, 0.0, 0.0, 0.0 };
	GLfloat mat_shininess[] = { 0.0 };
	GLfloat light_position[] = { 0.0, 0.0, 0.0, 0.0 };
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambdif);	// set both amb and diff components
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);		// set specular
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);		// set shininess
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);		// set light "position", in this case direction
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);		// active material changes by glColor3f(..)


	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_DEPTH_TEST);
}
//Game role 
void Idle(void)
{

	if (CheckEnd()) {
		EndLight();
		S[0].x = S[1].x = -100;
	}
	else
	{
		if (flagMoving == 0)
		{
			if (S[0].FlagZ && S[0].MovZ && S[0].z >= -1.95)
				S[0].z -= 0.003;
			if (!S[0].MovZ && S[0].z <= 1.95)
				S[0].z += 0.003;

			if (S[1].FlagZ && S[1].MovZ && S[1].z <= 1.95)
				S[1].z += 0.003;
			if (S[1].FlagZ && !S[1].MovZ && S[1].z >= -1.95)
				S[1].z -= 0.003;
		}
		else
			for (int i = 0; i < 2; i++)
			{
				if (C[i].Status == 1)
				{
					if (C[i].MovZ == 0 && S[!C[i].StickIndex].z >= -1.95)
						S[!C[i].StickIndex].z -= C[i].v;
					if (C[i].MovZ == 1 && S[!C[i].StickIndex].z <= 1.95)
						S[!C[i].StickIndex].z += C[i].v;
				}
			}
		for (int i = 0; i < N; i++)
			if (C[i].Status)
			{
				CheckHit(i);
				CheckStickCollision(i);
				if (C[i].x >= 5.5)
				{
					C[i].v = 0;
					Fall(i);
				}

				else if (C[i].x <= -5.5)
				{
					Fall(i);
					C[i].v = 0;
				}

				else if (C[i].FlagX)
				{
					if (C[i].MovX && C[i].x <= 5.5)	 C[i].x += C[i].v;
					else if (!C[i].MovX && C[i].x >= -5.5)	C[i].x -= C[i].v;
				}

				if (C[i].FlagZ)
				{
					if (C[i].z <= 3.75 && C[i].MovZ) {
						C[i].z += C[i].v;
						if (C[i].z >= 3.75) C[i].MovZ = 0;
					}
					if (!C[i].MovZ && C[i].z >= -3.75) {
						C[i].z -= C[i].v;
						if (C[i].z <= -3.75) C[i].MovZ = 1;
					}
				}
			}
	}
	draw();
}
// Set OpenGL parameters
void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1.0, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);


}
int main(int argc, char *argv[])

{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);	// RGB display, double-buffered, with Z-Buffer
	glutInitWindowSize(500, 500);					// 500 x 500 pixels
	glutCreateWindow("3D");
	initCubes();
	initSticks();
	glutDisplayFunc(draw);						// Set the display function
	glutKeyboardFunc(keyboard);					// Set the keyboard function
	glutIdleFunc(Idle);
	init();
	glutMainLoop();							// Start the main event loop
}