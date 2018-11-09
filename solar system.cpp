#include"glut.h"
#include"stdlib.h"
#include"math.h"

static int time = 0;

const GLfloat pi = 3.1415926536f;
const int point = 100;
void drawCircle(float radius)
{
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < point; i++)
	{
		glVertex3f(radius * cos(2 * pi / point * i), radius * sin(2 * pi / point * i), 0.0);
	}
	glEnd();
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	glPushMatrix();
	glRotatef((GLfloat)time/50, 0.0, 0.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glutWireSphere(1.0, 20, 20);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.6, 0.5, 0.4);
	glVertex3d(0.0, 0.0, 2.0);
	glVertex3d(0.0, 0.0, -2.0);
	glEnd();
	drawCircle(2.121);
	glPopMatrix();//draw sun

	glPushMatrix();
	glRotatef((GLfloat)time / 10, 0.0, 0.0, 1.0);
	glTranslatef(1.5, 1.5, 0.0);
	glRotated(30, 0, 1, 0);
	glRotatef((GLfloat)time / 10, 0.0, 0.0, 1.0);
	glColor3f(0.0, 0.0, 1.0);
	glutWireSphere(0.3, 20, 20);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.6, 0.5, 0.4);
	glVertex3d(0.0, 0.0, 1.0);
	glVertex3d(0.0, 0.0, -1.0);
	glEnd();
	drawCircle(0.566);
	glPopMatrix();//draw earth

	glPushMatrix();
	glRotatef((GLfloat)time / 10, 0.0, 0.0, 1.0);
	glTranslatef(1.5, 1.5, 0.0);
	glRotated(30, 0, 1, 0);
	glRotatef((GLfloat)time / 10, 0.0, 0.0, 1.0);
	glTranslatef(0.4, 0.4, 0.0);
	glColor3f(1.0, 1.0, 0.0);
	glutWireSphere(0.1, 10, 10);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.6, 0.5, 0.4);
	glVertex3d(0.0, 0.0, 0.5);
	glVertex3d(0.0, 0.0, -0.5);
	glEnd();
	glPopMatrix();

	glutSwapBuffers();
	time++;
}

void myReshape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);

	if (w <= h)
		glOrtho(-1.0, 1.5, -1.5*(GLfloat)h / (GLfloat)w, 1.5*(GLfloat)h / (GLfloat)w, -1.0, 1.0);
	else
		glOrtho(1.5*(GLfloat)w / (GLfloat)h, 1.5*(GLfloat)w / (GLfloat)h, -1.0, 1.5, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
}


int main(int argc, char * argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(900, 600);
	int windowHandle
		= glutCreateWindow("Solar System");

	glutDisplayFunc(display);
	glutReshapeFunc(myReshape);
	glutIdleFunc(display);
	glutMainLoop();

	return 0;
}
