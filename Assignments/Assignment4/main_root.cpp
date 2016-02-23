#include <iostream>
#include <iomanip>
#include <gsl/gsl_roots.h>
#include <stdio.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_min.h>
#include <cmath>
#include "energy_root.h"
#include <fstream>

using namespace std;

int main(){
  double m     = 0.3;

  // found the lower and upper bounds for each root by plotting the dEtot(x) and eyballing it
  double root1 = f_all_min(m,0.4,0.48,100,0.00001);
  double root2 = f_all_min(m,0.1,0.2,100,0.00001);
  cout << "root 1 is:" << setprecision (15) << root1 << "\n" << "root 2 is:" << root2 << endl;
  //printf ("%9f %9f \n",root1,root2);
  /*
  double xstart = -5;  // starting point for x values
  double xend   = 5;   // end point of x values
  int    n      = 10000; // number of x values
  double dx     = (xend-xstart)/n; // uniform spacing between the x values
  double values;
  double xval;
  ofstream fout("dEtot.txt");
  for (int i=0; i<n; i++) {
    xval = xstart + (i*dx);
    
    Params args = {1., 0.1, 100., 0.5, 2500., 9.8, 1.0};
    values = dEtot(xval, &args);
    fout << xval << " " << "\t" << values << endl;
  }
  fout.close(); 
  */
  return 0;
}
