#include "energy_root.h"

using namespace std;

double dEspring(double x, void* param){
  Params* p = (Params*)param;
  double a = p->a;
  double b = p->b;
  double c = p->c;
  double d = p->d;
  double f = p->f;

  return a * ( (-b/(x*x)) + ((-2.*d*d)/(f*(x-d)*(x-d)*(x-d))) + ((c*(x-b)/a) * exp( (-c*(x-b)*(x-b))/(2.*a))) );
}


double dEweight(double x, void* param){
  Params* p = (Params*)param;
  double g = p->g;
  double m = p->m;

  return -m * g;
}

double dEtot(double x, void* param){
  return dEspring(x, param) + dEweight(x, param);
}

double f_all_min(double mass){

  double x_lo = 0.01;
  double x_hi = 0.49;
  Params args = {1., 0.1, 100., 0.5, 2500., 9.8, 0.3};
  gsl_root_fsolver* solver;
  gsl_function      fwrapper;
  solver = gsl_root_fsolver_alloc(gsl_root_fsolver_brent);
  fwrapper.function = dEtot;
  fwrapper.params   = &args;
  gsl_root_fsolver_set(solver, &fwrapper, x_lo, x_hi);
  cout << " iter [ lower, upper] root err\n" <<endl;
  int status = 1;
  for (int iter=0; status and iter < 100; ++iter) {
    gsl_root_fsolver_iterate(solver);
    double x_rt = gsl_root_fsolver_root(solver);
    double x_lo = gsl_root_fsolver_x_lower(solver);
    double x_hi = gsl_root_fsolver_x_upper(solver);
    cout << iter <<" "<< x_lo <<" "<< x_hi
	      <<" "<< x_rt <<" "<< x_hi - x_lo << "\n";
    status = gsl_root_test_interval(x_lo,x_hi,0,0.001);
  }
  gsl_root_fsolver_free(solver);
  return status;
}
