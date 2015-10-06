/*
Craig Reingold
09/09/15
Vector Algebra

This code will ask the user for coordinates of two vectors in 3D Space
	Store the user input in two 1-D arrays
	Return the results of addition, subtraction, scalar and vector products

*/

#include<iostream>
#include<math.h>
#include<cstdlib>

using namespace std;

int main(){

	double A[3];
	double B[3];

	cout << "Welcome to program.  Can vector algebra do." << endl;
	cout << "Please define the A and B vectors in terms of their components (A1 A2 A3) : " << endl;

	cin >> A[0] >> A[1] >> A[2];

	cout << "Now vector B" << endl;

	cin >> B[0] >> B[1] >> B[2];
	
	//Now we will do math.  Starting with Addition, Subtraction, and inner product

	double AplusB[3];
	double AminusB[3];
	double AinnerB = 0;
	double AouterB[3];

	for ( int i = 0 ; i < 3 ; i += 1 ){
		AplusB[i] = A[i] + B[i];
		AminusB[i] = A[i] - B[i];
		AinnerB += A[i]*B[i];
	}

	AouterB[0] = A[1]*B[2] - A[2]*B[1];
	AouterB[1] = A[2]*B[0] - A[0]*B[2];
	AouterB[2] = A[0]*B[1] - A[1]*B[0];

	cout << " A + B = [ " << AplusB[0] << " " << AplusB[1] << " " << AplusB[2] << " ]" << endl;

	cout << " A - B = [ " << AminusB[0] << " " << AminusB[1] << " " << AminusB[2] << " ]" << endl;

	cout << " A * B = " << AinnerB << endl;

	cout << " A x B = [ " << AouterB[0] << " " << AouterB[1] << " " << AouterB[2] << " ]" << endl;

	return 0;

}
