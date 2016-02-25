/*
Anita Bahmanyar (Feb. 25, 2016)

Main code for using the functions in energy.cpp 
to find the mass-extension relation and to find the maximum load
*/

#include <iostream>
#include <iomanip>
#include <gsl/gsl_roots.h>
#include <stdio.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_min.h>
#include <cmath>
#include "energy.h"
#include <fstream>

using namespace std;

int main(){

  // figuring out the mass-extension relation
  double min_mass = 0.0; //minimum mass
  double max_mass = 0.5; //maximum mass
  int    n        = 25;  //number of mass values
  int    n1       = 20;
  double dm       = (max_mass-min_mass)/n; // uniform spacing between the mass values 
  double M;

  double root1;    //root1 (first minimum of x)
  double root2;    //root2 (second minimum of x)
  double E1;       //total energy at first x maximum
  double E2;       //total energy at second x maximum
  double glob_min; //global minimum
  double Efinal;   //energy of the global minimum
  
  // opening the output file
  ofstream fout("global_mins.txt");
  
  // writing the header of the output file
  fout << "# Mass(Kg) " << "\t" << "Global minimum " << "\t \t" << "Total Energy" << endl;

  // iterating over mass to find the global minimum for each mass
  for (int j=0;j<n1;j++){
    cout << "iteration number: " << j << endl;
    
    Params args = {1., 0.1, 100., 0.5, 2500., 9.8, 1.0}; 
    // making mass to be increasing by dm each time
    M = min_mass + (j*dm);

    // found the lower and upper bounds for each root by plotting the dEtot(x) and eyballing it   
    root1 = f_all_min(M,0.01,0.21,100,0.00001);
    root2 = f_all_min(M,0.4,0.49,100,0.00001);

    // total energy of the two minima points
    E1 = Etot(root1, &args);
    E2 = Etot(root2, &args);

    // finding the global minimum
    if (E1 < E2){
      glob_min = root1;
      Efinal   = E1; 
    }
    else{
      glob_min = root2;
      Efinal   = E2;
    }

    // writing to the output file
    fout << M << " " << "\t \t" << glob_min << "\t \t" << Efinal  << endl;
    cout << "Two minima points are at: " << root1 << " " << "and" << " " << root2 << "\n" << endl;
  }
  // this loop is for values of mass that have only one minimum
  for (int k=n1; k<n; k++){
    cout << "iteration number: " << k << endl;

    Params args = {1., 0.1, 100., 0.5, 2500., 9.8, 1.0};
    M = min_mass + (k*dm);

    // finding the root
    root2    = f_all_min(M,0.4,0.49,100,0.00001);
    E2       = Etot(root2, &args);
    glob_min = root2;
    Efinal   = E2;
    fout << M << " " << "\t \t" << glob_min << "\t \t" << Efinal  << endl;
    cout << "The only minimum point is at: " << root2 << "\n" << endl;
  }
  Params args = {1., 0.1, 100., 0.5, 2500., 9.8, 1.0};

  // maximum load 
  double maximum_load = max_load(args.m);
  cout << "Maximum load is: " << maximum_load << " " << "Kg" << endl;
  return 0;
}
