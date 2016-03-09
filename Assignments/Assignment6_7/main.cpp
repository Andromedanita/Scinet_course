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


int main(){
  // open the file named f
  ifstream f("/home/b/bovy/bahmanya/Assignments/hw6_7/gwdata/GWprediction.rat");
  // create empty arrays for time and signal
  rarray<double,1> times;
  rarray<complex<double>,1> signal;
  // read in the signal
  f >> times;
  f >> signal;

  // creating the fourier transform of an array
  int n       = signal.size();
  rarray<complex<double>,1> FT_signal(n);

  fftw_plan p = fftw_plan_dft_1d(n,(fftw_complex*)signal.data(), (fftw_complex*)FT_signal.data(),FFTW_FORWARD, FFTW_ESTIMATE);

  fftw_execute(p);
  fftw_destroy_plan(p);
  
  cout << "signal FT is:" << FT_signal << "\n"  << endl;

  

  // power spectrum for GWprediction.rat = F
  //rarray<double,1> power_spec;
  //for (int j=0;j<FT_signal.size(),j++){
  //  rarray<complex<double>,1> prod = FT_signal[j] * conj(FT_signal[j]);
  //  power_spec[j] = prod.real()
  //}

  // compute G  which is the fourier transform of detection01.rat. . .detection32.rat files
  

  // compute correlation between F and G


  // repeat this for each of the detection01.rat ... detection32.rat files

  return 0;
}
