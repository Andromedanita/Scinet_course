// Anita Bahmanyar
// Code containing all the functions used in the main code

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

// Reading the output of each .rat file
rarray<complex<double>,1> read_data(string dir,string filename){                                                                                      
  // openning the file
  ifstream f(dir+filename);                                                                                                                        

  // create empty arrays for time and signal                                                                                                        
  rarray<double,1> times;                                                                                                                             
  rarray<complex<double>,1> signal;                                                                                                                    

  // read in the signal                                                                                                                               
  f >> times;                                                                                                                                         
  f >> signal;                                                                                                                                                                                                                                                                
  // returning signal
  return signal;                                                                                                                                       
}                                                                                                                                                       
                   
// Fourier Transfrom function, the input should be a complex array which is the signal from reading each file
rarray<complex<double>,1> Fourier_Trans(rarray<complex<double>,1> signal){ 
  rarray<complex<double>,1> FT_signal(signal.size()); // an array with signal size to hold FT
  fftw_plan p = fftw_plan_dft_1d(signal.size(),(fftw_complex*)signal.data(), (fftw_complex*)FT_signal.data(),FFTW_FORWARD, FFTW_ESTIMATE);
  fftw_execute(p);
  fftw_destroy_plan(p);
  return FT_signal;
}


// Power spectrum function that takes Fourier Transformed signal (complex) as input                                                                
rarray<double,1> power_spec(rarray<complex<double>,1> FT_signal){
  rarray<double,1> power_spec(FT_signal.size()); // an array with the size of FT signal
  
  // looping over each element of the FT signal array
  for (int j=0;j<FT_signal.size();j++){
    complex<double> prod = FT_signal[j] * conj(FT_signal[j]); // f.f^* (multiplication by its conjugate)
    power_spec[j] = prod.real(); // taking only the real part for power spectrum
  }
  return power_spec;
}


// Correlation function that takes a real-valued arrays as input
// F: power spectrum of f(detection file)
// G: power spectrum of g(GW file)                                                                                                                    
double corr(rarray<double,1> F, rarray<double,1> G){
  double FF = cblas_ddot(F.size(), F.data(), 1, F.data(), 1); // dot prodcut (F.F)
  double GG = cblas_ddot(G.size(), G.data(), 1, G.data(), 1); // dot prodcut (G.G)
  double FG = cblas_ddot(F.size(), F.data(), 1, G.data(), 1); // dot prodcut (F.G)
  double corr_val = FG/sqrt(FF * GG); // correlation coefficient

  return corr_val;
}



