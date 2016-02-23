#include "energy_root.h"

using namespace std;

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
  args.m      = mass;

  gsl_root_fsolver* solver;
  gsl_function      fwrapper;
  solver = gsl_root_fsolver_alloc(gsl_root_fsolver_brent);
  
  // setting function for root finding to be dEtotal
  // and the arguments to be the parameters given
  fwrapper.function = dEtot;
  fwrapper.params   = &args;
  gsl_root_fsolver_set(solver, &fwrapper, x_lo, x_hi);
  cout << " iter \t [ lower, upper] root err\n" <<endl;
  int status = 1;

  double x_rt;
  // iterating to find the root iter_max times
  for (int iter=0; status and iter < iter_max; ++iter) {
    gsl_root_fsolver_iterate(solver);
    double x_rt = gsl_root_fsolver_root(solver);
    double x_lo = gsl_root_fsolver_x_lower(solver);
    double x_hi = gsl_root_fsolver_x_upper(solver);
    cout << iter <<" "<< x_lo <<" "<< x_hi
	      <<" "<< x_rt <<" "<< x_hi - x_lo << "\n";
    status = gsl_root_test_interval(x_lo,x_hi,0,prec);
  }
  // cleaning the memory
  gsl_root_fsolver_free(solver);
  return x_rt;
}
