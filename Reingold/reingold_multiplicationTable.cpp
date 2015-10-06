/*
Craig Reingold
9/16/15
Multiplication Table

This code will calculate the results of integer multiplication between 1 and 9

The code will write output to a file, and then flush the output every time the multiplier is incremented.
*/

#include<iostream>
#include<fstream>
#include<cstdlib>
#include<iomanip>

using namespace std;

int main(){
	// ofstream is used for writing files
	ofstream fOut("multTable.dat");

	//Always check if the file was opened properly
	if (!fOut){
		cout << " multTable.dat could not be opened for writing!" << endl;
		exit(1);
	}

	//Write the numbers to a file
	for ( int j = 1 ; j < 10 ; j++ ){
		for ( int k = 1 ; k < 10; k++ ){
			fOut << setfill('0') << setw(3) << j*k << " ";
		}
		
		fOut << endl;
		fOut.flush();
	}

	fOut.close();

	return 0;


}
