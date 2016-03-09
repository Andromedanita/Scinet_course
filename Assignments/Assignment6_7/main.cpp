#include <iostream>
#include <fstream>
#include <rarray>
#include <rarrayio>
#include <complex>
#include <fftw3.h>
#include <cblas.h>
#include <math.h>

using namespace std;

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

int main(){
  rarray<complex<double>,1> GW_signal = read_data("/home/b/bovy/bahmanya/Assignments/hw6_7/gwdata/","GWprediction.rat");
  /*
  rarray<complex<double>,1> detection = read_data("/home/b/bovy/bahmanya/Assignments/hw6_7/gwdata/","detection01.rat");
  
  rarray<complex<double>,1> f = Fourier_Trans(detection);
  rarray<complex<double>,1> g = Fourier_Trans(GW_signal);

  rarray<double,1> F = power_spec(f);
  rarray<double,1> G = power_spec(g);
  
  double C = corr(F, G);
  
  cout << "correlation is:" << C << endl;
  */

  for (int k=0; k<32;k++){
    rarray<complex<double>,1> detection = read_data("/home/b/bovy/bahmanya/Assignments/hw6_7/gwdata/","detection01.rat");
    rarray<complex<double>,1> f = Fourier_Trans(detection);
    rarray<complex<double>,1> g = Fourier_Trans(GW_signal);

    rarray<double,1> F = power_spec(f);
    rarray<double,1> G = power_spec(g);

    double C = corr(F, G);

    cout << "correlation is:" << C << endl;
  }
  
  return 0;
}
