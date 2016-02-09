/*
This is the main code that uses the dependencies initialize and single_time_step to
compute the mean number of ants on each square of the table. 
*/

#include <cmath>
#include <iostream>
#include "initialize.h"
#include "single_time_step.h"
#include <rarray>
#include <ticktock.h>

using namespace std;

int main()
{
    // ants walk on a table
    // defining parameters of table and ants
    const int table_size = 356;  // table size
    int       end_time   = 40;
    float     frac_move  = 0.2;  // fraction of ants moving
    const int total_ants = 1010; // initial number of ants
    TickTock stopwatch;
    TickTock timer_single;

    // defining arrays of velocity, number and the new number of ants using rarray
    // so that we do not need to handle pointers to pointers 
    rarray<float,2> velocity_of_ants(table_size, table_size);
    rarray<float,2> number_of_ants(table_size, table_size);
    rarray<float,2> new_number_of_ants(table_size, table_size);
    
    stopwatch.tick();
    // initializing the code
    initialize(table_size, velocity_of_ants, number_of_ants, total_ants);
    
    // run simulation
    for (int t = 0; t < end_time; t++) {
        timer_single.tick();
        single_time_step(table_size, t, number_of_ants, new_number_of_ants, velocity_of_ants, frac_move);
	timer_single.tock("Elapsed time for this step is:");
	cout << "\n" << endl;
	
    }

    stopwatch.tock("Total elapsed time is:");
    return 0;
    
}             
 
