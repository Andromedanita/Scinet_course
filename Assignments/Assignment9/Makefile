#
# Makefile for 1dwave code for SciNet's High Performance Scientific Computing
#  
# Modules required
#
#module load gcc/4.8.1
#module load pgplot/5.2.2-gcc


CXX       = g++
CPPFLAGS  = -I${SCINET_PGPLOT_INC}
CXXFLAGS  = -g -O0 -std=c++11
LDLIBS    = -lcpgplot -lpgplot -lX11 -lgfortran -lpng 
LDFLAGS   = -L${SCINET_PGPLOT_LIB}
#MP        = -fopenmp

all: wave1d

# Makefile for wave equation

wave1d: wave1d.o ticktock.o
	$(CXX) $(LDFLAGS) -fopenmp -o $@ $^ $(LDLIBS)

wave1d.o: wave1d_timepar.cc ticktock.h
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) -fopenmp -o $@ $< 

ticktock.o: ticktock.cc ticktock.h
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) -fopenmp -o $@ $< 

clean:
	rm -f *.o
