# Anita Bahmanyar
TICKTOCK_PATH =/Users/anita/Documents/Grad_First_Year/Scinet_Course/ticktock
CPP      = g++  # setting the compiler
CPPFLAGS = -std=c++11  -I${TICKTOCK_PATH} -O2 # setting the flags

all: ants # the key to run if we only type make

# linking all the files to one single output file (ants)
ants: single_time_step.o output_time_step.o initialize.o ants.o ticktock.o
	${CPP} initialize.o single_time_step.o output_time_step.o ants.o ticktock.o -o ants

# creating the output files
ants.o: ants.cc
	${CPP} ${CPPFLAGS} ants.cc -c -o ants.o

initialize.o: initialize.cpp
	${CPP} ${CPPFLAGS} initialize.cpp -c -o initialize.o

single_time_step.o: single_time_step.cpp
	${CPP} ${CPPFLAGS}  single_time_step.cpp -c -o single_time_step.o

output_time_step.o: output_time_step.cpp
	${CPP} ${CPPFLAGS}  output_time_step.cpp -c -o output_time_step.o

ticktock.o: ${TICKTOCK_PATH}/ticktock.cc
	${CPP} ${CPPFLAGS} ${TICKTOCK_PATH}/ticktock.cc -c -o ticktock.o	

# cleaning the directory by removing executable and the output files
clean:
	rm -f initialize.o single_time_step.o output_time_step.o ticktock.o ants.o ants
