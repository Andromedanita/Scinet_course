//Anita Bahmanyar
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


rarray<complex<double>,1> read_data(string dir,string filename){                                                                                        
  // openning the file                                                                                                                                  
  ifstream f(dir+filename);                                                                                                                             
                                                                                                                                                        
  // create empty arrays for time and signal                                                                                                            
  rarray<double,1> times;                                                                                                                               
  rarray<complex<double>,1> signal;                                                                                                                     
                                                                                                                                                        
  // read in the signal                                                                                                                                 
  f >> times;                                                                                                                                           
  f >> signal;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
  return signal;                                                                                                                                        
}                                                                                                                                                       
                   
// Fourier Transfrom function
rarray<complex<double>,1> Fourier_Trans(rarray<complex<double>,1> signal){
  // creating the fourier transform of an array                                                                                                         
  int n       = signal.size();
  rarray<complex<double>,1> FT_signal(signal.size());
  fftw_plan p = fftw_plan_dft_1d(n,(fftw_complex*)signal.data(), (fftw_complex*)FT_signal.data(),FFTW_FORWARD, FFTW_ESTIMATE);
  fftw_execute(p);
  fftw_destroy_plan(p);
  return FT_signal;
}



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



