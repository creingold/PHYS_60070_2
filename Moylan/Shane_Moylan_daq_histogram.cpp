/*
Shane Moylan
10/07/15
Energy Histograms
*/

#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;

int main(){
        ifstream getdata("week6_data.dat");     //access data file
    
        if (!getdata){
                cout << "week6_data.dat could not be opened" << endl; //make sure file is accessed
                exit(1);
        }
        
        float hists[2][1000] = {0};  //initialize both histograms to zero (I made the two histograms into one array of histograms to simplify later code
        
        int detNo = 0;
        
        float* buffer = new float [210];  //make dynamically allocated array
        
        while(!getdata.eof()){  //loop over entire file
                for (int i=0; i<210; i++)
                        getdata >> buffer[i];  //assign raw data of one line to an array
                
                for (float *pbuffer = buffer+10; pbuffer < buffer + 210; pbuffer++){  //skip header
                        
                        if (*pbuffer == 0 || *pbuffer == 1)  //figure out which detector to assign to histogram bins
                                detNo = *pbuffer;
                        
                        else{
                                for (int ii=0; ii<1000; ii++){
                                        if (*pbuffer > (ii/2.00 - 0.25) && *pbuffer <= (ii/2.00 + 0.25)){  //1000 bins of width 0.5, centered around the index
                                                hists[detNo][ii]++;
                                                break;
                                        }
                                }
                        }
                }
        }
        
        delete [] buffer;

        ofstream writedata("histograms.dat");   //create new file to write data to
        
        if (!writedata){
                cout << "histograms.dat could not be opened for writing" << endl;  //make sure file is opened properly
                exit(1);
        }
        
        for (int k=0; k<1000; k++)  
                writedata << k/2. << ' ' << hists[0][k] << ' ' << hists[1][k] << endl;  //write data to file in the format requested
        return 0;
}