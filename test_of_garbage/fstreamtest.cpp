#include <Eigen/Core>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

string csvFileName = "W1matrix.dat";

int main(){
	string str;
	ifstream csvFile(csvFileName);
	if(!csvFile){
		cerr << "failed" << endl;
		exit(1);
	}
	string buff;
	double a[16][256];
	string buf;
	for(int i = 0; i < 16; i++){
		for(int j = 0; j < 256; j++){
			getline(csvFile, buf, ',');
			a[i][j] = stod(buf);
		}
	}
	Eigen::MatrixXd W2 = Eigen::MatrixXd::Zero(5, 16);
	ifstream ifs2("W2matrix.dat");
	if(!ifs2){
			cerr << "fuck!!!!1!!!" << endl;
			exit(1);
	}
	for(int indy = 0; indy < 5; indy++){
		for(int indx = 0; indx < 16; indx++){
			getline(ifs2, buf, ',');
			W2(indy, indx) = stod(buf);
		}
	}
	cout << W2 << endl;
	Eigen::VectorXd b1 = Eigen::VectorXd::Zero(16);
	ifstream ifs3("b1vector.dat");
	if(!ifs3){
			cerr << "fuck!!!!1!!!" << endl;
			exit(1);
	}
	for(int indy = 0; indy < 16; indy++){
		getline(ifs3, buf, ',');
		b1(indy) = stod(buf);
	}
	cout << b1 << endl;
}
