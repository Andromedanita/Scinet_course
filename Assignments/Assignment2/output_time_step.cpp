# include "output_time_step.h"
float output_per_time_step(int table_size, rarray<float,2>& number_of_ants){
    
    float totants = 0.0;
    for (int i=0;i<table_size;i++) {
        for (int j=0;j<table_size;j++) {
            totants += number_of_ants[i][j];
        }
    }
    return totants;
}

