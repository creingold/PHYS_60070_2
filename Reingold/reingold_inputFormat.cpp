/*
Craig Reingold
09/11/15
Input format

	This code will collect the following information from the user:
		First name and last name
		Phone number in the format: ### - ### - ####
		City of residence.

	Read the full name into the C-string, then extract the first name to a C-string and change the first letter to an uppercase
	Read phone number into C-string, make sure the format is correct.
	Check if the city of residence is South Bend, print 'Go Irish', else print out the greeting message:
	"(Name), welcome to South Bend

*/

#include<iostream>
#include<cstdlib>
#include<cctype>

using namespace std;

int main(){

	char nameFirst[256], nameLast[256];
	cout << "Hello.  Welcome to program.  What is your full name, friend?" << endl;
	cin.getline( nameFirst, 255, ' ' );
	cin.getline( nameLast, 255 );

	bool bFirst = isalpha( nameFirst[0] );
	bool bLast = isalpha( nameLast[0] );

	bool bFirst2 = islower( nameFirst[0] );
	bool bLast2 = islower( nameLast[0] );

	switch ( bFirst ){
		case true:
			switch ( bFirst2 ){
				case true:
					toupper( nameFirst[0] );
					break;
				case false:
					break;
			}
			break;
		case false:
			cout << "Your name has broken me.  Terrible.  Take a Lap." << endl;
			main();
	}

	switch ( bLast ){
		case true:
			switch ( bLast2 ){
				case true:
					toupper( nameLast[0] );
					break;
				case false:
					break;
			}
			break;
		case false:
			cout << "Your name has broken me.  Terrible.  Take a Lap." << endl;
			main();
	}

	//Getting phone number
	char phoneNumber[13];
	char numberTemplate[12] = {'#','#','#','-','#','#','#','-','#','#','#','#'};
	cout << "You are quite attractive, " << nameFirst << " " << nameLast << "." << endl <<"I will have phone number in ###-###-#### format now.  Give me now?" << endl;

	cin.getline( phoneNumber , 12 );

	
	return 0;
}

