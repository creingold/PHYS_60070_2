/*
Craig Reingold 
09/02/2015
Compute Summations

This code will compute the following summations

	1) sin(1.1) + sin(1.3) + sin(1.5) + ... + sin(9.9)
	2) exp(1.1) + exp(1.3) + exp(1.5) + ... + exp(9.9)

where exp(x) is the inverse of ln(x).
*/


#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include<math.h>

using namespace std;

//Declaring Global Variables

double gWhereToStart = 1.1;
double gWhereToStop = 9.9;
double gIncrement = 0.2;

int main()
{

	//Defining some initial iterators and conditions.
	double i = gWhereToStart;
	double sumSin = 0;
	
	double j = gWhereToStart;
	double sumExp = 0;

	//Summing over the sine functions
	while ( i <= gWhereToStop )
	{
		sumSin += sin(i);
		i += gIncrement;
	}

	//Summing over the exponential functions
	while ( j <= gWhereToStop )
	{
		sumExp += exp(j);
		j += gIncrement;
	}

	//And finally, a pretty output
	cout << "sin(1.1) + sin(1.3) + sin(1.5) + ... + sin(9.9) = " << setprecision(10) << sumSin << endl;
	cout << "exp(1.1) + exp(1.3) + exp(1.5) + ... + exp(9.9) = " << setprecision(10) << sumExp << endl;

	return 0;
}
