#include "glut.h"
#include <stdlib.h>
#include <time.h>

GLfloat coneSize[8];
GLfloat crand1[8][10], crand2[8][10],
		trand1[8][10], trand2[8][10],
		sphereSize[8][10];

void firBulidingWindow()
{
	//창문
	glColor3f(0.2, 0.4, 0.7);
	glPushMatrix();
	glScalef(0.15, 0.3, 0.1);
	glutSolidCube(1.);
	glPopMatrix();

	glColor3f(0.1, 0.1, 0.1);		//창틀
	glPushMatrix();
	glTranslatef(0, 0, 0.01);
	glScalef(0.01, 0.3, 0.1);
	glutSolidCube(1.);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.075, 0, 0.01);
	glScalef(0.01, 0.3, 0.1);
	glutSolidCube(1.);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.075, 0, 0.01);
	glScalef(0.01, 0.3, 0.1);
	glutSolidCube(1.);
	glPopMatrix();

	glColor3f(0.1, 0.1, 0.1);
	glPushMatrix();
	glTranslatef(0.0, 0.15, 0.01);
	glScalef(0.175, 0.01, 0.1);
	glutSolidCube(1.);
	glPopMatrix();

	glPushMatrix();		//손잡이
	glTranslatef(0.03, 0, 0.055);
	glutSolidSphere(0.01, 30, 30);
	glPopMatrix();

	glPushMatrix();		//손잡이
	glTranslatef(-0.03, 0, 0.055);
	glutSolidSphere(0.01, 30, 30);
	glPopMatrix();
}

void firBulidingTerrace()
{
	//테라스
	glColor3f(0.7, 0.7, 0.7);
	glPushMatrix();

	glPushMatrix(); 	 //테라스 바닥
	glScalef(1.0, 0.01, 0.1);
	glutSolidCube(1.);
	glPopMatrix();

	glPushMatrix();				 	 //테라스 난간
	glTranslatef(0.0, 0.05, 0.05);
	glScalef(1.05, 0.1, 0.01);
	glutSolidCube(1.);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5, 0.05, 0.0);
	glScalef(0.05, 0.1, 0.1);
	glutSolidCube(1.);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5, 0.05, 0.0);
	glScalef(0.05, 0.1, 0.1);
	glutSolidCube(1.);
	glPopMatrix();

	glColor3f(0.1, 0.1, 0.1);
	glPushMatrix();				 	 //테라스 난간2
	glTranslatef(0.2, 0.05, 0.0);
	glScalef(0.05, 0.1, 0.1);
	glutSolidCube(1.);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.2, 0.05, 0.0);
	glScalef(0.05, 0.1, 0.1);
	glutSolidCube(1.);
	glPopMatrix();

	//창문 3개
	glPushMatrix();
	glTranslatef(0.35, 0.15, -0.04);
	firBulidingWindow();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.15, -0.04);
	firBulidingWindow();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.35, 0.15, -0.04);
	firBulidingWindow();
	glPopMatrix();

	glPopMatrix();

}

void firBuliding()
{
	glPushMatrix();

	glPushMatrix();
	glColor3f(0.3, 0.3, 0.3);
	glScalef(1.0, 2.0, 1.0);
	glutSolidCube(1.);
	glPopMatrix();

	glPushMatrix(); 	 //문
	glTranslatef(0.0, -0.8, 0.5);
	glColor3f(0.0, 0.3, 0.3);
	glScalef(0.3, 0.4, 0.1);
	glutSolidCube(1.);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -0.5, 0.5);
	firBulidingTerrace();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 0.5);
	firBulidingTerrace();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.5, 0.5);
	firBulidingTerrace();
	glPopMatrix();

	glRotatef(180, 0, 1, 0);
	glPushMatrix();
	glTranslatef(0, -0.5, 0.5);
	firBulidingTerrace();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 0.5);
	firBulidingTerrace();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.5, 0.5);
	firBulidingTerrace();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -1, 0.5);
	firBulidingTerrace();
	glPopMatrix();

	glPopMatrix();
}

void createRandomArray()
{
	srand(time(NULL));

	for (int i = 0; i < 8; i++) {
		coneSize[i] = 0.01 * (rand() % 21 + 30);

		for (int j = 0; j < 10; j++) {
			crand1[i][j] = 0.01 * (rand() % 60 + 30);
			crand2[i][j] = 0.01 * (rand() % 40);
			trand1[i][j] = 0.01 * (rand() % 100 + 30);
			trand2[i][j] = 0.01 * (rand() % 100 + 30);
			sphereSize[i][j] = 0.01 * (rand() % 41 + 20);
		}
	}
}

void tree(int num)
{
	glPushMatrix();
	glTranslatef(0, -1, 0);

	glPushMatrix();
	glColor3f(0.5, 0.5, 0.3);
	glRotatef(90, -1, 0, 0);
	glutSolidCone(coneSize[num], 1.3, 10, 20);
	glPopMatrix();

	glTranslatef(-0.7, 0.5, 0);

	for (int i = 0; i < 10; i++) {
		glPushMatrix();
		glColor3f(0.0, crand1[num][i], crand2[num][i]);
		glTranslatef(trand1[num][i], trand2[num][i], 0);
		glutSolidSphere(sphereSize[num][i], 30, 30);
		glPopMatrix();
	}

	glPopMatrix();
}