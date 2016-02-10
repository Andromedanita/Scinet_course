#define BOOST_TEST_MODULE myTest
#define BOOST_TEST_MODULE check_num_ants
#define BOOST_TEST_MODULE table_size
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>                                                                                     
#include <iostream>
#include <rarray>
#include "single_time_step.h"                                                                                          
#include <time.h>
#include <stdlib.h>
#include "ticktock.h"

using namespace std;

BOOST_AUTO_TEST_CASE (myTest)
{
    cout << "Running test # 1..." << endl;
    cout << "Checking the initial movement of ants with zero velocity in a 1 X 1 table:"  << endl; 
    int table_size=1;
    rarray<float,2> velocity_of_ants(table_size, table_size);
    rarray<float,2> number_of_ants(table_size, table_size);
    rarray<float,2> new_number_of_ants(table_size, table_size);
    velocity_of_ants[0][0] = 0;   // giving a zero velocity 
    number_of_ants[0][0] = 1050;  // assigning a number for the initial number of ants
    cout << "Initial number of ants: " << number_of_ants[0][0] << "\n" <<endl;
    single_time_step(table_size, 0, number_of_ants, new_number_of_ants, velocity_of_ants, 0);

    // checking to see if non of the ants move due to the zero velocity
    BOOST_CHECK(number_of_ants[0][0] == 1050);                                  
    cout << "\n" <<endl;
    
}

BOOST_AUTO_TEST_CASE (table_size)
{
    cout << "Running test # 2..." << endl;
    cout << "Checking the movement of ants with zero velocity in a 4 X 4 table:" <<endl;
    int table_size=2; // table size = 2
    rarray<float,2> velocity_of_ants(table_size, table_size);
    rarray<float,2> number_of_ants(table_size, table_size);
    rarray<float,2> new_number_of_ants(table_size, table_size);
    // assigning zero velocity to the table squares
    velocity_of_ants[0][0] = 0;
    velocity_of_ants[0][1] = 0;
    velocity_of_ants[1][0] = 0;
    velocity_of_ants[1][1] = 0;
    // giving an initial number of ants in each table square
    number_of_ants[0][0]   = 100;
    number_of_ants[0][1]   = 200;
    number_of_ants[1][0]   = 300;
    number_of_ants[1][1]   = 400;
   
    int init_tot = number_of_ants[0][0] + number_of_ants[0][1] + number_of_ants[1][0] + number_of_ants[1][1];
    cout << "Initial number of ants in square [0][0]: " << init_tot << "\n" <<endl;  
    // running a single time step function to see if the number of ants stays the same
    // because of the zero initial velocity
    single_time_step(table_size, 0, number_of_ants, new_number_of_ants, velocity_of_ants, 0);
   
    // checking the initial and final number of ants to be equal after moving the ants with 
    // a zero velocity
    BOOST_REQUIRE_EQUAL (number_of_ants[0][0], 100);
    BOOST_REQUIRE_EQUAL (number_of_ants[0][1], 200);
    BOOST_REQUIRE_EQUAL (number_of_ants[1][0], 300);
    BOOST_REQUIRE_EQUAL (number_of_ants[1][1], 400);
    cout << "\n" <<endl;   
}


BOOST_AUTO_TEST_CASE (check_num_ants)
{
    cout << "Running test # 3..." << endl;
    cout << "Checking if the new number of ants is smaller than the initial ones \nso that ants are not created during the simulation:" << endl;
    srand (time(NULL));
    int table_size=rand() % 100 + 1; //giving a random number for the size of the table

    cout << "Table size is:" << table_size << endl;
    rarray<float,2> velocity_of_ants(table_size, table_size);
    rarray<float,2> number_of_ants(table_size, table_size);
    rarray<float,2> new_number_of_ants(table_size, table_size);
    float total_ants_begin = 0;
    float total_ants_end   = 0;
    float frac_move = (float)rand()/(float)(RAND_MAX); // fraction of ants that move as a random number
    for (int i =0 ; i < table_size; i++){
	for (int j =0 ; j < table_size; j++){
	  velocity_of_ants[i][j] = (float)rand()/(float)(RAND_MAX); //giving random velocities to the ants 
	  number_of_ants[i][j]   = (float)rand()/(float)(RAND_MAX/1000); //giving random number of ants to each square of the table
	  total_ants_begin +=number_of_ants[i][j]; // initial total number of ants 
    	}
    }

    cout << "Total initial number of ants:" << total_ants_begin << "\n" << endl;
    // running one single timestep
    single_time_step(table_size, 0, number_of_ants, new_number_of_ants, velocity_of_ants, frac_move);
    //checking the final total number of ants after running the simulation for one time step
    for (int i =0 ; i < table_size; i++){
        for (int j =0 ; j < table_size; j++){
	  total_ants_end +=number_of_ants[i][j]; // total final number of ants
        }
    }

    BOOST_TEST_MESSAGE( "Table Size: " << table_size << "\tTotal ants (begin): " << total_ants_begin << "\tTotal ants (end): " << total_ants_end << "\tFraction of moving ants: " << frac_move << "\n" ); 
    BOOST_CHECK( total_ants_begin >= total_ants_end); // checking the initial number of ants > final number of ants
}


