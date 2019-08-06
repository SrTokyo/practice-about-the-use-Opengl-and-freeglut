#include <stdio.h>
#include <stdarg.h>
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <gl/glut.h>
#include <math.h>
#include <time.h>
#include <Windows.h>
#define GL_GLEXT_PROTOTYPES


using namespace std;


//Point class for taking the points
class Point {
public:
	float x, y;
	void setxy(float x2, float y2)
	{
		x = x2; y = y2;
	}
	//operator overloading for '=' sign
	const Point & operator=(const Point &rPoint)
	{
		x = rPoint.x;
		y = rPoint.y;
		return *this;
	}

};

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



int initial_time = time(NULL), final_time;
Point abc[20];
int SCREEN_HEIGHT = 500;
int points = 0;
int clicks = 6;


void myInit() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glPointSize(3);
	glMatrixMode(GL_PROJECTION);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

}

void drawDot(float x, float y) {
	glBegin(GL_POINTS);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(x, y, 0);
	glEnd();
	glFlush();
}

void drawLine(Point p1, Point p2) {
	glBegin(GL_LINES);
	glVertex3f(p1.x, p1.y, 0.0f);
	glVertex3f(p2.x, p2.y, 0.0f);
	glEnd();
	glFlush();
}






Point drawBezierGeneralized(Point PT[], double t) {
	Point P;
	P.x = 0; P.y = 0;
	for (int i = 0; i < clicks; i++)
	{
		P.x = P.x + binomial_coff((float)(clicks - 1), (float)i) * pow(t, (double)i) * pow((1 - t), (clicks - 1 - i)) * PT[i].x;
		P.y = P.y + binomial_coff((float)(clicks - 1), (float)i) * pow(t, (double)i) * pow((1 - t), (clicks - 1 - i)) * PT[i].y;
	}
	return P;
}


double rotate_y = 0;
double rotate_x = 0;
float nx = 0;
float ny = 0;

double t = 0.0;
Point p1 = abc[0];
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glColor3f(0.0, 1.0, 0.0);
	drawDot(nx, ny);
	if (points == clicks) {

		glColor3f(0.2, 1.0, 0.0);
		
		for (int k = 0; k < clicks - 1; k++) {
			drawLine(abc[k], abc[k + 1]);
		}
		
		Point p2 = drawBezierGeneralized(abc, t);
		
		drawLine(p1, p2);
		p1 = p2;
		glPushMatrix();
		glTranslatef(p2.x, p2.y, 0);
		glRotatef(rotate_x, 1.0, 0.0, 0.0);
		glRotatef(rotate_y, 0.0, 1.0, 0.0);
		rotate_x += 0.7;
		glutWireSphere(0.03, 10, 10);
		glPopMatrix();
		if (t >= 1.0) {
			
			points = 0;
			t = 0;
			Point p1 = abc[0];
		}
		if (t <= 1.0) {
			t += 0.02;
		}
		
	}
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}



void myMouse(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		
		if (x > 250) {
			nx = (x / 300.0) - 1.0;
		}
		else {
			nx = (x / 300.0) - 1.0;
		}
		if (y > 250) {
			ny = (y / -300.0) + 1.0;
		}
		else {
			ny = (y / -300.0) + 1.0;
		}

		abc[points].setxy(nx, ny);
		points++;
		cout << x << "  ,  " << y << endl;
	}
}

void specialKeys(int key, int x, int y) {

	//  Flecha derecha: aumentar rotación 5 grados
	if (key == GLUT_KEY_RIGHT)
		rotate_y += 5;

	
	else if (key == GLUT_KEY_LEFT)
		rotate_y -= 5;

	else if (key == GLUT_KEY_UP)
		rotate_x += 5;

	else if (key == GLUT_KEY_DOWN)
		rotate_x -= 5;

	
	glutPostRedisplay();

}


int main(int argc, char *argv[]) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Práctica 2");
	myInit();
	glutMouseFunc(myMouse);
	glutSpecialFunc(specialKeys);
	glutDisplayFunc(display);


	glutMainLoop();

	return 0;
}