/*
Craig Reingold
09/04/2015
Gaussian Distribution Generator

This program beings with a function that will generate normal distributions, given a mean and standard deviation.
It will then print out a histogram of the normal distribution generated.

*/

#include<iostream>
#include<iomanip>
#include<math.h>
#include<cstdlib>
#include<ctime>

using namespace std;

const double g_pi = 3.1415926;

// ##########################################################

//Edit the section below to adjust the output

const float rangeMin = -10.0;
const float rangeMax = 10.0;
const float binSize = 0.2;
const int numberOfBins = 100;

// ###########################################################


float Normal ( float mean, float stddev ){
	//This function will generate the normal distribution with given mean and standard deviation
	
	float R1;
	R1 = (float) rand() / (float) (RAND_MAX);
	float R2;
	R2 = (float) rand() / (float) (RAND_MAX);

	return mean + stddev * cos(2*g_pi*R1) * sqrt(-log(R2) );
}

int main(){
	//This is where the histogram will be generated

	float hist[numberOfBins] = {0};
	const float mean = 0;
	const float stddev = 2;
	
	srand ( time ( 0 ) );

	//Filling the histogram
	for ( int i = 0 ; i < 10000 ; i += 1 ){

		float toFill = Normal(mean, stddev);
		for ( int j = 0 ; j < numberOfBins ; j += 1 ){
			if ( toFill >= rangeMin + j * binSize && toFill < rangeMin + (j + 1)*binSize ){
				hist[j] += 1;
			}
		}
		
	}

	//Printing the output
	for ( int k = 0 ; k < numberOfBins ; k += 1 ){
		float binStart = rangeMin + binSize * k;
		cout << setprecision(2);
		cout << k << '\t' << binStart << '\t' << setprecision(5) << hist[k] << endl;
	}


	return 0;
}
