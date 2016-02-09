/*
Anita Bahmanyar
 
This code uses the output function in output code to print out the total number of ants to the console.
Then it computes the new number of ants on each square of the table.
*/

# include "single_time_step.h"

// function that moves the ants over one single time step
void single_time_step(int table_size, int t, rarray<float,2>& number_of_ants, rarray<float,2>& new_number_of_ants, rarray<float,2>& velocity_of_ants, float frac_move){
    
    // using output code taht contains the output function
    float totants = output_per_time_step(table_size, number_of_ants);
    
    // printing out the total number of ants (since some fall off)
    std::cout << "Doing timestep " << t << "\n" << "Total number of ants: " << totants << std::endl;
    
    for (int i=0;i<table_size;i++) {
        for (int j=0;j<table_size;j++) {
            new_number_of_ants[i][j] = 0.0;
        }
    }
    // computing where the ants move
    for (int i=0;i<table_size;i++) {
        for (int j=0;j<table_size;j++) {
            int di = 1.9*sin(velocity_of_ants[i][j]);
            int dj = 1.9*cos(velocity_of_ants[i][j]);
            int i2 = i + di;
            int j2 = j + dj;
            
            // some ants do not walk
            new_number_of_ants[i][j]+= (1.-frac_move) * number_of_ants[i][j];
            
            // the rest of the ants walk, but some fall of the table
            // I have changed the if condition so that the condition is
            // that the ants are on the table
            if (i2>=0 and i2<table_size and j2>=0 and j2<table_size) {
                new_number_of_ants[i2][j2]+=frac_move*number_of_ants[i][j];
            }
        }
    }
    // summing up all the ants
    for (int i=0;i<table_size;i++) {
        for (int j=0;j<table_size;j++) {
            number_of_ants[i][j] = new_number_of_ants[i][j];
            totants += number_of_ants[i][j];
        }
    }
}
