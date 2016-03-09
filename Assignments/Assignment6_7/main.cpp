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

/*
// Power spectrum function
rarray<double,1> power_spec(rarray<complex<double>,1> FT_signal){
  rarray<double,1> power_spec(FT_signal.size());
  for (int j=0;j<FT_signal.size();j++){
    complex<double> prod = FT_signal[j] * conj(FT_signal[j]);
    power_spec[j] = prod.real();
  }
  return power_spec;
}

// Correlation function
double corr(rarray<double,1> F, rarray<double,1> G){
  double FF = cblas_ddot(F.size(), F.data(), 1, F.data(), 1);
  double GG = cblas_ddot(G.size(), G.data(), 1, G.data(), 1);
  double FG = cblas_ddot(F.size(), F.data(), 1, G.data(), 1);
  double corr_val = FG/sqrt(FF * GG);

  return corr_val;
}


rarray<complex<double>,1> Fourier_Trans(rarray<complex<double>,1> signal){
  // creating the fourier transform of an array                                                                                          
  int n       = signal.size();
  rarray<complex<double>,1> FT_signal(signal.size());
  fftw_plan p = fftw_plan_dft_1d(n,(fftw_complex*)signal.data(), (fftw_complex*)FT_signal.data(),FFTW_FORWARD, FFTW_ESTIMATE);
  fftw_execute(p);
  fftw_destroy_plan(p);
  return FT_signal;
}


rarray<complex<double>,1> read_data(string dir,string filename){
  // openning the file
  ifstream f(dir+filename);

  // create empty arrays for time and signal                                                                                             
  rarray<double,1> times;
  rarray<complex<double>,1> signal;

  // read in the signal                                                                                                                  
  f >> times;
  f >> signal;  

  //rarray<complex<double>,2> columns;
  //for (int t=0; t<times.size(); t++){
  //  columns[t][0] = times[t];
  //  columns[t][1] = signal[t];
  //}

  return signal;
}
*/

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

    cout << "correlation is:" << C << endl;
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
