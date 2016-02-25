// Anita Bahmanyar

// detting gaurds
#ifndef  ENERGY_H
#define ENERGY_H
#include <iostream>
#include <iomanip>
#include <gsl/gsl_roots.h>
#include <stdio.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_min.h>
#include <cmath>

// defining the parameters in a struct
struct Params{
  double a,b,c,d,f,g,m;
};

double Espring(double x, void* param);
double Eweight(double x, void* param);
double Etot(double x, void* param);
double dEspring(double x, void* param);
double dEweight(double x, void* param);
double dEtot(double x, void* param);
double f_all_min(double mass, double x_lo, double x_hi, int iter_max, double prec);
double diff(double mass, void* param);
double f_min_diff(double mass, double x_lo, double x_hi, int iter_max, double prec);
double max_load(double mass);

#endif

