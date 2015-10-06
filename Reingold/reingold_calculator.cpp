/*
Craig Reingold
09/02/2015
Calculator

This code will take a number (float), an operator (as a character), and another number (float), and perform the operator on these two numbers.

*/

#include<iostream>
#include<stdlib.h>
using namespace std;

float floatInput(){
	//A function to take in a float from the user

	float floatIn;
	cin >> floatIn;
	return floatIn;
}

char charInput(){
	//A function to take in a character from the user
	char charIn;
	cin >> charIn;
	return charIn;
}

int main() {

	//Introduction to the user, and prompt for the first input
	cout << "Welcome to the calculator.  Please input your first number." << endl;
	float firstFloat = floatInput();


	//Prompt user for operator, and do not let the program continue until one of the four given is selected.
	cout << "Enter your operator ( + or - or * or / )" << endl;
	char cOperator = charInput();

	while ( cOperator != '+' and cOperator != '-' and cOperator != '*' and cOperator != '/' )
	{
		cout << "Improper operator.  Please ener your operator ( + or - or * or / )" << endl;
		cOperator = charInput();
	}

	//Prompt user for the second number
	cout << "Enter your second number." << endl;
	float secondFloat = floatInput();

	float fOutput;

	//The actual calculation is done here, with the input operator character determining which arithmatic operation to employ. 
	switch(cOperator)
	{
		case '+':
			fOutput = firstFloat + secondFloat;
			break;

		case '-':
			fOutput = firstFloat - secondFloat;
			break;
		
		case '*':
			fOutput = firstFloat * secondFloat;
			break;

		case '/':
			fOutput = firstFloat / secondFloat;
			break;

		default:
		//default error message
			cout << "Something has gone wrong.  Please check inputs and try again" << endl;
			exit(1);

	}

	//A pretty output
	cout << firstFloat << " " << cOperator << " " << secondFloat << " = " << fOutput << endl;

	return 0;


}
