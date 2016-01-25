#include <cmath>
#include <iostream>
#include "initialize.h"
#include "single_time_step.h"
#include <rarray>


int main()
{
    // ants walk on a table
    const int table_size = 356;
    int   end_time = 40;
    float frac_move = 0.2;
    const int total_ants = 1010; // initial number of ants
    
    
    // initialize
    /*
    float **velocity_of_ants   = new float *[table_size];
    float **number_of_ants     = new float *[table_size];
    float **new_number_of_ants = new float *[table_size];
    
    for (int i=0; i<table_size; i++) {
        velocity_of_ants[i]   = new float [table_size];
        number_of_ants[i]     = new float [table_size];
        new_number_of_ants[i] = new float [table_size];
    }
    */
    rarray<float,2> velocity_of_ants(table_size, table_size);
    rarray<float,2> number_of_ants(table_size, table_size);
    rarray<float,2> new_number_of_ants(table_size, table_size);
    
    initialize(table_size, velocity_of_ants, number_of_ants, total_ants);
    
    // run simulation
    for (int t = 0; t < end_time; t++) {
        
        single_time_step(table_size, t, number_of_ants, new_number_of_ants, velocity_of_ants, frac_move);
    }
    /*
    // deleting arrays
    for (int i=0; i<table_size; i++) {
        delete[] velocity_of_ants[i];
        delete[] new_number_of_ants[i];
        delete[] number_of_ants[i];
    }
    
    delete[] velocity_of_ants;
    delete[] new_number_of_ants;
    delete[] number_of_ants;
    */
    //rarray<float,3> a(256, 256, 256);
    //a[1][2][3] = 105;
    
    //std::cout << a[1][2][3] <<std::endl;
    
    
    
    return 0;
    
}             
 
