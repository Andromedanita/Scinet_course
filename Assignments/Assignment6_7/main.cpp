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
 
  complex<double> sig[n],sighat[n];

  int n       = times.size();
  //f           = signal;
  fftw_plan p = fftw_plan_dft_1d(n,
				 (fftw_complex*)sig, (fftw_complex*)fhat,
				 FFTW_FORWARD, FFTW_ESTIMATE);
  fftw_execute(p);
  fftw_destroy_plan(p);
  for (int i=0; i<n; i++)
    cout << sig[i] << "," << sighat[i] << endl;
  return 0;

  //for (int i=0; i<432330;i++){
  //  cout << "time is:" << signal[i] << "\n" << endl;
  //}
 
  //cout << "trial" << times.extent(1) << "\n" <<endl;
  //cout << "size of time array is:" << times.extent(0) << "\n" << endl;
  //cout << "size of signal array is:" << signal.extent(0) << "\n" << endl;
  //cout << "signal array:" << signal << endl;
  //cout << "entent1:" << signal.extent(1) << endl;
  //cout << "size of time array is:" << sizeof(times) << endl;
  //cout << "size of signal array is:" << sizeof(signal) << endl;

}
