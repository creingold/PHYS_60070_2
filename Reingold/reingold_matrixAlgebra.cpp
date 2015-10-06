/*

Craig Reingold
09/09/15
Matrix Algebra

The code will take in two 3x3 matricies from the user.  Then the code will calculate:
	* A^(-1) and B^(-1)
	* Trace(A) and Trace(B)
	* A + B and A - B
	* A*B
*/

#include<iostream>
#include<math.h>
#include<cstdlib>

using namespace std;

void printer( float matrix[3][3] ){
	//A function designed to print matricies, so I don't have to write this out a thousand times.
	for ( int i = 0 ; i <3 ; i += 1 ){
		for ( int j = 0 ; j <3 ; j += 1 ){
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

int main(){

	float A[3][3];
	float B[3][3];

	cout << "Enter your 3x3 matricies now.  Type the first three elements, then hit enter to go to the next row.  Please only enter floats for the matricies." << endl << "Enter A below: " << endl;

	cin >> A[0][0] >> A[0][1] >> A[0][2];
	cin >> A[1][0] >> A[1][1] >> A[1][2];
	cin >> A[2][0] >> A[2][1] >> A[2][2];

	cout << "Now B : " << endl;

	cin >> B[0][0] >> B[0][1] >> B[0][2];
	cin >> B[1][0] >> B[1][1] >> B[1][2];
	cin >> B[2][0] >> B[2][1] >> B[2][2];

	//Declaring arrays to store the answers to be returned.
	float Atranspose[3][3];
	float Btranspose[3][3];
	float AplusB[3][3];
	float AminusB[3][3];

	float traceA = 0;
	float traceB = 0;

	//The following loop will simultaneously calculate the transposed matricies, the trace of each matrix, and the sum and difference of the two matricies.
	for ( int row = 0 ; row <3 ; row += 1 ){
		for ( int column = 0 ; column <3 ; column += 1 ){
			Atranspose[row][column] = A[column][row];
			Btranspose[row][column] = B[column][row];

			AplusB[row][column] = A[row][column] + B [row][column];
			AminusB[row][column] = A[row][column] - B[row][column];

			if ( row == column ){
				traceA += A[row][column];
				traceB += B[row][column];
			}
		}

	}	

	//Now, matrix multiplication with three for loops
	
	float AtimesB[3][3];

	for ( int q = 0 ; q <3 ; q += 1 ){
		for ( int r = 0 ; r <3 ; r += 1 ){
			float elementAtimesB = 0;
			//Summing over the product of all row 'q' elements and column 'r' elements
			for ( int s = 0 ; s <3 ; s += 1 ){
				elementAtimesB += A[q][s] * B[s][r];
			}
			
			AtimesB[q][r] = elementAtimesB;
		}

	}

	//Using the printer function and cout to output the results
	cout << endl << "A transpose = " << endl;
	printer( Atranspose );
	cout << endl << "B transpose = " << endl;
	printer( Btranspose );
	cout << endl << "trace(A) =  " << endl;
	cout << traceA << endl;
	cout << endl << "trace(B) = " << endl;
	cout << traceB << endl;
	cout << endl << "A + B = " << endl;
	printer( AplusB );
	cout << endl << "A - B = " << endl;
	printer( AminusB );
	cout << endl << "A * B = " << endl;
	printer( AtimesB );

	return 0;
}
