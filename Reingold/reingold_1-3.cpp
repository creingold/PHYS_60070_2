#include<iostream>
#include<math.h>
using namespace std;

int ReadNumber(){

	int number;
	cout << "Please give me integer.  I love integer." << endl;
	cin >> number;

	return number;
}

int WriteAnswer( int nAnswer ){
	 return nAnswer;
}

int main(){

	int nAnswer = ReadNumber();
	cout << "Now I has the integer " << WriteAnswer( nAnswer ) <<".  Yay." << endl;

	return 0;

}
