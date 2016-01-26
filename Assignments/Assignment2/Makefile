CPP      = g++
CPPFLAGS = -std=c++11  -O2

all: ants

ants: single_time_step.o output_time_step.o initialize.o ants.o
	${CPP} initialize.o single_time_step.o output_time_step.o ants.o -o ants
 
ants.o: ants.cc
	${CPP} ${CPPFLAGS} ants.cc -c -o ants.o

initialize.o: initialize.cpp
	${CPP} ${CPPFLAGS} initialize.cpp -c -o initialize.o

single_time_step.o: single_time_step.cpp
	${CPP} ${CPPFLAGS}  single_time_step.cpp -c -o single_time_step.o

output_time_step.o: output_time_step.cpp
	${CPP} ${CPPFLAGS}  output_time_step.cpp -c -o output_time_step.o

clean:
	rm -f initialize.o single_time_step.o output_time_step.o main
