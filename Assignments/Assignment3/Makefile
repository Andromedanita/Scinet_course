# Anita Bahmanyar
TICKTOCK_PATH =/Users/anita/Documents/Grad_First_Year/Scinet_Course/ticktock
CPP      = g++  -pg -g  # setting the compiler
CPPFLAGS = -I${TICKTOCK_PATH} -O2 #-lstdc++ # setting the flags
PROF     = gprof

all: profiling #ants # the key to run if we only type make


profiling: move_files
	${PROF} ants ants_gmon.out > ants_gmon.txt
	${PROF} ants_orig ants_orig_gmon.out > ants_orig_gmon.txt


move_files: ants ants_orig
	./ants
	mv gmon.out ants_gmon.out
	./ants_orig
	mv gmon.out ants_orig_gmon.out


ants_orig: ants_orig.o ticktock.o
	${CPP} ants_orig.o ticktock.o -o ants_orig

ants_orig.o: ants_orig.cc
	${CPP} ${CPPFLAGS} ants_orig.cc -c -o ants_orig.o

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
	rm -f initialize.o single_time_step.o output_time_step.o ticktock.o ants.o ants_orig.o ants_gmon.out ants_orig_gmon.out ants