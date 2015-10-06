/*
Craig Reingold
10/02/15
Q-Value Calculator

This program will allow the user to specify a target, an incident projectile, and a reaction Q-Value.
It will then output the possible reaction chains, marking specifically which ones are possible.

*/

#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstdlib>
#include<math.h>
#include<string>

using namespace std;

// This will allow the program to store various parameters inherent to the nucleus as a structure.  It's basically defining a nucleus in terms of 4 parameters, and it allows the program to use this definition to understand what a nucleus is.

struct nucleus {
	int A;
	int Z;
	char Name[2];
	double massExcess;
};

// Defining the photon in terms of the 'nuclear' struct

const nucleus Photon = { 0 , 0 , 'g' , 0 };

// This fucntion will be called if the user chooses to look up their mass by the nucleus's A and Z numbers.  It will return the line number in atomicMass.dat that the target's information can be found on.

int findMassByAZ(){
	int massNum, protonNum;

	cin >> massNum;

	while ( cin.fail() or massNum <= 0 ){
		cout << "ERROR: improper mass number (A)" << endl << "Input mass number (A): ";
		cin.clear();
		cin.ignore(256, '\n');
		cin >> massNum;
	}

	cout << "Input target proton number (Z): ";
	cin >> protonNum;

	while ( cin.fail() or protonNum < 0 ){
		cout << "ERROR: improper proton number (Z)" << endl << "Input proton number (Z): ";
		cin.clear();
		cin.ignore(256, '\n');
		cin >> protonNum;
	} 

//	cout << protonNum << '\t' << massNum << endl;

	ifstream massTable("/home/craig/Documents/CompDataAnal/atomicMass.dat");
	if ( !massTable ){
		cout << "FATAL ERROR: Could not find atomic mass table.  Exiting Now." << endl;
		exit(1);
	}

	int lineNumber, lineZ , lineA;

	for ( int line = 0 ; line < 3394 ; line += 1 ){
		massTable.seekg( 0 , ios::beg );

		if ( line == 3393){
			cout << "Could not find your target.  Check inputs and try again." << endl;
			exit(1);
		}

		string dummyString;
		for ( int j = 0 ; j < 39 + line ; j++){
			getline(massTable, dummyString);
		}	

		massTable.seekg(10, ios::cur);
		
		massTable >> lineZ >> lineA;

		//cout << lineZ << '\t' << lineA << endl;

		if ( lineA == massNum and lineZ == protonNum ){
			//cout << "Target Acquired" << endl;
			lineNumber = line + 39;
			break;
		}
	}

	massTable.close();
	return lineNumber;

}


// This function will construct a nucleus if it is given a line number in the mass table.

nucleus getInfo( const int lineNum ){
	ifstream massTable("/home/craig/Documents/CompDataAnal/atomicMass.dat");
	if ( !massTable ){
		cout << "FATAL ERROR: Could not find atomic mass table.  Exiting Now." << endl;
		exit(1);
	}
	
	massTable.seekg( 0 , ios::beg );
	string dummyString;
	for ( int i = 0 ; i < lineNum ; i++ ){
		getline(massTable , dummyString);
	}
	
	massTable.seekg(10, ios::cur);

	nucleus TargetNucleus;

	massTable >> TargetNucleus.Z >> TargetNucleus.A >> TargetNucleus.Name;

	massTable.seekg( 7 , ios:: cur );
	
	massTable >> TargetNucleus.massExcess;

//	TargetNucleus.massMeV =  ( TargetNucleus.Z * massProtonKeV + ( TargetNucleus.A - TargetNucleus.Z ) * massNeutronKeV - TargetNucleus.massExcess) / (double) 1000;

	massTable.close();
	return TargetNucleus;

}

// Used to calculate what's left after the reaction

nucleus Reactor( nucleus Target , nucleus Beam , nucleus Ejectile , int numEjected = 1){

	nucleus Product;
	int ProductLine;
	int ProductZ, ProductA;

	ProductZ = Target.Z + Beam.Z - numEjected * Ejectile.Z;
	ProductA = Target.A + Beam.A - numEjected * Ejectile.A;
	
	ifstream massTable("/home/craig/Documents/CompDataAnal/atomicMass.dat");
	if ( !massTable ){
		cout << "FATAL ERROR: Could not find atomic mass table.  Exiting Now." << endl;
		exit(1);
	}

	int lineZ , lineA;


	for ( int line = 0 ; line < 3394 ; line += 1 ){
		massTable.seekg( 0 , ios::beg );

		if ( line == 3393){
			Product.Z = -100;
			Product.A = -100;
			Product.Name[0] = 'Q';
			Product.Name[1] = 'Q';
			Product.massExcess = 0;
			break;		
		}

		string dummyString;
		for ( int j = 0 ; j < 39 + line ; j++){
			getline(massTable, dummyString);
		}	

		massTable.seekg(10, ios::cur);
		
		massTable >> lineZ >> lineA;

		//cout << lineZ << '\t' << lineA << endl;

		if ( ProductA == lineA and ProductZ == lineZ ){
			//cout << "Target Acquired" << endl;
			ProductLine = line + 39;
			Product = getInfo(ProductLine);
			break;
		}
	}


	return Product;

}

// Pretty obvious what this guy does ...

double QCalculator ( nucleus Target , nucleus Project , nucleus Product , nucleus Eject , int numEject = 1 ){
	double QValue = Target.massExcess + Project.massExcess -  Product.massExcess - numEject * Eject.massExcess;
	return QValue;
}

int main(){

// Getting Parameters from user

	cout << "Welcome to hell! I mean . . . QCalc!" << endl;
	cout << "Input the target's mass number (A): ";

	int foundTarget = findMassByAZ();
//	cout << foundTarget << endl;

	cout << "Input the projectile's mass number (A): ";
	int foundProjectile = findMassByAZ();
//	cout << foundProjectile << endl;



	double QLow , QHigh;

	cout << "Input the Q-Value Lower Bound (MeV) : ";
	cin >> QLow;
	while( cin.fail() ){
		cout << "ERROR: improper Q-Value. Input Q-Value Lower Bound (MeV): ";
		cin.clear();
		cin.ignore( 256 , '\n' );
		cin >> QLow;
	}
	
	cout << "Input the Q-Value Upper Bound (MeV) : ";
	cin >> QHigh;
	while( cin.fail() or QHigh <= QLow){
		cout << "ERROR: improper Q-Value. Input Q-Value Upper Bound (MeV): ";
		cin.clear();
		cin.ignore( 256 , '\n' );
		cin >> QHigh;
	}

// Constructing the target and projectile

	nucleus Target , Projectile;

	Target = getInfo( foundTarget );
	Projectile = getInfo( foundProjectile );

	if ( Target.Z == 0 and Target.A == 1 and Projectile.Z == 0 and Projectile.A == 1){
		cout << "Neutron - neutron reactions are not possible.  Need at least one proton" << endl;
		exit(1);
	}

/*
For reference:
n = 39
p = 40
d = 41
t = 42
He3 = 43
a = 46
*/

	nucleus Product;
	double QValue;
	
	char filename[256];
	sprintf( filename , "QCalcResult_%d%s-%d%s.dat" , Target.A , Target.Name , Projectile.A , Projectile.Name );
	ofstream outfile(filename);
	if ( !outfile ){
		cout << " FATAL ERROR : cannot open output file. Exiting." << endl;
		exit(1);
	}

	char outputString[256];

	Product = Reactor( Target , Projectile , Photon );
	if ( Product.Z != -1 ){
		QValue = QCalculator(Target, Projectile , Product , Photon );
		sprintf ( outputString , "%d%s + %d%s -> %d%s + ( %s ) ( QValue = %f keV )" , Target.A , Target.Name , Projectile.A , Projectile.Name , Product.A , Product.Name , Photon.Name , QValue );

		cout << outputString;

		if ( QLow * 1000 <= QValue and QHigh * 1000 >= QValue ){
			cout << " * " ;
			outfile << outputString << '\n';
		}
		cout  << endl;
	}


	for ( int c = 39 ; c < 44 ; c++ ){
		for ( int d = 1 ; d < 4 ; d++ ){
			nucleus Ejectile = getInfo(c);
		//	cout << d << ' ' << Ejectile.A << Ejectile.Name << endl;
			Product = Reactor( Target , Projectile , Ejectile , d);
		//	cout << Product.A << Product.Name << endl;
			if ( Product.Z != -100 ){
				QValue = QCalculator(Target, Projectile , Product , Ejectile , d);
				sprintf ( outputString , "%d%s + %d%s -> %d%s + %d( %d%s ) ( QValue = %f keV )" , Target.A , Target.Name , Projectile.A , Projectile.Name , Product.A , Product.Name , d , Ejectile.A , Ejectile.Name , QValue );

				cout << outputString;

				if ( QLow * 1000 <= QValue and QHigh * 1000 >= QValue and Product.Z != -100 ){
					cout << " * " ;
					outfile << outputString << '\n';	
				}
				cout << endl;		
			}
		}
	}

	for ( int e = 1; e < 4 ; e++ ){
		nucleus Ejectile = getInfo(46);
		Product = Reactor ( Target , Projectile, Ejectile , e);
	//	cout << Product.A << Product.Name << endl;
		if ( Product.Z != -100 ){
			QValue = QCalculator(Target, Projectile , Product , Ejectile , e);
			sprintf ( outputString , "%d%s + %d%s -> %d%s + %d( %d%s ) ( QValue = %f keV )" , Target.A , Target.Name , Projectile.A , Projectile.Name , Product.A , Product.Name , e , Ejectile.A , Ejectile.Name , QValue );
			if ( QLow * 1000 <= QValue and QHigh * 1000 >= QValue and Product.Z != -100 ){
				cout << " * " ;
				outfile << outputString << '\n';
			}
			cout << endl;
		}
	}

	return 0;
}
