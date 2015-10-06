/*
Craig Reingold
09/02/2015
Fibonacci Sequence

This code will print out the first 25 Fibonacci Numbers, and the Fibonacci quotient for each number.
The Fibonacci quotient is the current number divided by the previous number.

The cout precision will be set to 10 and the cout width will be set to 20
*/

#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include<math.h>

using namespace std;

//Global Variable: This is the number of Fibonacci numbers the code will output.
int numbersToBeShown = 25;

float Fibonacci( int iNumber )
//This function will allow the program to calculate the nth (iNumber) fibonacci number by setting the initial conditions, and then finding the nth number recursively.
{
	cout << setprecision (10);
	cout << setw(20);

	float Fib;
	switch ( iNumber )
	//This says that f(0) = f(1) = 1.  f(n) = f(n-1) + f(n-2) for all n >= 2.
	{
		case 0:
			Fib = 1;
			break;

		case 1:
			Fib = 1;
			break;

		default:
			Fib = Fibonacci ( iNumber - 1 ) + Fibonacci ( iNumber - 2 );
	
	}

	return Fib;

}

int main()
{
	cout << setprecision(10);
	cout << setw(20);
	
	cout << "Fibonacci number 0 is " << setprecision(10) << setw(20) << Fibonacci(0) << endl << endl;

	int i = 1;
	while ( i < numbersToBeShown + 1 )
	//Here, we will calculate the ith Fibonacci number and quotient, and then print them to the screen.  Loop will display numberToBeShown.
	{
		float CurrentFib = Fibonacci( i );
		float PrevFib = Fibonacci( i - 1 );
		
		float QuotFib = CurrentFib / PrevFib;

		cout << "Fibonacci number " << i << " is " << setprecision(10) 
			<< setw(20) << CurrentFib << endl;

		cout << "Fibonacci quotient " << i << " is " << setprecision(10) 
			<< setw(20) << QuotFib << endl << endl;

	i += 1;

	}

	return 0;
}
