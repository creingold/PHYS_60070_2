/*
Craig Reingold
9/15/15
Monte Carlo Integral

This code will be used to calculate pi using the Monte Carlo integral technique.
It will do the following things

	* generate random numbers in the range from 0 to 1
	* define int Counter to store number of accepted events
	* generate a slew of coordinates in the first quadrant
	* use an if statement to determine if the coordinates are within the quarter circle, if so add one to the counter
	* Calculate the value of pi

Pi will be calculated by taking the ratio of the points that fell within the area of the quarter circle (times 4) to the total number of points in the 1 x 1 square that is the first quadrant.

*/

#include<iostream>
#include<iomanip>
#include<math.h>
#include<cstdlib>
#include<ctime>

using namespace std;

//Change this to increase or decrease the number of iterations in the MC integral
const int numberOfRuns = 1000000000;

float randomNormalized(){
	float R1 = (float) rand() / (float) (RAND_MAX);
	return R1;
}

int main(){
	//Definining things
	const float rangeStart = 0.0;
	const float rangeStop = 1.0;
	srand ( time(0) );
	
	//This is the counter to be used for the MC integral
	int Counter = 0;

	//In this loop, we will generate a coordinate (x,y) with randomNormalized, and then check if that point is on or within the quarter circle.
	//Elected to put this in one loop because it will decrease the running time, and the memory usage.

	for ( int i = 0 ; i < numberOfRuns ; i += 1 ){
		float coordinate[2] = {0};
		coordinate[0] = randomNormalized();
		coordinate[1] = randomNormalized();
	
		if ( coordinate[0]*coordinate[0] + coordinate[1]*coordinate[1] <= 1 ){
			Counter += 1;
		}
	}

	float pi = 4*(float)Counter/(float)numberOfRuns;

	cout << setprecision(5) << pi << endl;

	return 0;
}
