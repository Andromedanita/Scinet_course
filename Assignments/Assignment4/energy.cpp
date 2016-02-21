#include "energy.h"

using namespace std;

double Espring(double x, void* param){
  Params* p = (Params*)param;
  double a = p->a;
  double b = p->b;
  double c = p->c;
  double d = p->d;
  double f = p->f;

  return a * (b/x + d*d/f*(x-d)*(x-d) - exp((-c*(x-b)*(x-b))/(2.*a)));
}


double Eweight(double x, void* param){
  Params* p = (Params*)param;
  double g = p->g;
  double m = p->m;

  return -m * g * x;
}

double Etot(double x, void* param){
  return Espring(x, param) + Eweight(x, param);
}

double f_all_min(double mass){

  int    status;
  int    iter = 0, max_iter = 100;
  Params args = {1., 0.1, 100., 0.5, 2500., 9.8, 10.};
  args.m      = mass;

  const gsl_min_fminimizer_type *T;
  gsl_min_fminimizer *s;
  gsl_function F;
  F.function       = Etot;
  F.params         = &args;
  double lower     = -1000000.;
  double upper     = 1000000.;
  double min_guess = 500000.0;

  T = gsl_min_fminimizer_brent;
  s = gsl_min_fminimizer_alloc (T);
  gsl_min_fminimizer_set (s, &F, min_guess, lower, upper);

  printf ("using %s method\n",
          gsl_min_fminimizer_name (s));
  printf ("%5s [%9s, %9s] %9s %9s\n",
          "iter", "lower", "upper", "min",
          "err(est)");

  printf ("%5d [%.7f, %.7f] %.7f %.7f\n",
          iter, lower, upper,
          min_guess, upper - lower);

  do
    {
      iter++;
      status = gsl_min_fminimizer_iterate (s);

      min_guess = gsl_min_fminimizer_x_minimum (s);
      lower = gsl_min_fminimizer_x_lower (s);
      upper = gsl_min_fminimizer_x_upper (s);

      status
        = gsl_min_test_interval (lower, upper, 0.001, 0.0);

      if (status == GSL_SUCCESS)
        printf ("Converged:\n");

      printf ("%5d [%.7f, %.7f] "
              "%.7f %.7f\n",
              iter, lower, upper,
              min_guess, upper - lower);
    }
  while (status == GSL_CONTINUE && iter < max_iter);

  gsl_min_fminimizer_free (s);
  cout << "This is min_guess:" << setprecision(7) << min_guess << endl;
  printf( " This is : %.7f\n",min_guess);
  return min_guess;
}

