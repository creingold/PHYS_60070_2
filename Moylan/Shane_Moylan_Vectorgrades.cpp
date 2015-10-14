/*Shane Moylan
 * 10/14/15
 * Analyzing grades using vectors and algorithms
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <math.h>

using namespace std;

//define a function that generates a random number from a Gaussian distribution
float Gaussian(float mean, float stdev){
        float R1;
        R1 = (float)rand()/(float)(RAND_MAX);
        
        float R2;
        R2 = (float)rand()/(float)(RAND_MAX);
        
        return mean + stdev*cos(3.14159265359*R1)*sqrt(-log(R2));
}

//define boolean functions to act as arguments to the count_if algorithm
bool IsA(int i){
        return (i >= 94);
}
bool IsAm(int i){
        return (i < 94 and i >= 91);
}
bool IsBp(int i){
        return (i < 91 and i >= 88);
}
bool IsB(int i){
        return (i < 88 and i >= 82);
}
bool IsBm(int i){
        return (i < 82 and i >= 79);
}
bool IsCp(int i){
        return (i < 79 and i >= 76);
}
bool IsC(int i){
        return (i < 76 and i >= 70);
}
bool IsCm(int i){
        return (i < 70 and i >= 67);
}
bool IsD(int i){
        return (i < 67 and i >= 64);
}
bool IsF(int i){
        return (i < 64);
}

int main(){
        srand(time(0));
        float randScore = 0;
        
        vector<float> vScores;
        
        for(int i=0; i<100; i++){
                randScore = Gaussian(75, 25);
                while(randScore >= 100 or randScore <= 0)  //run the Gaussian function until I get a score between 0 and 100
                        randScore = Gaussian(75, 25);
                
                vScores.push_back(randScore);                
        }
        
        // print scores:
        //for (int j = 0; j < vScores.size() ; j++)
                //cout << vScores.at(j) << endl;
        
        float sumbefore = 0;
        
        //add up all scores before the curve
        for (int k = 0; k < vScores.size() ; k++)
                sumbefore += vScores.at(k);
        
        //use count_if to count the number of students that obtained each letter grade
        int Acount = count_if(vScores.begin(), vScores.end(), IsA);
        int Amcount = count_if(vScores.begin(), vScores.end(), IsAm);
        int Bpcount = count_if(vScores.begin(), vScores.end(), IsBp);
        int Bcount = count_if(vScores.begin(), vScores.end(), IsB);
        int Bmcount = count_if(vScores.begin(), vScores.end(), IsBm);
        int Cpcount = count_if(vScores.begin(), vScores.end(), IsCp);
        int Ccount = count_if(vScores.begin(), vScores.end(), IsC);
        int Cmcount = count_if(vScores.begin(), vScores.end(), IsCm);
        int Dcount = count_if(vScores.begin(), vScores.end(), IsD);
        int Fcount = count_if(vScores.begin(), vScores.end(), IsF);
        
        //print calculated quantities before the curve
        //cout << "The highest grade is " << *min_element(vScores.begin(), vScores.end()) << endl;
        //cout << "The lowest grade is " << *max_element(vScores.begin(), vScores.end()) << endl;
        //cout << "The average grade is " << sumbefore/vScores.size() << endl;
        cout << "Grade Distribution before the curve:" << endl;
        cout << "A:\t" << Acount << endl;
        cout << "A-:\t" << Amcount << endl;
        cout << "B+:\t" << Bpcount << endl;
        cout << "B:\t" << Bcount << endl;
        cout << "B-:\t" << Bmcount << endl;
        cout << "C+:\t" << Cpcount << endl;
        cout << "C:\t" << Ccount << endl;
        cout << "C-:\t" << Cmcount << endl;
        cout << "D:\t" << Dcount << endl;
        cout << "F:\t" << Fcount << endl;
        cout << endl;
        
        vector<float> curvedGrades(vScores);
        
        int curvecount = 0;
        
        //loop until there are at least as many people with grades above a C+ as have a C+ or lower
        while (Cpcount + Ccount + Cmcount + Dcount + Fcount >= Bmcount + Bcount + Bpcount + Amcount + Acount){
                
                //curve grades by 2 points
                for (int i=0; i<curvedGrades.size(); i++)
                        curvedGrades.at(i) += 2;
                
                //recount letter grades
                Acount = count_if(curvedGrades.begin(), curvedGrades.end(), IsA);
                Amcount = count_if(curvedGrades.begin(), curvedGrades.end(), IsAm);
                Bpcount = count_if(curvedGrades.begin(), curvedGrades.end(), IsBp);
                Bcount = count_if(curvedGrades.begin(), curvedGrades.end(), IsB);
                Bmcount = count_if(curvedGrades.begin(), curvedGrades.end(), IsBm);
                Cpcount = count_if(curvedGrades.begin(), curvedGrades.end(), IsCp);
                Ccount = count_if(curvedGrades.begin(), curvedGrades.end(), IsC);
                Cmcount = count_if(curvedGrades.begin(), curvedGrades.end(), IsCm);
                Dcount = count_if(curvedGrades.begin(), curvedGrades.end(), IsD);
                Fcount = count_if(curvedGrades.begin(), curvedGrades.end(), IsF);
                
                curvecount += 2;
        }
        
        float sumafter = 0;
        
        //Add up all the scores after the curve
        for (int k = 0; k < curvedGrades.size() ; k++)
                sumafter += curvedGrades.at(k);
        
        //print grade distribution after the curve
        cout << "Grade distribution after the curve:" << endl;
        cout << "A:\t" << Acount << endl;
        cout << "A-:\t" << Amcount << endl;
        cout << "B+:\t" << Bpcount << endl;
        cout << "B:\t" << Bcount << endl;
        cout << "B-:\t" << Bmcount << endl;
        cout << "C+:\t" << Cpcount << endl;
        cout << "C:\t" << Ccount << endl;
        cout << "C-:\t" << Cmcount << endl;
        cout << "D:\t" << Dcount << endl;
        cout << "F:\t" << Fcount << endl;
        cout << endl;
        
        //print after-curve statistics
        cout << "The lowest curved grade is " << *min_element(curvedGrades.begin(), curvedGrades.end()) << endl;
        cout << "The highest curved grade is " << *max_element(curvedGrades.begin(), curvedGrades.end()) << endl;
        cout << "The average curved score is " << sumafter/curvedGrades.size() << endl;
        
        cout << "The curve was " << curvecount << " points" << endl;
        return 0;
}