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
MP        = -fopenmp

all:  wave1d      # time loop parallelized
way1: wave1d_way1 # writing to different files
way2: wave1d_way2 # writing to a single file

# Makefile for wave equation time loop parallel
wave1d: wave1d.o ticktock.o
	$(CXX) $(LDFLAGS) ${MP} -o $@ $^ $(LDLIBS)

wave1d.o:  wave1d_timepar.cc ticktock.h
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) ${MP} -o $@ $< 

# Makefile for wave equation writing to different files(way1)
wave1d_way1: wave1d_way1.o ticktock.o
	$(CXX) $(LDFLAGS) ${MP} -o $@ $^ $(LDLIBS)

wave1d_way1.o:  wave1d_outputpar_way1.cc ticktock.h
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) ${MP} -o $@ $<


# Makefile for wave equation to single file (way2)
wave1d_way2: wave1d_way2.o ticktock.o
	$(CXX) $(LDFLAGS) ${MP} -o $@ $^ $(LDLIBS)

wave1d_way2.o:  wave1d_outputpar_way2.cc ticktock.h
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) ${MP} -o $@ $<

ticktock.o: ticktock.cc ticktock.h
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) ${MP} -o $@ $< 

clean:
	rm -f *.o parallel_way1_*
