/*********
CTIS164 - Template Source Program
----------
STUDENT :M. Kasım Varol
SECTION :1
HOMEWORK:2
----------
PROBLEMS: 
*********/

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 700

#define TIMER_PERIOD  25 // Period for the timer.

#define D2R 0.0174532

/* Global Variables for Template File */
bool up = false, down = false, right = false, left = false, activeTimer=false, weaponis=false;
int  winWidth, winHeight, movelimit = 0, lastpoints = 0, points = 0, totalrockets = 0,// current Window width and height
counter = 0, movesY[4] = { 0 }, movesX[4], weaponx = 0, weapony=0, burst = 0;
bool hitted[4] = { 0 };

void initializeGlobals()
{
	counter = 0;
	totalrockets = 0;
	points = 0;
	lastpoints = 0;
	burst = 0;
	weapony = 0;
	for (int i = 0; i < 4; i++){
		movesY[i] = -WINDOW_HEIGHT / 2 - i * 180;
		movesX[i] = rand() % 200 + 50;
	}

}

						  //
						  // to draw circle, center at (x,y)
						  // radius r
						  //
void circle(int x, int y, int r)
{
#define PI 3.1415
	float angle;
	glBegin(GL_POLYGON);
	for (int i = 0; i < 100; i++)
	{
		angle = 2 * PI*i / 100;
		glVertex2f(x + r*cos(angle), y + r*sin(angle));
	}
	glEnd();
}

void circle_wire(int x, int y, int r)
{
#define PI 3.1415
	float angle;

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 100; i++)
	{
		angle = 2 * PI*i / 100;
		glVertex2f(x + r*cos(angle), y + r*sin(angle));
	}
	glEnd();
}

void print(int x, int y, char *string, void *font)
{
	int len, i;

	glRasterPos2f(x, y);
	len = (int)strlen(string);
	for (i = 0; i<len; i++)
	{
		glutBitmapCharacter(font, string[i]);
	}
}

// display text with variables.
// vprint(-winWidth / 2 + 10, winHeight / 2 - 20, GLUT_BITMAP_8_BY_13, "ERROR: %d", numClicks);
void vprint(int x, int y, void *font, char *string, ...)
{
	va_list ap;
	va_start(ap, string);
	char str[1024];
	vsprintf_s(str, string, ap);
	va_end(ap);

	int len, i;
	glRasterPos2f(x, y);
	len = (int)strlen(str);
	for (i = 0; i<len; i++)
	{
		glutBitmapCharacter(font, str[i]);
	}
}

// vprint2(-50, 0, 0.35, "00:%02d", timeCounter);
void vprint2(int x, int y, float size, char *string, ...) {
	va_list ap;
	va_start(ap, string);
	char str[1024];
	vsprintf_s(str, string, ap);
	va_end(ap);
	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(size, size, 1);

	int len, i;
	len = (int)strlen(str);
	for (i = 0; i<len; i++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
	}
	glPopMatrix();
}

//
// To display onto window using OpenGL commands
//
void drawSubmarine(int y)
{
	//body of submarine
	glColor3f(0.7, 0.7, 0.7);
	circle(-330, 0 + y, 30);
	circle(-270, 0 + y, 30);
	glRectf(-330, -30 + y, -270, 30 + y);
	glBegin(GL_TRIANGLES);
	glVertex2f(-330, 30+y);
	glVertex2f(-390, 0+y);
	glVertex2f(-330, -30+y);
	glEnd();
	glRectf(-391, -2 + y, -381, 2 + y);
	//telescope of submarine
	glColor3f(1, 1, 1);
	circle(-286, 51+y, 2);
	glColor3f(0.7, 0.7, 0.7);
	glRectf(-293, 30 + y, -297, 50 + y);
	circle(-295, 51 + y, 2);
	glRectf(-294, 49 + y, -288, 53 + y);
	//propeller of submarine
	glColor3f(0.4, 0.4, 0.4);
	glRectf(-400, -2 + y, -390, 2 + y);
	circle(-395, 7 + y, 5);
	circle(-395, -7 + y, 5);
	//windows of submarine
	glColor3f(0.1, 0.1, 0.1);
	circle(-315, 10 + y, 12);
	circle(-285, 10 + y, 12);
	glColor3f(1, 1, 1);
	circle(-315, 10 + y, 10);
	circle(-285, 10 + y, 10);
	//missile body
	glColor3f(0.4, 0.4, 0.4);
	glRectf(-330, -30 + y, -270, -10 + y);
}
void drawEnemies(int x, int y)
{
	glColor3f(0, 0.2, 0.1);
	circle(0+x, -350+y, 30);
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex2f(0+x, -350+y);
	glVertex2f(30+x, -320+y);
	
	glVertex2f(0 + x, -350 + y);
	glVertex2f(-30 + x, -320 + y);
	
	glVertex2f(0 + x, -350 + y);
	glVertex2f(-30 + x, -380 + y);
	
	glVertex2f(0 + x, -350 + y);
	glVertex2f(30 + x, -380 + y);
	//
	glVertex2f(0 + x, -350 + y);
	glVertex2f(35 + x, -350 + y);

	glVertex2f(0 + x, -350 + y);
	glVertex2f(0 + x, -315 + y);

	glVertex2f(0 + x, -350 + y);
	glVertex2f(-35 + x, -350 + y);

	glVertex2f(0 + x, -350 + y);
	glVertex2f(0 + x, -385 + y);

	glEnd();

}
void drawBullet(int x, int y)
{
	//glRectf(-330, -30 + y, -270, -10 + y);
	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0);
	glVertex2f(-270 + x, -30 + y);
	glVertex2f(-270 + x, -10 + y);
	glVertex2f(-250 + x, -20 + y);
	glEnd();
}
void display() {

	//
	// clear window to black
	//
	glClearColor(0.196078, 0.6, 0.8, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	//submarine
	drawSubmarine(movelimit);
	if(weaponis)
	drawBullet(weaponx, weapony);
	//draw mines
	int i;
	for (i = 0; i < 4; i++) {
		if(hitted[i]!=true)
		drawEnemies(movesX[i], movesY[i]);
	}
	//key board
	glColor3f(0, 0, 0);
	glRectf(-400, -350, 400, -320);
	//info board
	glRectf(300, -350, 400, 350);
	//timeleft
	glColor3f(1, 1, 1);
	vprint(305, 320, GLUT_BITMAP_HELVETICA_12, "Remaining Time");
	vprint(320, 300, GLUT_BITMAP_HELVETICA_18, "%02d", 20-counter/40);
	vprint(305, 280, GLUT_BITMAP_HELVETICA_12, "Total Mines");
	vprint(320, 260, GLUT_BITMAP_HELVETICA_18, "%02d", totalrockets);
	vprint(305, 240, GLUT_BITMAP_HELVETICA_12, "Destroyed Mines");
	vprint(320, 220, GLUT_BITMAP_HELVETICA_18, "%02d",burst);
	vprint(305, 200, GLUT_BITMAP_HELVETICA_12, "Last Points");
	vprint(320, 180, GLUT_BITMAP_HELVETICA_18, "%d", lastpoints);
	vprint(305, 160, GLUT_BITMAP_HELVETICA_12, "Total Points");
	vprint(320, 140, GLUT_BITMAP_HELVETICA_18, "%d", points);
	vprint(-200, -340, GLUT_BITMAP_HELVETICA_18, "Press <SpaceBar to Shoot | Press F1 to stop or restart");
	glutSwapBuffers();

	
}
///
//
// key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
//
void onKeyDown(unsigned char key, int x, int y)
{
	// exit when ESC is pressed.
	if (key == 27)
		exit(0);
	if (key == ' ' && activeTimer && weapony==0) {
		weaponis = true;
		weapony = movelimit;
	}
	// to refresh the window it calls display() function
	glutPostRedisplay();
}

void onKeyUp(unsigned char key, int x, int y)
{
	// exit when ESC is pressed.
	if (key == 27)
		exit(0);

	// to refresh the window it calls display() function
	glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyDown(int key, int x, int y)
{
	// Write your codes here.
	switch (key) {
	case GLUT_KEY_UP: up = true; 
		if(movelimit<=295 && activeTimer)
			movelimit+=6;  break;
	case GLUT_KEY_DOWN: down = true; 
		if (movelimit >= -290 && activeTimer)
			movelimit-=6;  break;
	case GLUT_KEY_LEFT: left = true; break;
	case GLUT_KEY_RIGHT: right = true; break;
	case GLUT_KEY_F1:if((counter/40)<20)
		activeTimer = !activeTimer;
					 else
					 {
						 initializeGlobals();
						 activeTimer = true;
					 }
	}

	// to refresh the window it calls display() function
	glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyUp(int key, int x, int y)
{
	// Write your codes here.
	switch (key) {
	case GLUT_KEY_UP: up = false; break;
	case GLUT_KEY_DOWN: down = false; break;
	case GLUT_KEY_LEFT: left = false; break;
	case GLUT_KEY_RIGHT: right = false; break;
	}

	// to refresh the window it calls display() function
	glutPostRedisplay();
}

//
// When a click occurs in the window,
// It provides which button
// buttons : GLUT_LEFT_BUTTON , GLUT_RIGHT_BUTTON
// states  : GLUT_UP , GLUT_DOWN
// x, y is the coordinate of the point that mouse clicked.
//
void onClick(int button, int stat, int x, int y)
{
	// Write your codes here.



	// to refresh the window it calls display() function
	glutPostRedisplay();
}

//
// This function is called when the window size changes.
// w : is the new width of the window in pixels.
// h : is the new height of the window in pixels.
//
void onResize(int w, int h)
{
	winWidth = w;
	winHeight = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	display(); // refresh window.
}

void onMoveDown(int x, int y) {
	// Write your codes here.



	// to refresh the window it calls display() function   
	glutPostRedisplay();
}

// GLUT to OpenGL coordinate conversion:
//   x2 = x1 - winWidth / 2
//   y2 = winHeight / 2 - y1
void onMove(int x, int y) {
	// Write your codes here.



	// to refresh the window it calls display() function
	glutPostRedisplay();
}


void onTimer(int v) {

	glutTimerFunc(TIMER_PERIOD, onTimer, 0);
	// Write your codes here.
	if (activeTimer)
	{
		counter++;
		for (int i = 0; i < 4; i++) {
			if (movesY[i] == 0)
				totalrockets++;
			if (movesY[i] <= 700)
				movesY[i] += 5;
			else
			{
				movesY[i] = 0;
				movesX[i] = rand() % 200 + 50;
				hitted[i] = false;
			}
			if (hitted[i] == false)
			{
				if (-260 + weaponx <= movesX[i] + 30 && -260 + weaponx >= movesX[i] - 30 && -20 + weapony <= -320 + movesY[i] && -20 + weapony >= -380 + movesY[i])
				{
					burst++;
					hitted[i] = true;
					int distances = (-20 + weapony) - (-350 + movesY[i]);
					if (distances <= 6)
						lastpoints = 5;
					else if (distances <= 12)
						lastpoints = 4;
					else if (distances <= 18)
						lastpoints = 3;
					else if (distances <= 24)
						lastpoints = 2;
					else
						lastpoints = 1;
					points += lastpoints;
					
				}
			}
			
		}
		
	}
	if (weaponis && activeTimer) {
		weaponx += 12;
		if (weaponx >= 550) {
			weaponis = false;
			weaponx = 0;
			weapony = 0;
		}
		if (counter / 40 == 20) {
			activeTimer = false;
		}
	}
	// to refresh the window it calls display() function
	glutPostRedisplay(); // display()

}


void Init() {

	// Smoothing shapes
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void main(int argc, char *argv[]) {
	initializeGlobals();
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("HW-2 KASIM VAROL || Shooting Mines");

	
	glutDisplayFunc(display);
	glutReshapeFunc(onResize);

	//
	// keyboard registration
	//
	glutKeyboardFunc(onKeyDown);
	glutSpecialFunc(onSpecialKeyDown);

	glutKeyboardUpFunc(onKeyUp);
	glutSpecialUpFunc(onSpecialKeyUp);

	//
	// mouse registration
	//
	glutMouseFunc(onClick);
	glutMotionFunc(onMoveDown);
	glutPassiveMotionFunc(onMove);
	glutTimerFunc(TIMER_PERIOD, onTimer, 0);


	Init();

	glutMainLoop();
}