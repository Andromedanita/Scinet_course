/*
Anita Bahmanyar 
 
This code is used in single_time_step code that returns the total number of ants so that we can 
print it out.
*/

# include "output_time_step.h" // I used "" instead of <> since this is not part of the C library

// function that returns the total number of ants as output so that we can
// print it out in the single_time_step.cpp code
float output_per_time_step(int table_size, rarray<float,2>& number_of_ants){
    
    float totants = 0.0; // total number of ants
    for (int i=0;i<table_size;i++) {
        for (int j=0;j<table_size;j++) {
            totants += number_of_ants[i][j];
        }
    }
    return totants;
}

