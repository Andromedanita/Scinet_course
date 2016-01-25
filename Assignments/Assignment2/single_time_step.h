#ifndef SINGLE_TIME_STEP_H
#define SINGLE_TIME_STEP_H

#include <iostream>
#include <cmath>
#include "output_time_step.h"
#include <rarray>

void single_time_step(int table_size, int t, rarray<float,2>& number_of_ants, rarray<float,2>& new_number_of_ants, rarray<float,2>& velocity_of_ants, float frac_move);

#endif
