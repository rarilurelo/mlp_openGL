#include <Eigen/Core>
#include <stdio.h>
#include <stdlib.h>
#include <GLUT/glut.h>
#include <string>
#include <iostream>
#include <math.h>
#include <fstream>
#define MAXPOINT 100000


using namespace std;
using namespace Eigen;

Matrix<double, 50, 256> W1;
Matrix<double, 5, 50> W2;
VectorXd b1 = VectorXd::Zero(50);
VectorXd b2 = VectorXd::Zero(5);
VectorXd xv = VectorXd::Zero(256);
VectorXd yv = VectorXd::Zero(50);
VectorXd zv = VectorXd::Zero(5);
VectorXd u1 = VectorXd::Zero(50);
VectorXd u2 = VectorXd::Zero(5);

int color = 10;
int point[MAXPOINT][2];
int tim = 10;
int pointnum = 0;
unsigned char mouseFlag = GL_FALSE;
int WinID[2];
int ll;

void init1(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
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
	double R, G, B;
	switch(color){
	case 0:
		R = 1.0;
		G = 0;
		B = 0;
		break;
	case 1:
		R = 0;
		G = 0;
		B = 1.0;
		break;
	case 2:
		R = 1.0;
		G = 1.0;
		B = 0;
		break;
	case 3:
		R = 1.0;
		G = 1.0;
		B = 1.0;
		break;
	case 4:
		R = 0;
		G = 0.5;
		B = 0;
		break;
	default:
		R = 0;
		G = 0;
		B = 0;
		break;
	}
	static double rx, ry;
	rx += 0.1;
	ry += 0.1;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3d(R, G, B);
	glBegin(GL_POLYGON);
	double x, y, r = 0.5;
	int i;
	int n = 50;
	double rate;
	for(i = 0; i < n; i++){
		rate = (double)i/n;
		x = r*cos(2.0*3.1415926535*rate)+1.5*cos(rx);
		y = r*sin(2.0*3.1415926535*rate)+1.5*sin(ry);
		glVertex3d(x, y, -5.0);
	}
	glEnd();
	glPopMatrix();
	glutSwapBuffers();
}

void display2(void)
{
	int i;
	glClear(GL_COLOR_BUFFER_BIT);
	if (pointnum > 1) {
		draw(0);
	}
	glutSwapBuffers();
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

void keyboard2(unsigned char key, int x, int y){
	int i;
	int push[256];
	switch (key) {
	case 'q':
	case 'Q':
	case '\033':
		exit(0);
	case 'r':
		for(i = 0; i < 256; i++){
			push[i] = 0;
		}
		for(i = 0; i < pointnum; i++){
			push[point[i][0]/16+(point[i][1]/16)*16] = 1;
		}
		FILE *outputfile0;
		outputfile0 = fopen("outputr.dat", "a");
		for(i = 0; i < 256; i++){
			if(i == 256){
				fprintf(outputfile0, "%d", push[i]);
				break;
			}
			fprintf(outputfile0, "%d,", push[i]);
		}
		fprintf(outputfile0, "\n");
		fclose(outputfile0);
		pointnum = 0;
		break;
	case 'b':
		for(i = 0; i < 256; i++){
			push[i] = 0;
		}
		for(i = 0; i < pointnum; i++){
			push[point[i][0]/16+(point[i][1]/16)*16] = 1;
		}
		FILE *outputfile1;
		outputfile1 = fopen("outputb.dat", "a");
		for(i = 0; i < 256; i++){
			if(i == 256){
				fprintf(outputfile1, "%d", push[i]);
				break;
			}
			fprintf(outputfile1, "%d,", push[i]);
		}
		fprintf(outputfile1, "\n");
		fclose(outputfile1);
		pointnum = 0;
		break;
	case 'y':
		for(i = 0; i < 256; i++){
			push[i] = 0;
		}
		for(i = 0; i < pointnum; i++){
			push[point[i][0]/16+(point[i][1]/16)*16] = 1;
		}
		FILE *outputfile2;
		outputfile2 = fopen("outputy.dat", "a");
		for(i = 0; i < 256; i++){
			if(i == 256){
				fprintf(outputfile2, "%d", push[i]);
				break;
			}
			fprintf(outputfile2, "%d,", push[i]);
		}
		fprintf(outputfile2, "\n");
		fclose(outputfile2);
		pointnum = 0;
		break;
	case 'w':
		for(i = 0; i < 256; i++){
			push[i] = 0;
		}
		for(i = 0; i < pointnum; i++){
			push[point[i][0]/16+(point[i][1]/16)*16] = 1;
		}
		FILE *outputfile3;
		outputfile3 = fopen("outputw.dat", "a");
		for(i = 0; i < 256; i++){
			if(i == 256){
				fprintf(outputfile3, "%d", push[i]);
				break;
			}
			fprintf(outputfile3, "%d,", push[i]);
		}
		fprintf(outputfile3, "\n");
		fclose(outputfile3);
		pointnum = 0;
		break;
	case 'g':
		for(i = 0; i < 256; i++){
			push[i] = 0;
		}
		for(i = 0; i < pointnum; i++){
			push[point[i][0]/16+(point[i][1]/16)*16] = 1;
		}
		FILE *outputfile4;
		outputfile4 = fopen("outputg.dat", "a");
		for(i = 0; i < 256; i++){
			if(i == 256){
				fprintf(outputfile4, "%d", push[i]);
				break;
			}
			fprintf(outputfile4, "%d,", push[i]);
		}
		fprintf(outputfile4, "\n");
		fclose(outputfile4);
		pointnum = 0;
		break;
	case '5':
		for(i = 0; i < 256; i++){
			push[i] = 0;
		}
		for(i = 0; i < pointnum; i++){
			push[point[i][0]/16+(point[i][1]/16)*16] = 1;
		}
		FILE *outputfile5;
		outputfile5 = fopen("output5.dat", "a");
		for(i = 0; i < 256; i++){
			if(i == 256){
				fprintf(outputfile5, "%d", push[i]);
				break;
			}
			fprintf(outputfile5, "%d,", push[i]);
		}
		fprintf(outputfile5, "\n");
		fclose(outputfile5);
		pointnum = 0;
		break;
	case '6':
		for(i = 0; i < 256; i++){
			push[i] = 0;
		}
		for(i = 0; i < pointnum; i++){
			push[point[i][0]/16+(point[i][1]/16)*16] = 1;
		}
		FILE *outputfile6;
		outputfile6 = fopen("output6.dat", "a");
		for(i = 0; i < 256; i++){
			if(i == 256){
				fprintf(outputfile6, "%d", push[i]);
				break;
			}
			fprintf(outputfile6, "%d,", push[i]);
		}
		fprintf(outputfile6, "\n");
		fclose(outputfile6);
		pointnum = 0;
		break;
	case '7':
		for(i = 0; i < 256; i++){
			push[i] = 0;
		}
		for(i = 0; i < pointnum; i++){
			push[point[i][0]/16+(point[i][1]/16)*16] = 1;
		}
		FILE *outputfile7;
		outputfile7 = fopen("output7.dat", "a");
		for(i = 0; i < 256; i++){
			if(i == 256){
				fprintf(outputfile7, "%d", push[i]);
				break;
			}
			fprintf(outputfile7, "%d,", push[i]);
		}
		fprintf(outputfile7, "\n");
		fclose(outputfile7);
		pointnum = 0;
		break;
	case '8':
		for(i = 0; i < 256; i++){
			push[i] = 0;
		}
		for(i = 0; i < pointnum; i++){
			push[point[i][0]/16+(point[i][1]/16)*16] = 1;
		}
		FILE *outputfile8;
		outputfile8 = fopen("output8.dat", "a");
		for(i = 0; i < 256; i++){
			if(i == 256){
				fprintf(outputfile8, "%d", push[i]);
				break;
			}
			fprintf(outputfile8, "%d,", push[i]);
		}
		fprintf(outputfile8, "\n");
		fclose(outputfile8);
		pointnum = 0;
		break;
	case '9':{
		for(i = 0; i < 256; i++){
			push[i] = 0;
		}
		for(i = 0; i < pointnum; i++){
			push[point[i][0]/16+(point[i][1]/16)*16] = 1;
		}
		int indi;
		for(indi = 0; indi < 256; indi++){
			xv(indi) = push[indi];
		}
		u1 = W1*xv+b1;
		int indj;
		for(indj = 0; indj < u1.rows(); indj++){
			yv(indj) = (0 < u1(indj) ? u1(indj) : 0);
		}
		u2 = W2*yv+b2;
		double sum = exp(u2(0))+exp(u2(1))+exp(u2(2))+exp(u2(3))+exp(u2(4));
		double print;
		for(indj = 0; indj < u2.rows(); indj++){
			zv(indj) = exp(u2(indj))/sum;
			print = zv(indj);
		}
		double mp = 0;
		int mpi;
		for(indi = 0; indi < 5; indi++){
			if(mp < zv(indi)){
				mp = zv(indi);
				mpi = indi;
			}
		}
		color = mpi;
		pointnum = 0;
		break;
	}
	default:
		break;
	}
}

void Timer(int value)
{
	if(value == 1){
		glutTimerFunc(tim, Timer, 1);
		for(int loop = 0; loop < 2; ++loop){
			glutSetWindow(WinID[loop]);
			glutPostRedisplay();
		}
	}
}

int main(int argc, char *argv[])
{
	ifstream ifs("W1matrix.dat");
	if(!ifs){
		cerr << "fuck!!!!1!!!" << endl;
		exit(1);
	}
	string buf;
	int indy;
	int indx;
	for(indy = 0; indy < 50; indy++){
		for(indx = 0; indx < 256; indx++){
			if(getline(ifs, buf, ',')){
				W1(indy, indx) = std::stod(buf);
			}
		}
	}
	
	ifstream ifs2("W2matrix.dat");
	if(!ifs2){
			cerr << "fuck!!!!1!!!" << endl;
			exit(1);
	}
	for(indy = 0; indy < 5; indy++){
		for(indx = 0; indx < 50; indx++){
			if(getline(ifs2, buf, ',')){
				W2(indy, indx) = std::stod(buf);
			}
		}
	}
	
	ifstream ifs3("b1vector.dat");
	if(!ifs3){
			cerr << "fuck!!!!1!!!" << endl;
			exit(1);
	}
	for(indy = 0; indy < 50; indy++){
		if(getline(ifs3, buf, ',')){
			b1(indy) = std::stod(buf);
		}
	}
	
	ifstream ifs4("b2vector.dat");
	if(!ifs4){
			cerr << "fuck!!!!1!!!" << endl;
			exit(1);
	}
	for(indy = 0; indy < 50; indy++){
		if(getline(ifs4, buf, ',')){
			b2(indy) = std::stod(buf);
		};
}
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(500, 400);
	glutInitWindowPosition(10, 10);
	WinID[0] = glutCreateWindow("output");
	glutDisplayFunc(display1);
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

	glutTimerFunc(tim, Timer, 1);
	glutMainLoop();
	return 0;

}
