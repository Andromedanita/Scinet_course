#include <iostream>
#include <gsl/gsl_roots.h>
#include <stdio.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_min.h>
#include <math.h>

using namespace std;


//typedef struct
struct Params{
  double a,b,c,d,f,g,m;
};

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

double Etot2(double x, void* param){
  Params* p = (Params*)param;
  double a = p->a;
  double b = p->b;
  double c = p->c;
  double d = p->d;
  double f = p->f;
  double g = p->g;
  double m = p->m;
  //double espring = a * (b/x + d*d/f*(x-d)*(x-d) - exp((-c*(x-b)*(x-b))/(2.*a)));
  double ew = -m * g * x;
  return /*espring +*/ ew;
  //return (x-a)*(x-a);
}


int main(){
  int status;
  int iter = 0, max_iter = 100;
  Params args = {1., 0.1, 100., 0.5, 2500., 9.8, 1.};
  const gsl_min_fminimizer_type *T;
  gsl_min_fminimizer *s;
  gsl_function F;
  F.function = Etot2;
  F.params   = &args;
  double a = -1000.;
  double b = 1000.;
  double m = 500.0;
  double m_expected = 6.;
  cout << "Hadi 1" << endl;
  T = gsl_min_fminimizer_brent;
  cout << "Hadi 2" << endl;
  s = gsl_min_fminimizer_alloc (T);
  cout << "Hadi 3" << endl;
  gsl_min_fminimizer_set (s, &F, m, a, b);
  cout << "Hadi 4" << endl;
  printf ("using %s method\n",
          gsl_min_fminimizer_name (s));
  cout << "Hadi 5" << endl;
  printf ("%5s [%9s, %9s] %9s %10s %9s\n",
          "iter", "lower", "upper", "min",
          "err", "err(est)");

  printf ("%5d [%.7f, %.7f] %.7f %+.7f %.7f\n",
          iter, a, b,
          m, m - m_expected, b - a);

  do
    {
      iter++;
      status = gsl_min_fminimizer_iterate (s);

      m = gsl_min_fminimizer_x_minimum (s);
      a = gsl_min_fminimizer_x_lower (s);
      b = gsl_min_fminimizer_x_upper (s);

      status 
	= gsl_min_test_interval (a, b, 0.001, 0.0);

      if (status == GSL_SUCCESS)
        printf ("Converged:\n");

      printf ("%5d [%.7f, %.7f] "
              "%.7f %+.7f %.7f\n",
              iter, a, b,
              m, m - m_expected, b - a);
    }
  while (status == GSL_CONTINUE && iter < max_iter);

  gsl_min_fminimizer_free (s);   
  return 0;
}
