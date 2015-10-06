/*
Craig Reingold
9/15/15
Vector Rotation

This code will allow the user to rotate a vector in three space.
The user will specify the initial vector to be rotated, the number of rotations to be performed, and then axis and corresponding angle of rotation for each rotation they want.  Example below.

>> Initial Vector please
>> 1 1 1
>> How many rotations?
>> 3
>> Axis and angle (in radians) of each rotation
>> x 3.14 y 3.14 z 3.14
>>


*/

#include<iostream>
#include<iomanip>
#include<math.h>
#include<cstdlib>

using namespace std;

const float pi = 3.14159265;
const float degToRad = pi / 180;

int main(){
	//Declaring places to store user input
	
	float vector[3];
	int rotationNumber;

	cout << "Hello again, my good friend.  Vector.  Please give me.  I will rotate it." << endl;
	cin >> vector[0] >> vector[1] >> vector[2];

	cout << "That was delicious.  Thank you.  How many rotates do you want?" << endl;
	cin >> rotationNumber;

	//Declaring places to put the axis of rotation and the corresponding angles

	char axisArray[rotationNumber];
	float angleArray[rotationNumber];

	cout << "Fantastic!  Now I can has the axis of rotation, followed by angle in degrees, of each of your rotations!" << endl;
	for ( int i = 0 ; i < rotationNumber ; i += 1 ){
		cin >> axisArray[i] >> angleArray[i];
	}

	//Now we will perform each of the rotations within this for loop

	for ( int j = 0 ; j < rotationNumber ; j += 1 ){

		float rotMatrix[3][3] = {0};
		for ( int p = 0 ; p < 3 ; p += 1 ){
			for ( int q = 0 ; q < 3 ; q += 1 ){
				rotMatrix[p][q] = 0;
			}
		}
		float alpha = angleArray[j]*degToRad;

		switch(axisArray[j]){
			case 'x':
				rotMatrix[0][0] = 1;
				rotMatrix[1][1] = cos(alpha);
				rotMatrix[2][2] = cos(alpha);
				rotMatrix[2][1] = -sin(alpha);
				rotMatrix[1][2] = sin(alpha);
				break;

			case 'y':
				rotMatrix[1][1] = 1;
				rotMatrix[0][0] = cos(alpha);
				rotMatrix[2][2] = cos(alpha);
				rotMatrix[0][2] = sin(alpha);
				rotMatrix[2][0] = -sin(alpha);
				break;

			case 'z':
				rotMatrix[2][2] = 1;
				rotMatrix[0][0] = cos(alpha);
				rotMatrix[1][1] = cos(alpha);
				rotMatrix[1][0] = -sin(alpha);
				rotMatrix[0][1] = sin(alpha);
				break;

		}

		//This loop will now multiply the rotation matrix with the initial vector
		for ( int k = 0 ; k < 3 ; k += 1 ){
			float toVector = 0;
			for ( int m = 0 ; m < 3 ; m += 1 ){
				toVector = toVector + rotMatrix[k][m]*vector[m];
			}
			
			vector[k] = toVector;

		}

	}

	cout << "Your new vector after rotation is ( " << setprecision(2) << fixed << vector[0] << " " << vector[1] <<  " " << vector[2] << " )" << endl;

	return 0;
}
