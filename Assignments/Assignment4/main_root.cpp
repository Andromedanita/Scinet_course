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
  //double root11 = f_all_min(m,0.4,0.48,100,0.00001);
  //double root22 = f_all_min(m,0.1,0.2,100,0.00001);
  //cout << "root 1 is:" << setprecision (15) << root11 << "\n" << "root 2 is:" << root22 << endl;

  // figuring out the mass-extension relation
  double min_mass = 0.0; //minimum mass
  double max_mass = 0.5; //maximum mass
  int    n        = 25;  //number of mass values 
  double dm       = (max_mass-min_mass)/n; // uniform spacing between the mass values 
  double M;

  double root1;    //root1 (first minimum of x)
  double root2;    //root2 (second minimum of x)
  double E1;       //total energy at first x maximum
  double E2;       //total energy at second x maximum
  double glob_min; //global minimum

  ofstream fout("global_mins.txt");
  fout << "# Mass(Kg) " << "\t" << "Global minimum " << endl;

  for (int j=0;j<n;j++){
    cout << "iteration number" << j << endl;
    
    Params args = {1., 0.1, 100., 0.5, 2500., 9.8, 1.0}; 
    M = min_mass + (j*dm);

    root1 = f_all_min(M,0.1,0.22,100,0.00001);
    root2 = f_all_min(M,0.4,0.49,100,0.00001);

    E1 = Etot(root1, &args);
    E2 = Etot(root2, &args);

    if (E1 < E2){
      glob_min = root1;
    }
    else{
      glob_min = root2;
    }

    fout << M << " " << "\t \t" << glob_min << endl;
    cout << "x of global minimum is:" << glob_min << "\n" << endl;
  }
  //printf ("%9f %9f \n",root1,root2);
  return 0;
}
