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

void Calibrator( const float *channel , float *energy , const float *aa, const float *bb, const int detNo){

	for ( int c = 0 ; c < detNo ; c += 1 ){
		energy[c] = channel[c] * aa[c] + bb[c];
	}
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
		float slope[4] = { 1.05 , 1.05 , 0.95 , 0.95 };
		float offset[4] = {-20 , 20 , -20 , 20};

		Calibrator( detectorEnergy , energy , slope , offset , 4 );

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

	ofstream results("calibrated3.dat");

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
