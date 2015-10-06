/*
Craig Reingold
9/23/15
Dynamic Memory

This code will read in grades.dat.  It will then use dynamic memory allocation to create an array to store the grades.
The code will:
	* read the grades into an array
	* find the lowest and highest grade and calculate the average grade for the course
	* return the number of students that received and an A ( above 94 ) and students that failed ( less than 60 )

It will also delete the alocated memory when it is finished.

sprintf() will be used to print the result out to the screen.
*/


#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>

using namespace std;

struct student{
	int IDN;
	int grade;
};



int main(){

//Opening the grade.dat file

	ifstream gradebook("grades.dat");

	if (!gradebook){
		cout << "Could not open grades.dat  Shutting down . . . " << endl;
		exit(1);
	}

// Getting rid of the first two lines . . .
	string wasteString;
	getline(gradebook , wasteString);
	getline(gradebook , wasteString);

//Using dynamic memory allocation to read the grades into an array

	int size = 100;

	int studentID;
	int * grades = new int[size];

	for ( int i = 0 ; i < size ; i += 1 ){
		gradebook >> studentID >> grades[i];

	}

	gradebook.close();

// Finding the lowest and highest grades, while calculating average and counting the failures and A's

	int lowestIndex = 0;
	int highestIndex = 0;
	int numberOfA = 0;
	int numberOfF = 0;
	int sumGrades = 0;
	int studentNumber = 0;

	for ( int j = 0 ; j < size ; j += 1 ){
		if ( grades[j] <= grades[lowestIndex] ){
			lowestIndex = j;
		}

		if ( grades[j] >= grades[highestIndex] ){
			highestIndex = j;
		}

		if ( grades[j] >= 94 ){
			numberOfA += 1;
		}
		if ( grades[j] <= 60 ){
			numberOfF += 1;
		}

		sumGrades += grades[j];
		studentNumber += 1;
	}

	float averageGrade = ( float ) sumGrades / ( float ) studentNumber;
	int lowGrade = grades[lowestIndex];
	int highGrade = grades[highestIndex];

// Printing things to screen . . .
	char lowestStr[256];
	sprintf(lowestStr , "The lowest grade in the class was %d. \nThe highest grade in teh class was %d. \nThere were %d students that received an A.\nThere were %d students that failed.\nThe class average was %f.\n" , lowGrade, highGrade, numberOfA, numberOfF, averageGrade );

	cout << lowestStr << endl;

	return 0;
}
