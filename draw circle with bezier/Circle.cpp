#include "glut.h"
#include "math.h"
#include <iostream>

using namespace std;

struct PNode
{
	double x;
	double y;
};
typedef struct PNode Point;

Point control[4][4];
void init()
{
	control[0][0].x = 0;
	control[0][0].y = 1;
	control[0][1].x = 0.5;
	control[0][1].y = 1;
	control[0][2].x = 1;
	control[0][2].y = 0.5;
	control[0][3].x = 1;
	control[0][3].y = 0;

	control[1][0].x = 1;
	control[1][0].y = 0;
	control[1][1].x = 1;
	control[1][1].y = -0.5;
	control[1][2].x = 0.5;
	control[1][2].y = -1;
	control[1][3].x = 0;
	control[1][3].y = -1;

	control[2][0].x = 0;
	control[2][0].y = -1;
	control[2][1].x = -0.5;
	control[2][1].y = -1;
	control[2][2].x = -1;
	control[2][2].y = -0.5;
	control[2][3].x = -1;
	control[2][3].y = 0;

	control[3][0].x = -1;
	control[3][0].y = 0;
	control[3][1].x = -1;
	control[3][1].y = 0.5;
	control[3][2].x = -0.5;
	control[3][2].y = 1;
	control[3][3].x = 0;
	control[3][3].y = 1;
}



Point sumBwp(double w, double t, Point control[])
{
	double x = 0;
	double y = 0;
	x = powl(1 - t, 3) * control[0].x + 3 * t * powl(1 - t, 2) * control[1].x * w + 3 * powl(t, 2) * (1 - t) * control[2].x * w + powl(t, 3) * control[3].x;
	y = powl(1 - t, 3) * control[0].y + 3 * t * powl(1 - t, 2) * control[1].y * w + 3 * powl(t, 2) * (1 - t) * control[2].y * w + powl(t, 3) * control[3].y;
	Point res;
	res.x = x;
	res.y = y;
	return res;
}

double sumBw(double w, double t)
{
	double res = 0;
	res = powl(1 - t, 3) + 3 * t * powl(1 - t, 2) * w + 3 * powl(t, 2) * (1 - t) * w + powl(t, 3);
	return res;
}

Point pointinBezier(double w, double t, Point control[])
{
	Point res;
	Point p1;
	double sb;
	p1 = sumBwp(w, t, control);
	sb = sumBw(w, t);

	res.x = p1.x / sb;
	res.y = p1.y / sb;
	return res;
}

void drawcircle(double w, Point control[])
{
	glBegin(GL_LINE_STRIP);
	glColor3f(1.0f, 0.0f, 0.0f);
	for (double t = 0; t <= 1; t += 0.1)
	{
		Point p = pointinBezier(w, t, control);
		glVertex2d(p.x, p.y);
	}
	glEnd();
}

void reshape(int width, int height)
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	glOrtho(-4, 4, -4, 4, 0, 100);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

void redraw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glPushMatrix();
	drawcircle(1.610895, control[0]);
	glPopMatrix();
	glPushMatrix();
	drawcircle(1.610895, control[1]);
	glPopMatrix();
	glPushMatrix();
	drawcircle(1.610895, control[2]);
	glPopMatrix();
	glPushMatrix();
	drawcircle(1.610895, control[3]);
	glPopMatrix();

	glutSwapBuffers();
}

void idle()
{
	glutPostRedisplay();
}
int main(int argc, char *argv[])
{
	
	init();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(300, 300);
	glutInitWindowSize(400, 400);  
	glutCreateWindow("Bezier");
	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	glutMainLoop();

	return 0;
}