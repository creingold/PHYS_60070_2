/*
Craig Reingold
9/18/15
Pointer Practice

This code will take the input from grades.txt, and store them into two arrays.
One array will contain grades, the other will number of students that received this grade.
It will then use pointer arithmatic to calculate the average grade for the class

*/

#include<iostream>
#include<fstream>
#include<cstdlib>

using namespace std;

int main(){
	// Opening the gradebook
	ifstream gradebook("grades.txt");

	// Did the gradebook open?
	if ( !gradebook ){
		cout << "Could not open grades.txt.  Terminating code.  Goodbye." << endl;
	}

	// Initializing arrays for the grades and number of students

	float grades[7];
	int nStudents[7];

	// Reading in the gradebook
	for ( int i = 0 ; i < 7 ; i += 1 ){
		gradebook >> grades[i];
		gradebook >> nStudents[i];
	}
	gradebook.close();

	// Calculating the class average

	int nTotal = 0;
	float fSum = 0;

	for ( int j = 0 ; j < 7 ; j += 1){
		fSum += (*(grades + j)) * (*(nStudents + j));
		nTotal += *(nStudents + j);
	}

	float average = fSum / (float) nTotal;

	cout << "The class average is " << average << endl;

	return 0;
}
