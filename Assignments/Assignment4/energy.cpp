/*
Anita Bahmanyar (Feb. 25, 2016)

This code includes all the functions to be minimized and all the minimizing functions.
*/

#include "energy.h"

using namespace std;

double Espring(double x, void* param){
  // energy of the spring
  Params* p = (Params*)param;
  double a  = p->a;
  double b  = p->b;
  double c  = p->c;
  double d  = p->d;
  double f  = p->f;
  return a * ( (b/x) + ((d*d)/(f*(x-d)*(x-d))) - exp((-c*(x-b)*(x-b))/(2.*a)) );
}

double Eweight(double x, void* param){
  // energy of the weight 
  Params* p = (Params*)param;
  double g  = p->g;
  double m  = p->m;
  return -m * g * x;
}

double Etot(double x, void* param){
  // total energy of the system 
  return Espring(x, param) + Eweight(x, param);
}

// derivative of spring energy
double dEspring(double x,void* param){
  // assigning varibale names to the params for a less messy return argument 
  Params* p = (Params*)param;
  double a = p->a;
  double b = p->b;
  double c = p->c;
  double d = p->d;
  double f = p->f;
  return a * ( (-b/(x*x)) + ((-2.*d*d)/(f*(x-d)*(x-d)*(x-d))) + ((c*(x-b)/a) * exp( (-c*(x-b)*(x-b))/(2.*a))) );
}

// derivative of weight energy
double dEweight(double x, void* param){
  Params* p = (Params*)param;
  double g = p->g;
  double m = p->m;
  return -m * g;
}

// derivative of total energy(sum of spring and weight energy)
double dEtot(double x, void* param){
  return dEspring(x, param) + dEweight(x, param);
}

// function to find the root of derivative of total energy function
double f_all_min(double mass, double x_lo, double x_hi, int iter_max, double prec){

  // mass : mass
  // x_lo : lower limit for the interval to search for the root
  // x_hi : upper limit for the interval to search for the root
  // value of the parameters a,b,c,d,f,g,m
  // iter_max : maximum number of iterations
  // prec : precision to find the root

  Params args = {1., 0.1, 100., 0.5, 2500., 9.8, 0.3};
  // setting mass to the argument from the function
  args.m      = mass; // assigning new value to the mass argument

  gsl_root_fsolver* solver;
  gsl_function      fwrapper;

  // using brent root finding method
  solver = gsl_root_fsolver_alloc(gsl_root_fsolver_brent);
  
  // setting function for root finding to be dEtotal
  // and the arguments to be the parameters given
  fwrapper.function = dEtot;
  fwrapper.params   = &args;
  gsl_root_fsolver_set(solver, &fwrapper, x_lo, x_hi);

  int status = 1;

  double x_rt = (x_hi-x_lo)/2.;
  // iterating to find the root iter_max times
  for (int iter=0; status and iter < iter_max; ++iter) {
    gsl_root_fsolver_iterate(solver);
    x_rt = gsl_root_fsolver_root(solver);
    x_lo = gsl_root_fsolver_x_lower(solver);
    x_hi = gsl_root_fsolver_x_upper(solver);
    status = gsl_root_test_interval(x_lo,x_hi,0,prec);
  }
  // cleaning the memory
  gsl_root_fsolver_free(solver);
  return x_rt;
}
                                                                                                                                                                                                                                                                                 
double f_min_diff(double mass, double x_lo, double x_hi, int iter_max, double prec){
  // finding the root for diff function, which finds the difference between the
  // energies of two minima points for a given mass
  Params args = {1., 0.1, 100., 0.5, 2500., 9.8, 0.3};

  // setting mass to the argument from the function                                                                                                 
  args.m      = mass;

  gsl_root_fsolver* solver;
  gsl_function      fwrapper;
  solver = gsl_root_fsolver_alloc(gsl_root_fsolver_brent);

  // setting function for root finding to be dEtotal                                                                                                
  // and the arguments to be the parameters given                                                                                                   
  fwrapper.function = diff;
  fwrapper.params   = &args;
  gsl_root_fsolver_set(solver, &fwrapper, x_lo, x_hi);
  int status = 1;

  double x_rt = (x_hi-x_lo)/2.;
  // iterating to find the root iter_max times                                                                                                      
  for (int iter=0; status and iter < iter_max; ++iter) {
    gsl_root_fsolver_iterate(solver);
    x_rt = gsl_root_fsolver_root(solver);
    x_lo = gsl_root_fsolver_x_lower(solver);
    x_hi = gsl_root_fsolver_x_upper(solver);
    status = gsl_root_test_interval(x_lo,x_hi,0,prec);
  }
  // cleaning the memory                                                                                                                            
  gsl_root_fsolver_free(solver);
  return x_rt;
}

double diff(double mass, void* param){
  // returns the difference between the energies of
  // the two minima of the total energy

  Params* p = (Params*)param;
  Params args = {1., 0.1, 100., 0.5, 2500., 9.8, 1.0};
  args.m = mass;
  
  // finding the root of the total energy
  double min1 = f_all_min(mass,0.1,0.22,100,0.00001);
  double min2 = f_all_min(mass,0.4,0.49,100,0.00001);

  // computing total energies of the minima points
  double E1 = Etot(min1, &args);
  double E2 = Etot(min2, &args);

  return E1-E2;
}


double max_load(double mass){
  // returns the minimum of the energy difference function
  // to find where the difference between the energies of
  // the two minima is the smallest, and that becomes the 
  // maximum mass load

  double m_lo     = 0.01;    //minimum mass
  double m_hi     = 0.25;    //maximum mass
  double iter_max = 100;     //number of iterations
  double prec     = 0.00001; //precision

  double value = f_min_diff(mass, m_lo, m_hi, iter_max, prec);
  return value;
}
