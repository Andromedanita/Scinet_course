// Anita Bahmanyar

#ifndef FUNC_H
#define FUNCH

#include <iostream>
#include <fstream>
#include <rarray>
#include <rarrayio>
#include <complex>
#include <fftw3.h>
#include <cblas.h>
#include <math.h>
#include <string>

using namespace std;

rarray<complex<double>,1> read_data(string dir,string filename);
rarray<complex<double>,1> Fourier_Trans(rarray<complex<double>,1> signal);
rarray<double,1> power_spec(rarray<complex<double>,1> FT_signal);
double corr(rarray<double,1> F, rarray<double,1> G);

#endif
