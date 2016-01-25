# include"initialize.h"

void initialize(int table_size, rarray<float,2>& velocity_of_ants, rarray<float,2>& number_of_ants, int total_ants){
    
    for (int i=0;i<table_size;i++) {
        for (int j=0;j<table_size;j++) {
            velocity_of_ants[i][j] = M_PI*(sin((2*M_PI*(i+j))/(table_size*10))+1);
            
        }
    }
    int n = 0;
    float z = 0;
    for (int i=0;i<table_size;i++) {
        for (int j=0;j<table_size;j++) {
            number_of_ants[i][j] = 0.0;
        }
    }
    while (n < total_ants) {
        for (int i=0;i<table_size;i++) {
            for (int j=0;j<table_size;j++) {
                z += sin(0.3*(i+j));
                if (z>1 and n!=total_ants) {
                    number_of_ants[i][j] += 1;
                    n += 1;
                }
            }
        }
    }
}
