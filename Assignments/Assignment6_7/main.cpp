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
  rarray<complex<double>,1> GW_signal = read_data("/home/b/bovy/bahmanya/Assignments/hw6_7/gwdata/","GWprediction.rat");
  string num;
  string filename;
  rarray<double,1> correlation_array(32);
  for (int k=1; k<32;k++){
    if (k < 10){
      num = "0" + to_string(k);
      cout <<  " num is "<< num << endl; 
    }
    else{
      num = to_string(k);
      cout <<  " num is "<< num << endl;
    }
    filename = "detection" + num +  ".rat"; 
    rarray<complex<double>,1> detection = read_data("/home/b/bovy/bahmanya/Assignments/hw6_7/gwdata/",filename);
    rarray<complex<double>,1> f = Fourier_Trans(detection);
    rarray<complex<double>,1> g = Fourier_Trans(GW_signal);

    rarray<double,1> F = power_spec(f);
    rarray<double,1> G = power_spec(g);

    double C = corr(F, G);

    cout << "correlation is:" << C << "\n" << endl;
    correlation_array[k] = C;
  }
  
  rarray<double,1> max_array(5);
  double max_val = 0;
  for (int i=1; i<32;i++){
    if(correlation_array[i]>max_val){
      max_val = correlation_array[i];
      int q = 0;
      max_array[q] = max_val;
      q++;
      cout << "maximum value found at detection number " << i << " with correlation value of " << max_val << endl;
      max_val = 0;
      correlation_array[i] = 0;
    }
  }
  
  return 0;
}
