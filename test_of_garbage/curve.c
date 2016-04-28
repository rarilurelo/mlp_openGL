#include <stdio.h>
#include <stdlib.h>
#include <GLUT/glut.h>
#include <math.h>

int WinID[2];
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3d(0.0, 1.0, 1.0);
	glBegin(GL_LINES);
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
	glFlush();

}


void keyboard(unsigned char key, int x, int y)
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


void init(char *progname)
{
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(500, 400);
	glutInitWindowPosition(10, 10);
	WinID[0] = glutCreateWindow(progname);
	glClearColor(0.0, 0.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (double)500/(double)400, 0.1, 20);
}

void init2(char *progname)
{
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(500, 400);
	glutInitWindowPosition(600, 600);
	WinID[1] = glutCreateWindow(progname);
	glClearColor(0.0, 1.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (double)500/(double)400, 0.1, 20);
	}
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	init(argv[0]);
	init2(argv[1]);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
