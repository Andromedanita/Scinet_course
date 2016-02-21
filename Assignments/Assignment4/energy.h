#ifndef  ENERGY_H
#define ENERGY_H
#include <iostream>
#include <iomanip>
#include <gsl/gsl_roots.h>
#include <stdio.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_min.h>
#include <math.h>


struct Params{
  double a,b,c,d,f,g,m;
};


double Espring(double x, void* param);
double Eweight(double x, void* param);
double Etot(double x, void* param);
double f_all_min(double mass);

#endif
