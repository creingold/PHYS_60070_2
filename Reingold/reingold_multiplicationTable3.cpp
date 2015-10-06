/*
Craig Reingold
9/16/15
Multiplication Table 3

This code will calculate the results of integer multiplication between 1 and 9

The code will write output to a file, and then flush the output every time the multiplier is incremented.

This is the one that asks the user for input
*/

#include<iostream>
#include<fstream>
#include<cstdlib>
#include<iomanip>
#include<string>

using namespace std;

int firstHalf(){
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

int secondHalf(){
	// Using fstream to append the previous file
	fstream fInOut("multTable.dat" , fstream::in | fstream::out | fstream::app );		

	//Now check if file was opened properly
	if (!fInOut){
		cout << "multTable.dat could not be opened for writing the second half of the table" << endl;
		exit(1);
	}

	//Write the second half of the file
	for ( int j = 10 ; j < 20 ; j ++ ){
		for ( int k = 1 ; k < 10 ; k ++ ){
			fInOut << setfill('0') << setw(3) << j*k << " ";
		}
	
		fInOut << endl;
		fInOut.flush();
	}

	fInOut.close();
	return 0;
}

int userInputPart(){
	// Opening the multiplication table from the first half as a read only, and checking it opened
	ifstream multTable("multTable.dat");

	if (!multTable){
		cout << "multTable.dat could not be opend for reading" << endl;
		exit(1);
	}

	//Prompt the user for input 

	int firstNum, secondNum;

	cout << "Well, well, well ... Look what the cat dragged in ..." << endl;
	cout << "You got a lot of nerve showing up here ... especially after what happened last time ... " << endl;

	cout << "Let's just get this over with. Pick a number between 1 and 9." << endl; 
	cin >> firstNum;

	//Checking whether the input is acceptable
	
	while ( firstNum <= 0 or firstNum >= 10  or cin.fail() ){
		cout << "That ain't gonna cut it, partner.  Try again." << endl;
		cin.clear();
		cin.ignore(256, '\n');
		cin >> firstNum;
	}

	cout << "That's a start.  Now pick a number to multiply that first number by." << endl;
	cout << "Between 1 and 19 only. Pick wisely." << endl << "Remember, my wife died because of your mistakes in Argentina." << endl;
	cin >> secondNum;

	if (cin.fail() ) {
		cout << "If I had my six-shooter on me right now ... " ;
		for ( int q = 0 ; q < 4 ; q++ ){
			cout << " ... " << endl;
		}
		cout << "... also if I wasn't confined to this here magic box ... " << endl;
	}

	while ( secondNum < 1 or secondNum > 19 ){
		cout << "YOU MOCKIN' ME, PARD'NER?!?" << endl;
		cout << "If I had my six-shooter on me right now " ;
		for ( int q = 0 ; q < 4 ; q++ ){
			cout << " ... " << endl;
		}
		cout << "... also if I wasn't confined to this here magic box ... just try again ... " << endl;
		cin.clear();
		cin.ignore(256, '\n');
		cin >> secondNum;
	}

	//for debugging
	//cout << firstNum << endl << secondNum << endl;

	//Reading the secondNum line and the firstNum element in that line

	string readString;
	for ( int m = 0; m < (secondNum - 1) ; m++ ){
		getline(multTable, readString);
	}

	multTable.seekg(4*(firstNum - 1), ios::cur);

	int multAnswer;
	multTable >> multAnswer;

	cout << "Your answer is " << multAnswer << ".  Now get out of here, before I change my mind ... " << endl;

	return 0;
}

int main(){
	firstHalf();
	secondHalf();
	userInputPart();
	return 0;
}	
