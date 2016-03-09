#include<iostream>
#include<fstream>
#include <rarray>
#include <rarrayio>
#include <complex>
#include <fftw3.h>

using namespace std;

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

  // square fourier transform to get power spectrum for GWprediction.rat = F


  // write a function to compute the power spectrum


  // compute G  which is the fourier transform of detection01.rat. . .detection32.rat files
  

  // compute correlation between F and G


  // repeat this for each of the detection01.rat ... detection32.rat files

  return 0;
}
