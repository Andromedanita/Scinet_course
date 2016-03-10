// Anita Bahmanyar
// Main code

#include <iostream>
#include <fstream>
#include <rarray>
#include <rarrayio>
#include <complex>
#include <fftw3.h>
#include <cblas.h>
#include <math.h>
#include <string>
#include "funcs.h"

using namespace std;


int main(){
  // Reading the Gravitational Wave file and outputing the signal values
  rarray<complex<double>,1> GW_signal = read_data("/home/b/bovy/bahmanya/Assignments/hw6_7/gwdata/","GWprediction.rat");
  rarray<complex<double>,1> g = Fourier_Trans(GW_signal); // Computing the Fourier transform of GW file
  rarray<double,1>          G = power_spec(g); // computing the power spectrum of the GW file

  string num;        // the number representing the name of the detection file (01-32)
  string filename;   // name of the detection file name to read inside the for loop
  int    nfile = 32; // number of the detection files
  rarray<double,1> correlation_array(nfile); // an array to hold correlation values of GW file with each detection file

  // writing the correlation output to a txt file
  ofstream fout("correlattion_values.txt");
  // writing header for the output file
  fout << "#number" << "\t" << "Correlation Coefficient" << endl;
  
  for (int k=1; k<=nfile;k++){
    // if condition to make the filename consistent with one digit (detection01..detection09)
    if (k < 10){
      num = "0" + to_string(k);
      cout <<  " num is "<< num << endl; 
    }
    // making the file name that are two digits (detection11-detection32)
    else{
      num = to_string(k);
      cout <<  " num is "<< num << endl;
    }
    
    filename = "detection" + num +  ".rat"; // filename
    
    // each of the detection files
    rarray<complex<double>,1> detection = read_data("/home/b/bovy/bahmanya/Assignments/hw6_7/gwdata/",filename);
    rarray<complex<double>,1> f = Fourier_Trans(detection); // Fourier transform of each detection files

    rarray<double,1> F = power_spec(f); // power spectra of each of the detection files

    double C = corr(F, G); // correlation coefficient between GW file and each detection file

    cout << "correlation is:" << C << "\n" << endl; // printing out the correlation value
    correlation_array[k-1] = C; // adding the correlation coefficient to the correlation array
    
    // writing out to the file
    fout << num << "\t" << C << endl;
  }

  // closing the file
  fout.close();
  
  // opening another txt file to write the 5 maxima to it
  ofstream file_out("five_maxima.txt");
  
  int num_max = 5; // number of maximum values to be found
  // defining a max_array array to hold the five maximum values of the
  // correlation coefficient
  rarray<double,1> max_array(num_max);
  double max_val  = 0; // initial maximum value
  int    maxIndex = 0; // initial index of the maximum value
  
  // writing header for the max file
  file_out << "#Max number" << "\t" << "detection file number" << "\t"  << "maximum value" << endl;

  // finsing the first num_max maximum values which is 5 here
  for (int i=0; i < num_max ; i++){
    // looping over all values of the correlation array
    for(int j =0 ; j < nfile ; j++){
      // finding the maximm value
      if(correlation_array[j]>max_val){
	max_val = correlation_array[j];
	maxIndex  = j;
      }
    }
    // printing out the number of the maximum, which detection it belongs to and the maximum value
    cout << i+1 << ") maximum value found at detection number " << maxIndex+1  << " with correlation value of " << max_val << endl;

    // writing values to the file
    file_out << i+1 << "\t \t" << maxIndex+1 << "\t \t \t" << max_val << endl;

    max_val = 0; // setting the max_val to zero again to go over the loop for other correlation values
    correlation_array[maxIndex] = 0;//  setting the maximum value in correlation array to 0 so that we can find the next maximum value
    maxIndex = 0; // setting maximum index to 0 to go over the loop for other correlation values
  }
  
  return 0;
}
