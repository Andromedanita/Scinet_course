# include "single_time_step.h"


void single_time_step(int table_size, int t, rarray<float,2>& number_of_ants, rarray<float,2>& new_number_of_ants, rarray<float,2>& velocity_of_ants, float frac_move){
    
    float totants = output_per_time_step(table_size, number_of_ants);
    
    std::cout << t<< " " << totants << std::endl;
    for (int i=0;i<table_size;i++) {
        for (int j=0;j<table_size;j++) {
            new_number_of_ants[i][j] = 0.0;
        }
    }
    for (int i=0;i<table_size;i++) {
        for (int j=0;j<table_size;j++) {
            int di = 1.9*sin(velocity_of_ants[i][j]);
            int dj = 1.9*cos(velocity_of_ants[i][j]);
            int i2 = i + di;
            int j2 = j + dj;
            // some ants do not walk
            new_number_of_ants[i][j]+= (1.-frac_move) * number_of_ants[i][j];
            // the rest of the ants walk, but some fall of the table
            if (i2>=0 and i2<table_size and j2>=0 and j2<table_size) {
                new_number_of_ants[i2][j2]+=frac_move*number_of_ants[i][j];
            }
        }
    }
    for (int i=0;i<table_size;i++) {
        for (int j=0;j<table_size;j++) {
            number_of_ants[i][j] = new_number_of_ants[i][j];
            totants += number_of_ants[i][j];
        }
    }
}
