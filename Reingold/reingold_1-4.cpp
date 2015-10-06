/*
Craig Reingold
Unit Converter
09/01/15

This code will create a matrix of conversion factors, select the proper conversion 
factor based on the user's input, and then convert the given unit.
*/

#include<iostream>
#include<iomanip>
#include<math.h>
#include<stdlib.h>

using namespace std;

//Declaring Global Variables

int cm_m = 100; // Centimeters per meter
int m_km = 1000; // Meters per kilometer

int in_ft = 12; // Inches per foot
int ft_mi= 5280; // Feet per mile

float cm_in = 2.54; // Centimeters per inch

//Creating arrays with unit conversions built in

float inch_convert [6] = { 1.0, 1.0/in_ft , 1.0/(in_ft * ft_mi) , cm_in , cm_in/cm_m , cm_in/(cm_m * m_km)};
float foot_convert [6] = { in_ft, 1.0 , 1.0/(ft_mi) , cm_in*in_ft , cm_in*in_ft/cm_m , cm_in*in_ft/(cm_m * m_km)};
float mile_convert [6] = { in_ft*ft_mi, ft_mi , 1.0 , cm_in*in_ft*ft_mi , cm_in*in_ft*ft_mi/cm_m , cm_in*in_ft*ft_mi/(cm_m * m_km)};

float cm_convert [6] = {1.0/cm_in , 1.0/(cm_in*in_ft) , 1.0/(cm_in*in_ft*ft_mi) , 1.0 , 1.0/cm_m , 1.0/(cm_m * m_km)};
float m_convert [6] = { cm_m/cm_in , cm_m/(cm_in*in_ft) , cm_m/(cm_in*in_ft*ft_mi) , cm_m , 1.0 , 1.0/( m_km)};
float km_convert [6] = { cm_m*m_km/cm_in , cm_m*m_km/(cm_in*in_ft) , cm_m*m_km/(cm_in*in_ft*ft_mi) , cm_m*m_km , m_km , 1.0};

//In this area, functions will be defined that will later be called in main()

void Introduction(){
	//A simple output that shows the user the available units

	cout << "Welcome to unit converter.  You can convert between the following units: " << endl;

	cout << endl << "\t [1] inches \t [4] centimeters" << endl << "\t [2] feet \t [5] meters" << endl << "\t [3] miles \t [6] kilometers" << endl << endl;
}

int unitSelect(){
	//Used to get units from user
	int selection;
	string outString;	
	
	cin >> selection;
	
	if (selection != 1 and selection !=2 and selection != 3 and selection != 4 and selection != 5 and selection != 6)
	{
		cout << "Terrible, take a lap"<< endl;
		exit(0);
	}

	else if ( selection == 1 ) { outString = "inches" ;}
	else if ( selection == 2 ) { outString = "feet" ;}
	else if ( selection == 3 ) { outString = "miles" ;}
	else if ( selection == 4 ) { outString = "centimeters" ;}
	else if ( selection == 5 ) { outString = "meters"; }
	else if ( selection == 6 ) { outString = "kilometers" ;}

	else {return 0;}

	cout << "You have selected " << outString << "." << endl;
	return selection;
}

string UnitIntToString(int iValue){
	//Used to make the output look nicer

	string outString;	

	if ( iValue == 1 ) { outString = "in" ;}
	else if ( iValue == 2 ) { outString = "ft" ;}
	else if ( iValue == 3 ) { outString = "mi" ;}
	else if ( iValue == 4 ) { outString = "cm" ;}
	else if ( iValue == 5 ) { outString = "m"; }
	else if ( iValue == 6 ) { outString = "km" ;}
	else { exit (0); } 

	return outString;
}



//This is the main program that will run

int main(){
	
	Introduction();

	int select0;
	cout << "Select the integer from the list above for the units you would like to convert from." << endl;
	select0 = unitSelect();

	int select1;
	cout << "Select the integer from the list above for the units you would like to convert to." << endl;
	select1 = unitSelect();

	//This step will create a matrix of conversion factors

	float conversionMatrix[6][6];
	for (int i = 0 ; i < 6 ; i += 1){
		conversionMatrix[0][i] = inch_convert[i];
		conversionMatrix[1][i] = foot_convert[i];
		conversionMatrix[2][i] = mile_convert[i];
		conversionMatrix[3][i] = cm_convert[i];
		conversionMatrix[4][i] = m_convert[i];
		conversionMatrix[5][i] = km_convert[i];
	}
	
	float toConvert;

	cout << "What is the number you would like converted?" << endl;
	cin >> toConvert;
	
	float converted = toConvert * conversionMatrix[select0 - 1][select1 -1];

	string string1 = UnitIntToString(select0);
	string string2 = UnitIntToString(select1);

	cout << toConvert << " " << string1 << " is equal to " << converted << " " << string2 << endl;

	return 0;

}