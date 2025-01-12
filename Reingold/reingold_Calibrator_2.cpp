/*
Craig Reingold
9/25/15
Calibrator 1

This code will calibrate data from hist.dat, and generate four histograms, 100 bins each, ranging from 0 to 1000.
*/

#include<iostream>
#include<cstdlib>
#include<fstream>

using namespace std;

// Declaring global variables

const int numberOfBins = 100;
const float rangeMin = 0;
const float rangeMax = 1000;	

float Calibrator ( float Channel , float aa , float bb){

	float ene;
		ene = Channel * aa + bb;
	return ene;

}

int main(){
	// Opening the data and checking that it was opened

	ifstream data("hist.dat");

	if ( !data ){
		cout << "Could not open data.  Check input." << endl;
		exit(1);
	}

	// Reading the data into a pointer, and then placing it into the histogram array

	float detectorEnergy[4];

	int histogramMatrix[4][numberOfBins] = {0};

	while ( !data.eof() ){
		data >> detectorEnergy[0] >> detectorEnergy[1] >> detectorEnergy[2] >> detectorEnergy[3];

		// This is where I will calibrate;

		float energy[4];

		energy[0] = Calibrator( detectorEnergy[0] , 1.05 , -20 );
		energy[1] = Calibrator( detectorEnergy[1] , 1.05 , 20 );
		energy[2] = Calibrator( detectorEnergy[2] , .95 ,  -20 );
		energy[3] = Calibrator ( detectorEnergy[3] , .95 , 20 );

		// Filling in the Histogram array

		for ( int i = 0 ; i < 4 ; i += 1 ){
			for ( int j = 0 ; j < numberOfBins ; j += 1 ){
				if ( energy[i] >= rangeMin + j * (rangeMax - rangeMin)/(float)numberOfBins && energy[i] < rangeMin + (j + 1) * (rangeMax - rangeMin)/(float) numberOfBins ){
					histogramMatrix[i][j] += 1;
				}
			}
		}
	}

	data.close();

	// Printing the data

	ofstream results("calibrated.dat");

	if ( !results ){
		cout << "Could not print results.  Check source code." << endl;
		exit(1);
	}

	for ( int m = 0 ; m < numberOfBins; m += 1 ){
		for ( int n = 0 ; n < 4 ; n += 1){
			results << histogramMatrix[n][m] << '\t';
		}
		results << endl;
		results.flush();
	}
	results.close();
	return 0;
}
