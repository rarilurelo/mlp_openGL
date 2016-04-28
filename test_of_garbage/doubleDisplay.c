#include <stdio.h>
#include <stdlib.h>
#include <GLUT/glut.h>
#include <math.h>
#define MAXPOINT 100000

GLint point[MAXPOINT][2];
int time = 10;
int pointnum = 0;
unsigned char mouseFlag = GL_FALSE;
int WinID[2];
int ll;

void init1(void)
{
	glClearColor(0.0, 0.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (double)500/(double)400, 0.1, 20);
}

void init2(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

void draw(int s){
	int i;
	int zero = 0;
	for(int i = s; i < pointnum; i++){
		if(point[i][0] == 0 && point[i][1] == 0){
			zero = i;
			break;
		}
	}
	if(zero == 0){
		glColor3d(0.0, 0.0, 0.0);
		glBegin(GL_LINE_STRIP);
		for(i = s; i < pointnum; i++){
			glVertex2iv(point[i]);
		}
		glEnd();
	}
	else{
		glColor3d(0.0, 0.0, 0.0);
		glBegin(GL_LINE_STRIP);
		for(i = s; i < zero; ++i){
			glVertex2iv(point[i]);
		}
		glEnd();
	}
	if(zero+1 > pointnum-1){
		return;
	}
	else{
		if(zero == 0){
		}
		else{
		draw(zero+1);
		}
	}
}
void display1(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3d(0.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glVertex3d(-0.9, -0.9, -5.0);
	glVertex3d(0.9, -0.9, -5.0);
	glVertex3d(0.9, 0.9, -5.0);
	glVertex3d(-0.9, 0.9, -5.0);
	glEnd();
	glColor3d(0.5, 0.5, 0.0);
	glPushMatrix();
		glRotatef(-90.0, 0.0, 0.0, 1.0);
		glTranslatef(1.0, 3.0, -5.0);
		glutWireCone(0.4, 1.0, 10, 10);
	glPopMatrix();
	glutSwapBuffers();
}

void display2(void)
{
	int i;
	glClear(GL_COLOR_BUFFER_BIT);
	if (pointnum > 1) {
	/*
		int z = 0;
		for(i = 0; i < pointnum; ++i) {
			if(point[i][0] == 0 && point[i][1] == 0){
				z = i;
				break;
			}
		}
		if(z == 0){
			glColor3d(0.0, 0.0, 0.0);
			glBegin(GL_LINE_STRIP);
			for(i = 0; i < pointnum; ++i) {
				glVertex2iv(point[i]);
			}
			glEnd();
		}
		else{
			glColor3d(0.0, 0.0, 0.0);
			glBegin(GL_LINE_STRIP);
			for(i = 0; i < z; ++i){
				glVertex2iv(point[i]);
			}
			glEnd();
			glColor3d(0.0, 0.0, 0.0);
			glBegin(GL_LINE_STRIP);
			for(i = z+1; i < pointnum-1; ++i){
				glVertex2iv(point[i]);
			}
			glEnd();
		}
	*/
		draw(0);
	}
	glutSwapBuffers();
}


void keyboard1(unsigned char key, int x, int y)
{
	switch (key) {
	case 'q':
	case 'Q':
	case '\033':
		exit(0);
	default:
		break;
	}
}

void keyboard2(unsigned char key, int x, int y)
{
	switch (key) {
	case 'q':
	case 'Q':
	case '\033':
		exit(0);
	default:
		break;
	}
}

void Timer(int value)
{
	if(value == 1){
		glutTimerFunc(time, Timer, 1);
		for(int loop = 0; loop < 2; ++loop){
			glutSetWindow(WinID[loop]);
			glutPostRedisplay();
		}
	}
}

void MouseFunc2(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		mouseFlag = GL_TRUE;
	}
	else{
		mouseFlag = GL_FALSE;
		if(point[pointnum-1][0] == 0 && point[pointnum-1][1] == 0){
			return;
		}
		else{
			point[pointnum][0] = 0;
			point[pointnum][1] = 0;
			if(pointnum < MAXPOINT-1) ++pointnum;
			glutPostRedisplay();
		}
	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		ll = 0;
	}
}

void MouseMotion2(int x, int y)
{
	if(mouseFlag == GL_FALSE) return;
	point[pointnum][0] = x;
	point[pointnum][1] = y;
	if(pointnum < MAXPOINT-1) ++pointnum;
	glutPostRedisplay();
}

void resize(int w, int h)
{
	glViewport(0, 0, w, h);		//ウィンドウ全体をビューボードにする
	
	glLoadIdentity();		//変換行列の初期化

	glOrtho(-0.5, (GLdouble)w - 0.5, (GLdouble)h - 0.5, -0.5, -1.0, 1.0);	//スクリー上の表示領域をビューボードの大きさに比例させる
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(500, 400);
	glutInitWindowPosition(10, 10);
	WinID[0] = glutCreateWindow("output");
	glutDisplayFunc(display1);
	glutKeyboardFunc(keyboard1);
	init1();

	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(256, 256);
	glutInitWindowPosition(600, 600);
	WinID[1] = glutCreateWindow("input");
	glutDisplayFunc(display2);
	glutReshapeFunc(resize);
	glutMouseFunc(MouseFunc2);
	glutMotionFunc(MouseMotion2);
	glutKeyboardFunc(keyboard2);
	init2();

	glutTimerFunc(time, Timer, 1);
	glutMainLoop();
	return 0;

}
