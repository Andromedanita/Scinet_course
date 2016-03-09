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


  int n       = signal.size();
  rarray<complex<double>,1> FT_signal(n);

  fftw_plan p = fftw_plan_dft_1d(n,(fftw_complex*)signal.data(), (fftw_complex*)FT_signal.data(),FFTW_FORWARD, FFTW_ESTIMATE);

  fftw_execute(p);
  fftw_destroy_plan(p);
  
  cout << "signal FT is:" << FT_signal << "\n"  << endl;

  
  //for (int i=0; i<n; i++)
  //  cout << sig[i] << "," << sighat[i] << endl;
  //return 0;

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

  return 0;
}
