// 
// diffring_timestep.cc
//
// Time step module for 1d diffusion on a ring
//

#include "diffring_timestep.h"
#include <cblas.h>

// perform a single time step for the density field
// F: matrix that describes the time evolution
// P: the density
void perform_time_step(const rarray<double,2>& F, rarray<double,1>& P)
{
    // PART OF THE ASSIGNMENT!
  int n = F.extent(0);
  rarray<double,1> PP(P.size());
  // copying P into PP and the opposite
  std::swap(P,PP);

  float a = 1.0;
  float b = 0.0; 
  cblas_dgemv(CblasRowMajor, CblasNoTrans, n, n, a, F.data(), n, PP.data(), 1, b, P.data(), 1);
}

// fill the matrix needed in perform_time_step
// F: matrix that describes the time evolution
// D: the diffusion constant
// dt: the time step to be used
// dx: the spatial resolution
void fill_time_step_matrix(rarray<double,2>& F, double D, double dt, double dx)
{
  int n = F.extent(0);
  
  F.fill(0.0);
  double off_diag = (D * dt)/(dx*dx); // off-diagonal values
  double diag     = 1-2*off_diag;     // diagonal values

  for (int i  = 1; i < n-1; i++){
    F[i][i-1] = off_diag;  
    F[i][i+1] = off_diag;
    F[i][i]   = diag; 
  }
  // boundary conditions
  F[0][n-1] = off_diag;
  F[n-1][0] = off_diag;
  F[n-1][n-1] = diag;
  F[n-1][n-2] = off_diag;
  F[n-2][n-1] = off_diag;
  F[0][1] = off_diag;
  F[0][0] = diag;
  }
