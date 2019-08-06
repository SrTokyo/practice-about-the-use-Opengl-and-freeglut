#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

using namespace std;

//Point class for taking the points
class Point {
public:
	float x, y, z;
	void setxyz(float x2, float y2, float z2)
	{
		x = x2; y = y2; z = z2;
	}
	//operator overloading for '=' sign
	const Point & operator=(const Point &rPoint)
	{
		x = rPoint.x;
		y = rPoint.y;
		z = rPoint.z;
		return *this;
	}

};

Point abc[20];
int SCREEN_HEIGHT = 500;
int points = 0;
int clicks = 4;
float nx;
float ny;


int factorial(int n)
{
	if (n <= 1)
		return(1);
	else
		n = n * factorial(n - 1);
	return n;
}

float binomial_coff(float n, float k)
{
	float ans;
	ans = factorial(n) / (factorial(k)*factorial(n - k));
	return ans;
}


void drawDot(float x, float y, float z) {
	glBegin(GL_POINTS);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(x, y, z);
	glEnd();
	glFlush();
}

void drawLine(Point p1, Point p2) {
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(p1.x, p1.y, p1.z);
	glVertex3f(p2.x, p2.y, p2.z);
	glEnd();
	glFlush();
}


Point drawBezier(Point PT[], double t) {
	Point P;
	P.x = pow((1 - t), 3) * PT[0].x + 3 * t * pow((1 - t), 2) * PT[1].x + 3 * (1 - t) * pow(t, 2)* PT[2].x + pow(t, 3)* PT[3].x;
	P.y = pow((1 - t), 3) * PT[0].y + 3 * t * pow((1 - t), 2) * PT[1].y + 3 * (1 - t) * pow(t, 2)* PT[2].y + pow(t, 3)* PT[3].y;

	return P;
}

Point drawBezierGeneralized(Point PT[], double t) {
	Point P;
	P.x = 0; P.y = 0;
	for (int i = 0; i < clicks; i++)
	{
		P.x = P.x + binomial_coff((float)(clicks - 1), (float)i) * pow(t, (double)i) * pow((1 - t), (clicks - 1 - i)) * PT[i].x;
		P.y = P.y + binomial_coff((float)(clicks - 1), (float)i) * pow(t, (double)i) * pow((1 - t), (clicks - 1 - i)) * PT[i].y;
	}
	//cout << P.x << endl << P.y;
	//cout << endl << endl;
	return P;
}

void drawCube() {
	//glBegin(GL_QUADS);

	//glColor3f(1.0, 0.0, 0.0);     glVertex3f(0.5, -0.5,0);      // P1 es rojo
	//glColor3f(0.0, 1.0, 0.0);     glVertex3f(0.5, 0.5, 0);      // P2 es verde
	//glColor3f(0.0, 0.0, 1.0);     glVertex3f(-0.5, 0.5, 0);      // P3 es azul
	//glColor3f(1.0, 0.0, 1.0);     glVertex3f(-0.5, -0.5, 0);	 //

	//glEnd();
	glBegin(GL_LINES);

	float l = 250.0 / 500.0;
	glColor3f(1.0, 0.0, 0.0);     glVertex3f(0, 0, 0);      // P1 es rojo
	glColor3f(0.0, 1.0, 0.0);     glVertex3f(l,l, 0);      // P2 es verde


	glEnd();

	glFlush();
}

void myMouse(int button, int state, int x, int y) {
	// If left button was clicked
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		// Store where mouse was clicked, Y is backwards.
		if (x > 250)
			nx = x / -500.00000;
		else
			nx = x / 500.00000;
		if(y>250)
			ny = y / -500.0000;
		else
			ny = y / 500.00000;
		abc[points].setxyz((float)nx, (float)ny, 0);
		points++;
		// Draw the red  dot.
		drawDot(nx, ny,0);


		// If (click-amout) points are drawn do the curve.
		if (points == clicks)
		{
			glColor3f(0.2, 1.0, 0.0);
			// Drawing the control lines
			for (int k = 0; k < clicks - 1; k++)
				drawLine(abc[k], abc[k + 1]);

			Point p1 = abc[0];
			/* Draw each segment of the curve.Make t increment in smaller amounts for a more detailed curve.*/
			for (double t = 0.0; t <= 1.0; t += 0.02)
			{
				Point p2 = drawBezierGeneralized(abc, t);
				//cout << p1.x << "  ,  " << p1.y << endl;
				//cout << p2.x << "  ,  " << p2.y << endl;
				//cout << endl;
				drawLine(p1, p2);
				p1 = p2;
			}
			glColor3f(1.0, 0.0, 0.0);

			points = 0;
		}
	}
}


void initGL() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClearDepth(1.0f);                   // Set background depth to farthest
	glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
	glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
	glShadeModel(GL_SMOOTH);   // Enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}


void Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

	// Render a color-cube consisting of 6 quads with different colors
	glLoadIdentity();                 // Reset the model-view matrix
	drawCube();
	glFlush();
	glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
	if (height == 0) height = 1;                // To prevent divide by 0
	GLfloat aspect = (GLfloat)width / (GLfloat)height;

	// Set the viewport to cover the new window
	glViewport(0, 0, width, height);

	// Set the aspect ratio of the clipping volume to match the viewport
	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();             // Reset
	// Enable perspective projection with fovy, aspect, zNear and zFar
	gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB| GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Bezier Curve");
	glEnable(GL_DEPTH_TEST);
	glutMouseFunc(myMouse);
	glutDisplayFunc(Display);
	initGL();
	glutMainLoop();

	return 0;
}