/*Shane Moylan
10/7/15
Q-value calculator*/

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;
        
const double MeVperU = 931.5;

double getmass(int Zproj,int Aproj){  //Define a function to take the masses from the AME2012 table
        double mass;
                        
        int *Afile = new int;  //create dynamically allocated variables to hold A, Z, and atomic mass values from the file
        int *Zfile = new int;
        
        double *m1 = new double;  //two mass values are needed because of the formatting
        double *m2 = new double;
        
        ifstream fIn("mass.bin"); //open mass table
        
        if (!fIn){
                cout << "mass.bin could not be opened" << endl; //make sure it opens properly
                exit(1);
        }
        
        string line;
        for (int i=0; i<39; i++)
                getline(fIn, line);  //skip the 39-line header
        
        while(!fIn.eof()){  //loop over whole file
                fIn.seekg(11, ios::cur);  //put cursor in front of Z and A values, which follow each other
        
                fIn >> *Zfile;
                fIn >> *Afile;
        
                if (*Afile == Aproj and *Zfile == Zproj){  //if A, Z values from the file match user inputs, grab the mass
                        fIn.seekg(77, ios::cur);
                        fIn >> *m1;
                        fIn >> *m2;
                        
                        mass = *m1 + *m2/1000000;
                        break;
                }
                
                getline(fIn, line);  //go to next line
        }
        
        if (fIn.eof()){  //output error message if the A and Z values never match user inputs
                cout << "This nucleus doesn't exist or wasn't tabulated" << endl;
                exit (1);
        }
        delete Afile;
        delete Zfile;
        delete m1;
        delete m2; //free memory of dynamically allocated variables
        
        return mass;
}

double *Qcalcs(int Z, int A, int projectile){ //This funciton will output a pointer pointing to an array of all 8 qvalues
        double *Qvals = new double[8];
        int *proj_Z = new int; //these hold the projectile Z and A values
        int *proj_A = new int;
        
        double *products_mass = new double; //This will hold the total mass of the reaction products
        
        switch(projectile){  //turn user input for the projectile into usable A and Z values which will give masses
                case 1: //proton
                        *proj_Z = 1;
                        *proj_A = 1;
                        break;
                case 2: //deuterium
                        *proj_Z = 1;
                        *proj_A = 2;
                        break;
                case 3: //tritium
                        *proj_Z = 1;
                        *proj_A = 3;
                        break;
                case 4: //He-3
                        *proj_Z = 2;
                        *proj_A = 3;
                        break;
                case 5: //alpha
                        *proj_Z = 2;
                        *proj_A = 4;
                        break;
                default:
                        cout << "If you got this error, you screwed something up bad" << endl;
        }
        
        
        for (int j = 0; j<8; j++){ //use for loop to create array of Q-values for each possible ejectile
                switch(j){
                        case 0: //gamma
                                *products_mass = getmass(Z + *proj_Z, A + *proj_A);
                                break;
                        case 1: //deuterium
                                *products_mass = getmass(Z + *proj_Z - 1, A + *proj_A - 2) + getmass(1, 2);
                                break;
                        case 2: //tritium
                                *products_mass = getmass(Z + *proj_Z - 1, A + *proj_A - 3) + getmass(1, 3);
                                break;
                        case 3: //neutron
                                *products_mass = getmass(Z + *proj_Z - 0, A + *proj_A - 1) + getmass(0, 1);
                                break;
                        case 4: //2 neutrons
                                *products_mass = getmass(Z + *proj_Z - 0, A + *proj_A - 2) + 2 * getmass(0, 1);
                                break;
                        case 5: //3 neutrons
                                *products_mass = getmass(Z + *proj_Z - 0, A + *proj_A - 3) + 3 * getmass(0, 1);
                                break;
                        case 6: //alpha
                                *products_mass = getmass(Z + *proj_Z - 2, A + *proj_A - 4) + getmass(2, 4);
                                break;
                        case 7: //He-3
                                *products_mass = getmass(Z + *proj_Z - 2, A + *proj_A - 3) + getmass(2, 3);
                                break;
                        default:
                                cout << "How do loops work?" << endl;
                }
                
                Qvals[j] = MeVperU * (getmass(Z, A) + getmass(*proj_Z, *proj_A) - *products_mass);  //apply Q-value formula
        }
        
        delete products_mass;
        delete proj_A;
        delete proj_Z; //free memory of dynamically allocated variables
        
        return Qvals;
}

int main(){
        int Z;
        int A;
        double Qmin;
        double Qmax;
        double *Qvals = 0;
        
        cout << "Target proton number Z:\t";
        cin >> Z;
        
        cout << "Target mass number A:\t";   //prompt user for target A, Z
        cin >> A;
        
        if (Z < 0 or Z > 118 or A < 1 or A > 295 or A < Z){  //check to make sure given A, Z are reasonable
                cout << "Invalid input" << endl;
                exit(1);
        }
        
        int projectile;
        
        cout << "Choose the number corresponding to the projectile:" << endl << "1. proton" << endl << "2. deuterium" << endl << "3. tritium" << endl << "4. Helium-3" << endl << "5. Alpha particle" << endl; //prompt user for projectile
        
        cin >> projectile;
        
        string proj_name;  //convert user input into useful info for output, and check to make sure input is reasonable
        
        switch(projectile){
                case 1:
                        proj_name = "p";
                        break;
                case 2:
                        proj_name = "d";
                        break;
                case 3:
                        proj_name = "t";
                        break;
                case 4:
                        proj_name = "He-3";
                        break;
                case 5:
                        proj_name = "alpha";
                        break;
                default:
                        cout << "Invalid input" << endl;
        }
        
        cout << "Q-value lower bound in MeV:\t";  //prompt user for uper and lower limits for the Q-value
        cin >> Qmin;
        
        cout << "Q-value upper bound in MeV:\t";
        cin >> Qmax;
        
        if (Qmax <= Qmin){ //make sure user input is reasonable
                cout << "Invalid input" << endl;
                exit(1);
        }
        
        Qvals = Qcalcs(Z, A, projectile); //get array of Q-values for given user inputs
        
        string eject_name[8] = {"gamma", "d", "t", "n", "2n", "3n", "alpha", "He-3"}; //give names to corresponding ejectiles
        
        char is_in_range;
        
        ofstream fOut("possible_reactions.dat");   //create new file to write data to
        
        if (!fOut){   //make sure file is opened properly
                cout << "possible_reactions.dat could not be opened for writing" << endl;  
                exit(1);
        }
        
        fOut << "Possible reactions:" << endl; //header for output file
        
        for (int a = 0; a < 8; a++){
                if (Qvals[a] > Qmin and Qvals[a] < Qmax){
                        is_in_range = '*'; //mark reactions within user specified parameters
                        
                        fOut << "(" << eject_name[a] << "," << proj_name << ")" << endl; //write only reactions that meet user requirements to file
                }
                
                else
                        is_in_range = ' ';
                
                cout << is_in_range << "(" << eject_name[a] << "," << proj_name << "):\t" << Qvals[a] << endl; //print out all possible reactions and their corresponding Q-values
        }
        
        return 0;
}