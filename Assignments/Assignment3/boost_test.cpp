#define BOOST_TEST_MODULE myTest
#define BOOST_TEST_MODULE check_num_ants_1
#define BOOST_TEST_MODULE table_size_2
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
//#include "./str.h"                                                                                                                                           
# include <iostream>
# include <rarray>
# include "single_time_step.h"
//#define BOOSTTESTMODULE myTest                                                                                                                               
#include <time.h>
#include <stdlib.h>
#include "ticktock.h"

//BOOST_AUTO_TEST_SUITE (stringtest) // name of the test suite is stringtest

BOOST_AUTO_TEST_CASE (myTest)
{
    
    int table_size=1;
    rarray<float,2> velocity_of_ants(table_size, table_size);
    rarray<float,2> number_of_ants(table_size, table_size);
    rarray<float,2> new_number_of_ants(table_size, table_size);
    velocity_of_ants[0][0] = 0;
    number_of_ants[0][0] = 1003;
    single_time_step(table_size, 0, number_of_ants, new_number_of_ants, velocity_of_ants, 0);

    BOOST_CHECK(number_of_ants[0][0] == 1003);                                         
}

BOOST_AUTO_TEST_CASE (table_size_2)
{
    int table_size=2;
    rarray<float,2> velocity_of_ants(table_size, table_size);
    rarray<float,2> number_of_ants(table_size, table_size);
    rarray<float,2> new_number_of_ants(table_size, table_size);
    velocity_of_ants[0][0] = 0;
    velocity_of_ants[0][1] = 0;
    velocity_of_ants[1][0] = 0;
    velocity_of_ants[1][1] = 0;
    number_of_ants[0][0] = 100;
    number_of_ants[0][1] = 200;
    number_of_ants[1][0] = 300;
    number_of_ants[1][1] = 400;
    
    single_time_step(table_size, 0, number_of_ants, new_number_of_ants, velocity_of_ants, 0);

    BOOST_REQUIRE_EQUAL (number_of_ants[0][0], 100);
    BOOST_REQUIRE_EQUAL (number_of_ants[0][1], 200);
    BOOST_REQUIRE_EQUAL (number_of_ants[1][0], 300);
    BOOST_REQUIRE_EQUAL (number_of_ants[1][1], 400);
}

BOOST_AUTO_TEST_CASE (check_num_ants_1)
{
    srand (time(NULL));
    int table_size=rand() % 100 + 1;
    rarray<float,2> velocity_of_ants(table_size, table_size);
    rarray<float,2> number_of_ants(table_size, table_size);
    rarray<float,2> new_number_of_ants(table_size, table_size);
    float total_ants_begin = 0;
    float total_ants_end = 0;
    float frac_move = (float)rand()/(float)(RAND_MAX);
    for (int i =0 ; i < table_size; i++){
	for (int j =0 ; j < table_size; j++){
	velocity_of_ants[i][j] = (float)rand()/(float)(RAND_MAX);
	number_of_ants[i][j] = (float)rand()/(float)(RAND_MAX/1000);
	total_ants_begin +=number_of_ants[i][j];
    	}
    }
    single_time_step(table_size, 0, number_of_ants, new_number_of_ants, velocity_of_ants, frac_move);
    for (int i =0 ; i < table_size; i++){
        for (int j =0 ; j < table_size; j++){
        total_ants_end +=number_of_ants[i][j];
        }
    }
  BOOST_TEST_MESSAGE( "Table Size: " << table_size << "\tTotal ants (begin): " << total_ants_begin << "\tTotal ants (end): " << total_ants_end << "\tFraction of moving ants: " << frac_move << "\n" );
  BOOST_CHECK( total_ants_begin >= total_ants_end);
}


