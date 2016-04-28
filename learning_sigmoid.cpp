#include <cmath>
#include <algorithm>
#include <Eigen/Core>
#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;
using namespace Eigen;


Matrix<double, 16, 256> W1;
Matrix<double, 16, 256> dW1 = MatrixXd::Zero(16, 256);
Matrix<double, 5, 16> W2;
Matrix<double, 5, 16> dW2 = MatrixXd::Zero(5, 16);
VectorXd b1 = VectorXd::Zero(16);
VectorXd b2 = VectorXd::Zero(5);
VectorXd x = VectorXd::Zero(256);
VectorXd y = VectorXd::Zero(16);
VectorXd z = VectorXd::Zero(5);
VectorXd u1 = VectorXd::Zero(16);
VectorXd u2 = VectorXd::Zero(5);
VectorXd delta1 = VectorXd::Zero(5);
VectorXd delta2 = VectorXd::Zero(5);
const int loop = 30000;
const double mu = 0.3;
const double e = 0.6;
const double lambda = 0.0001;

int main(){
	random_device seed_gen;
	mt19937 engine(seed_gen());
	normal_distribution<> dist(0.0, 0.5);
	int i, j;
	for(i = 0; i < W1.rows(); i++){
		for(j = 0; j < W1.cols(); j++) W1(i, j) = dist(engine);
	}
	for(i = 0; i < W2.rows(); i++){
		for(j = 0; j < W2.cols(); j++) W2(i, j) = dist(engine);
	}

	uniform_int_distribution<> rand5(0, 4);
	uniform_int_distribution<> rand200(0, 199);
	int sp;
	int spline;
	string prefile = "output";
	string nexfile = ".dat";
	string str;
	string fileName;
	for(i = 0; i < loop; i++){
		sp = rand5(engine);
		spline = rand200(engine);
		switch(sp){
		case 0:
			str = 'r';
			break;
		case 1:
			str = 'b';
			break;
		case 2:
			str = 'y';
			break;
		case 3:
			str = 'w';
			break;
		case 4:
			str = 'g';
			break;
		default:
			str = "!!!1!!!";
			cout << str << endl;
			break;
		}
		fileName = prefile+str+nexfile;
		ifstream File(fileName);
		if(!File){
			cerr << "failed" << endl;
			exit(1);
		}
		string buf;
		int ind = 1;
		while(getline(File, buf) && ind < spline-1) ind++;
		for(j = 0; j < 256; j++){
			getline(File, buf, ',');
			x(j) = stod(buf);
		}
		u1 = W1*x+b1;
		for(j = 0; j < u1.rows(); j++){
			y(j) = 1/(1+exp(-u1(j)));
		}
		u2 = W2*y+b2;
		double sum = exp(u2(0))+exp(u2(1))+exp(u2(2))+exp(u2(3))+exp(u2(4));
		for(j = 0; j < u2.rows(); j++){
			z(j) = exp(u2(j))/sum;
		}
		VectorXd d = VectorXd::Zero(5);
		d(sp) = 1;
		delta2 = z-d;
		VectorXd fPrime = VectorXd::Zero(16);
		for(j = 0; j < 16; j++){
			fPrime(j) = (1/(1+exp(-u1(j))))*(1-1/(1+exp(u1(j))));
		}
		delta1 = fPrime.array()*(W2.transpose()*delta2).array();
		MatrixXd tempW1;
		tempW1 = W1+mu*dW1-e*(delta1*x.transpose()+lambda*W1);
		dW1 = tempW1-W1;
		W1 = tempW1;
		MatrixXd tempW2;
		tempW2 = W2+mu*dW2-e*(delta2*y.transpose()+lambda*W2);
		dW2 = tempW2-W2;
		W2 = tempW2;
		b1 = b1-e*delta1;
		b2 = b2-e*delta2;
	}

	ofstream out("W1matrix.dat");
	if(!out){
		cerr << "fuck!!!!1!!!" << endl;
		exit(1);
	}
	for(i = 0; i < 16; i++){
		for(j = 0; j < 256;j++){
			out << W1(i, j) << ',';
		}
		out << endl;
	}
	out.close();

	ofstream out2("W2matrix.dat");
	if(!out2){
		cerr << "fuck!!!!1!!!" << endl;
		exit(1);
	}
	for(i = 0; i < 5; i++){
		for(j = 0; j < 16;j++){
			out2 << W2(i, j) << ',';
		}
		out2 << endl;
	}
	out2.close();

	ofstream out3("b1vector.dat");
	if(!out3){
		cerr << "fuck!!!!1!!!" << endl;
		exit(1);
	}
	for(i = 0; i < 16; i++){
		out3 << b1(i) << ',';
	}
	out3.close();

	ofstream out4("b2vector.dat");
	if(!out4){
		cerr << "fuck!!!!!1!!!" << endl;
		exit(1);
	}
	for(i = 0; i < 5; i++){
		out4 << b2(i) << ',';
	}
	out4.close();
	return 0;
}
