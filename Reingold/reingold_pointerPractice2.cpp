/*
Craig Reingold
9/18/15
Pointer Practice 2

Same as 'pointer practice' but this time with structures.

*/

#include<iostream>
#include<fstream>
#include<cstdlib>

using namespace std;

struct distr_t{
	float grade[7];
	int nStudents[7];
};

int main(){
	// Opening the gradebook
	ifstream gradebook("grades.txt");

	// Did the gradebook open?
	if ( !gradebook ){
		cout << "Could not open grades.txt.  Terminating code.  Goodbye." << endl;
	}

	// Initializing structure

	distr_t distribution;

	// Reading in the gradebook
	for ( int i = 0 ; i < 7 ; i += 1 ){
		gradebook >> distribution.grade[i];
		gradebook >> distribution.nStudents[i];
	}
	gradebook.close();

	// Calculating the class average

	distr_t *pPointer = &distribution;

	int nTotal = 0;
	float fSum = 0;

	for ( int j = 0 ; j < 7 ; j += 1){
		fSum += (pPointer->grade[j]) * (pPointer->nStudents[j]);
		nTotal += pPointer->nStudents[j];
	}

	float average = fSum / (float) nTotal;

	cout << "The class average is " << average << endl;

	return 0;
}
