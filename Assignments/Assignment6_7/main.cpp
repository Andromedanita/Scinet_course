#include<iostream>
#include<fstream>
#include <rarray>
#include <rarrayio>
#include <complex>
#include <fftw3.h>
#include<cblas.h>

using namespace std;

// Power spectrum function
void power(rarray<complex<double>,1> FT_signal){
  rarray<double,1> power_spec;
  for (int j=0;j<FT_signal.size(),j++){
    rarray<complex<double>,1> prod = FT_signal[j] * conj(FT_signal[j]);
    power_spec[j] = prod.real();
  }
  return power_spec;
}

// Correlation function
void corr(rarray<double,1> F, rarray<double,1> G){
  double FF = cblas_ddot(F.size(), F.data(), 1, F.data(), 1);
  double GG = cblas_ddot(G.size(), G.data(), 1, G.data(), 1);
  double FG = cblas_ddot(F.size(), F.data(), 1, G.data(), 1);
  double corr_val = FG/sqrt(FF * GG);

  return corr_val;
}


void Fourier_Trans(){
  // creating the fourier transform of an array                                                                                          
  int n       = signal.size();
  rarray<complex<double>,1> FT_signal(n);
  fftw_plan p = fftw_plan_dft_1d(n,(fftw_complex*)signal.data(), (fftw_complex*)FT_signal.data(),FFTW_FORWARD, FFTW_ESTIMATE);
  fftw_execute(p);
  fftw_destroy_plan(p);
  return FT_signal;
}


void read_data(string dir,string filename){
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

int main(){
  rarray<complex<double>,1> GW_signal = read_data("/home/b/bovy/bahmanya/Assignments/hw6_7/gwdata/","GWprediction.rat");
  rarray<complex<double>,1> detection = read_data("/home/b/bovy/bahmanya/Assignments/hw6_7/gwdata/","detection01.rat");
  
  rarray<double,1> F = power_spec(detection);
  rarray<double,1> G = power_spec(GW_signla);
  
  double C = corr(F, G);

  
  //for (int k=0; k<32;k++){
    

  //}
  
  
  return 0;
}
