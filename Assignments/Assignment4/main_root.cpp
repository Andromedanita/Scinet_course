#include <iostream>
#include <iomanip>
#include <gsl/gsl_roots.h>
#include <stdio.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_min.h>
#include <math.h>
#include "energy_root.h"

using namespace std;

int main(){
  double m = 1.;
  cout << "anita:" << f_all_min(m) << endl;
  return 0;
}
