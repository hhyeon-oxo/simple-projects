#include "glut.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int joint1 = 0, joint2 = 0;
int light = 0, lonoff = 0;
GLfloat     fovy, nearClip, farClip,
distance,
twistAngle,
elevationAngle,
azimAngle;
GLint     action;
GLdouble    xStart = 0.0, yStart = 0.0;
enum  actions { MOVE_EYE, TWIST_EYE, ZOOM, MOVE_NONE };

void   polarView(GLfloat distance, GLfloat azimuth,
	GLfloat elevation, GLfloat twist)
{
	glTranslatef(0.0, 0.0, -distance);
	glRotatef(-twist, 0.0, 0.0, 1.0);
	glRotatef(elevation, 1.0, 0.0, 0.0);
	glRotatef(azimuth, 0.0, 1.0, 0.0);
}

void init(void)
{
	GLfloat light0_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat light0_diffuse[] = { 0.7, 0.7, 0.7, 0.1 };
	GLfloat light0_specular[] = { 0.7, 0.7, 0.7, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30, 1.0, 3.0, 50.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
}

GLvoid  mouse(GLint button, GLint state, GLint x, GLint y) {
	static GLint buttons_down = 0;
	if (state == GLUT_DOWN) {
		switch (button) {
		case GLUT_LEFT_BUTTON:action = MOVE_EYE; break;
		case GLUT_MIDDLE_BUTTON:action = TWIST_EYE; break;
		case GLUT_RIGHT_BUTTON:action = ZOOM; break;
		}
		xStart = x; yStart = y;
	}
	else {
		if (--buttons_down == 0)  action = MOVE_NONE;
	}
}

GLvoid  motion(GLint x, GLint y) {

	switch (action) {
	case MOVE_EYE:
		azimAngle += (GLdouble)(x - xStart);
		elevationAngle += (GLdouble)(y - yStart);
		break;
	case TWIST_EYE:
		twistAngle = fmod(twistAngle + (x - xStart), 360.0);
		break;
	case ZOOM:
		distance += (GLdouble)(y - yStart) / 10.0;
		break;

	default:
		printf("unknown action %d\n", action);
	}
	xStart = x;    yStart = y;

	glutPostRedisplay();
}

void DrawScene(void)
{
	GLfloat  LightPosition[] = { 0.5f, 0.5f, 0.5f, 1.0 };

	if (lonoff == 1) {
		glPushMatrix();
		glRotatef(light, 1.0, 0.0, 0.0);
		glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
		glTranslatef(0.0, 0.0, 1.5);
		glDisable(GL_LIGHTING);
		glColor3f(0.9, 0.9, 0.9);
		glutWireSphere(0.06, 10, 10); //
		glEnable(GL_LIGHTING);
		glPopMatrix();
	}

	//drawFloor
	// { Front }
	glPushMatrix();
	glTranslatef(-1.0, -1.0, 1.0);
	glRotatef((GLfloat)joint1, -1.0f, 0.0f, 0.0f);

	glTranslatef(1.0, 1.0, -1.0);
	glColor3f(0, 0.3, 0.3);
	glBegin(GL_QUADS);
	glVertex3f(-1.0, 1.0, 1.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(1.0, -1.0, 1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glEnd();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(0.0, 1.3, 0.5);
	glScalef(0.3, 0.3, 0.3);
	tree(3);
	glTranslatef(2.4, 0, -4);
	tree(4);
	glTranslatef(-1.3, 0, 1.8);
	tree(2);
	glTranslatef(-0.6, 0, 3);
	tree(2);
	glTranslatef(-2.6, 0, -4);
	tree(7);
	glTranslatef(0.6, 0, 1.8);
	tree(6);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, -1, 0, 0);
	glTranslatef(0.6, -0.675, -0.2);
	glScalef(0.3, 0.3, 0.3);
	firBuliding();
	glTranslatef(0.6, 0, -1.0);
	firBuliding();
	glTranslatef(-4.5, 0, 0.5);
	firBuliding();
	glTranslatef(0, 0, 3.0);
	firBuliding();
	glTranslatef(4.5, 0, 0);
	firBuliding();
	glScalef(0.5, 0.5, 0.5);
	glTranslatef(-5, 0, -2);
	tree(2);
	glPopMatrix();

	glPopMatrix();

	// { Back }
	glPushMatrix();
	glTranslatef(1.0, -1.0, -1.0);
	glRotatef((GLfloat)joint1, 1.0f, 0.0f, 0.0f);

	glTranslatef(-1.0, 1.0, 1.0);
	glColor3f(0, 0.3, 0.3);
	glBegin(GL_QUADS);
	glVertex3f(1.0, 1.0, -1.0);
	glVertex3f(1.0, -1.0, -1.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glEnd();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glRotatef(180, 0, 0, 1);
	glTranslatef(0.0, 1.3, 0.5);
	glScalef(0.3, 0.3, 0.3);
	tree(1);
	glTranslatef(2.4, 0, -4);
	tree(4);
	glTranslatef(-1.3, 0, 1.8);
	tree(2);
	glTranslatef(-0.6, 0, 3);
	tree(5);
	glTranslatef(-2.6, 0, -4);
	tree(5);
	glTranslatef(0.6, 0, 1.8);
	tree(7);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, -1, 0, 0);
	glRotatef(180, 0, 0, 1);
	glTranslatef(-0.6, -0.675, -0.2);
	glScalef(0.3, 0.3, 0.3);
	firBuliding();
	glTranslatef(1.2, 0, -1.0);
	firBuliding();
	glTranslatef(3.5, 0, 0.5);
	firBuliding();
	glTranslatef(-2.1, 0, 3.0);
	firBuliding();
	glTranslatef(-1, 0, -1.5);
	firBuliding();
	glScalef(0.5, 0.5, 0.5);
	glTranslatef(-1, -1.0, -2);
	tree(2);
	glTranslatef(5, 0, 4);
	tree(2);
	glPopMatrix();

	glPopMatrix();


	// { Left }
	glPushMatrix();
	glTranslatef(-1.0, -1.0, 1.0);
	glRotatef((GLfloat)joint1, 0.0f, 0.0f, -1.0f);

	glTranslatef(1.0, 1.0, -1.0);
	glColor3f(0, 0.3, 0.3);
	glBegin(GL_QUADS);
	glVertex3f(-1.0, 1.0, -1.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glEnd();
	
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	glTranslatef(0.0, 1.3, 0.5);
	glScalef(0.3, 0.3, 0.3);
	tree(2);
	glTranslatef(2.4, 0, -4);
	tree(4);
	glTranslatef(-1.3, 0, 1.8);
	tree(1);
	glTranslatef(-0.6, 0, 3);
	tree(6);
	glTranslatef(-2.6, -1.0, -4);
	tree(5);
	glTranslatef(0.6, 0, 1.8);
	tree(3);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	glRotatef(180, 1, 0, 0);
	glTranslatef(-0.6, -0.675, -0.2);
	glScalef(0.3, 0.3, 0.3);
	firBuliding();
	glTranslatef(1.2, 0, -1.0);
	firBuliding();
	glTranslatef(3.5, 0, 0.5);
	firBuliding();
	glTranslatef(-2.1, 0, 3.0);
	firBuliding();
	glTranslatef(-1, 0, -1.5);
	firBuliding();
	glScalef(0.5, 0.5, 0.5);
	glTranslatef(-1, -1.0, -2);
	tree(4);
	glTranslatef(5, 0, 4);
	tree(1);
	glPopMatrix();

	glPopMatrix();

	// { Right }
	glPushMatrix();
	glTranslatef(1.0, -1.0, 1.0);
	glRotatef((GLfloat)joint1, 0.0f, 0.0f, 1.0f);

	glTranslatef(-1.0, 1.0, -1.0);
	glColor3f(0, 0.3, 0.3);
	glBegin(GL_QUADS);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(1.0, -1.0, 1.0);
	glVertex3f(1.0, -1.0, -1.0);
	glVertex3f(1.0, 1.0, -1.0);
	glEnd();

	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	glRotatef(180, 1, 0, 0);
	glTranslatef(0.0, 1.3, 0.5);
	glScalef(0.3, 0.3, 0.3);
	tree(7);
	glTranslatef(2.4, 0, -4);
	tree(6);
	glTranslatef(-1.3, 0, 1.8);
	tree(4);
	glTranslatef(-0.6, 0, 3);
	tree(2);
	glTranslatef(-2.6, 0, -4);
	tree(1);
	glTranslatef(0.6, 0, 1.8);
	tree(3);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	glTranslatef(-0.6, -0.675, -0.2);
	glScalef(0.3, 0.3, 0.3);
	firBuliding();
	glTranslatef(1.2, 0, -1.0);
	firBuliding();
	glTranslatef(3.5, 0, 0.5);
	firBuliding();
	glTranslatef(-2.1, 0, 3.0);
	firBuliding();
	glTranslatef(-1, 0, -1.5);
	firBuliding();
	glScalef(0.5, 0.5, 0.5);
	glTranslatef(-1, -1.0, -2);
	tree(3);
	glTranslatef(5, 0, 4);
	tree(6);
	glPopMatrix();


	// { Top }
	glPushMatrix();
	glTranslatef(1.0, 1.0, -1.0);
	glRotatef((GLfloat)joint2, 0.0f, 0.0f, 1.0f);

	glTranslatef(-1.0, -1.0, 1.0);
	glColor3f(0, 0.3, 0.3);
	glBegin(GL_QUADS);
	glVertex3f(-1.0, 1.0, 1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(1.0, 1.0, -1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glEnd();
	
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(0.0, 1.3, 0.5);
	glScalef(0.3, 0.3, 0.3);
	tree(1);
	glTranslatef(2.4, 0, -4);
	tree(4);
	glTranslatef(-1.3, 0, 1.8);
	tree(2);
	glTranslatef(-0.6, 0, 3);
	tree(5);
	glTranslatef(-2.6, 0, -4);
	tree(5);
	glTranslatef(0.6, 0, 1.8);
	tree(7);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glRotatef(180, 0, 0, 1);
	glTranslatef(0.5, -0.675, -0.2);
	glScalef(0.3, 0.3, 0.3);
	firBuliding();
	glTranslatef(0.6, 0, -1.0);
	firBuliding();
	glTranslatef(-4.5, 0, 0.5);
	firBuliding();
	glTranslatef(0, 0, 3.0);
	firBuliding();
	glTranslatef(4.5, 0, 0);
	firBuliding();
	glScalef(0.5, 0.5, 0.5);
	glTranslatef(-5, 0, -2);
	tree(4);
	glPopMatrix();
	
	glPopMatrix();
	glPopMatrix();

	// { Bottom }
	glColor3f(0, 0.3, 0.3);
	glBegin(GL_QUADS);
	glVertex3f(1.0, -1.0, 1.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(1.0, -1.0, -1.0);
	glEnd();

	glPushMatrix();
	glRotatef(90, 0, 0, -1);
	glRotatef(90, 0, 0, 1);
	glRotatef(180, 1, 0, 0);
	glTranslatef(0.0, 1.3, 0.5);
	glScalef(0.3, 0.3, 0.3);
	tree(5);
	glTranslatef(2.4, 0, -4);
	tree(1);
	glTranslatef(-1.3, 0, 1.8);
	tree(4);
	glTranslatef(-0.6, 0, 3);
	tree(7);
	glTranslatef(-2.6, 0, -4);
	tree(1);
	glTranslatef(0.6, 0, 1.8);
	tree(1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 0, 0, 1);
	glRotatef(180, 1, 0, 0);
	glTranslatef(-0.6, -0.675, -0.2);
	glScalef(0.3, 0.3, 0.3);
	firBuliding();
	glTranslatef(1.2, 0, -1.0);
	firBuliding();
	glTranslatef(3.5, 0, 0.5);
	firBuliding();
	glTranslatef(-2.1, 0, 3.0);
	firBuliding();
	glTranslatef(-1, 0, -1.5);
	firBuliding();
	glScalef(0.5, 0.5, 0.5);
	glTranslatef(-1, -1.0, -2);
	tree(7);
	glTranslatef(5, -0, 4);
	tree(4);
	glPopMatrix();

}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	polarView(distance, azimAngle, elevationAngle, twistAngle);
	glMatrixMode(GL_MODELVIEW);
	DrawScene();
	glPopMatrix();
	glFlush();
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'Z':
		joint1 = (joint1 + 1) % 180;
		glutPostRedisplay();	break;
	case 'z':
		joint1 = (joint1 - 1) % 180;
		glutPostRedisplay();	break;
	case 'X':
		joint2 = (joint2 + 1) % 180;
		glutPostRedisplay();	break;
	case 'x':
		joint2 = (joint2 - 1) % 180;
		glutPostRedisplay();	break;
	case 'c':
		light = (light+ 3) % 360;
		glutPostRedisplay();	break;
	case 'v':
		if (lonoff == 1) {
			lonoff = 0;
			glDisable(GL_LIGHTING);
		}
		else {
			lonoff = 1;
			glEnable(GL_LIGHTING);
		}
		glutPostRedisplay();	break;
	case 27:
		exit(0);         break;
	default:         break;
	}
}

void main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("The Box");
	init();

	createRandomArray();

	glutMouseFunc(mouse);
	glutMotionFunc(motion);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
}