// Anita Bahmanyar, March 23, 2016 
// 
// walkring_timestep.cc
//
// Time stepping module for 1d random walk on a ring
//

#include "walkring_timestep.h"
#include <random>

using namespace std;

// initializing the random generator
default_random_engine engine;

// the random numbers are drawn uniformly between 0 and 1
uniform_real_distribution<double> uniform(0.0,1.0);

// perform a single time step for the random walkers
// pos: the positions of Z walkers. Z=pos.size()
// N: the number of grid points. All positions should remain between 0
//    and N-1, with periodic boundary conditions
// p: the probability to jump to the left. Also the probability to just right.
//    the probability to stay on the same spot is thus 1-2p.
void perform_time_step(rarray<int,1>& pos, int N, double p)
{
  int Z = pos.size();

  // looping through all grids
  for (int i=0;i<Z;i++){
    double state = uniform(engine);
    if (state>0 and state<p){
      //move to the left
      pos[i] -=1;
      // boundary periodicity
      if (pos[i]<0){
	pos[i] += N;
      }
    }
    else if (state>=p and state<(2*p)){
      // move to the right
      pos[i] += 1;
      // boundary periodicity
      if (pos[i]>N){
	pos[i] -= N;
      }
    }
    else if (state>=(2*p) and state<1){
      //stay at the same position
      pos[i] = pos[i];
    }
  }

}


