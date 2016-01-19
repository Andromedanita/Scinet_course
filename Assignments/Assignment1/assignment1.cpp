#include <iostream>
#include <math.h>
#include <fstream>
#include <string>


double f(double x) // defining a function f that takes x as double and returns sin(2x)
{
    return sin(2*x);
}

double g(double x) // defining a function f that takes x as double and returns cos(3x)
{
    return cos(3*x);
}


int main()
{
    
    double xstart = -5;  // starting point for x values
    double xend   = 5;   // end point of x values
    int    n      = 100; // number of x values
    double dx     = (xend-xstart)/n; // uniform spacing between the x values
    
    // defining the variables as double
    double xval;
    double sin_val;
    double cos_val;
    
    // opening the output file
    std::ofstream fout("lissajous.txt");
    // writing header as (x, sin(2x) and cos(3x) to the output file
    fout << "x " << "\t" << "sin(2x) " << "\t" << "cos(3x)" << std::endl;
    
    // for loop to iterate over x values and get sin(2x) and cos(3x) out
    // and to write these in the output file
    for (int i=0; i<100; i++) {
        xval = xstart + (i*dx);
        sin_val = f(xval);
        cos_val = g(xval);
        
        fout << xval << " " << "\t" << sin_val << " " << "\t" << cos_val << std::endl;
        
    }
    fout.close(); // closing the output file
    return 0;
    
    
}