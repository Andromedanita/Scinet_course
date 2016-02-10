# Anita Bahmanyar
TICKTOCK_PATH =/home/b/bovy/bahmanya/ticktock #ticktock code path if not in the same directory as your code
CPP        = g++  -pg -g             # setting the compiler
CPPFLAGS   = -O2 #-lboost_unit_test_framework #-I${TICKTOCK_PATH} -O2  # setting the flags
PROF       = gprof --line # setting the profiling (--line for showing the lines of code taking most of the run time)
BOOST_FLAG = -lboost_unit_test_framework

all: ants # the key to run if we only type make

# profiling and then moving the output to a text file
profiling: move_files
	${PROF} ants ants_gmon.out > ants_gmon.txt
	${PROF} ants_orig ants_orig_gmon.out > ants_orig_gmon.txt

# compiling the codes and renaming the profiling output
# since the output for both codes would be called the same
# thing and thus overwritten if not renames
move_files: ants ants_orig
	./ants
	mv gmon.out ants_gmon.out
	./ants_orig
	mv gmon.out ants_orig_gmon.out

test: test.o initialize.o single_time_step.o output_time_step.o ticktock.o
	${CPP} ${CPPFLAGS} ${BOOST_FLAG} initialize.o single_time_step.o output_time_step.o ticktock.o  boost_testing.o -o boost_testing	
	./boost_testing > boost_log.txt 

test.o: boost_test.cpp
        #${CPP} ${CPPFLAGS} boost_test.cpp -c -o boost_testing.o
	${CPP} ${CPPFLAGS} ${BOOST_FLAG} boost_test.cpp -c -o boost_testing.o

# linking all the files to one single output file for the original code (ants_orig)
ants_orig: ants_orig.o ticktock.o
	${CPP} ${CPPFLAGS} ants_orig.o ticktock.o -o ants_orig

# creating the output files for the original code
ants_orig.o: ants_orig.cc
	${CPP} ${CPPFLAGS} ants_orig.cc -c -o ants_orig.o


# linking all the files to one single output file for my modularized code (ants)
ants: single_time_step.o output_time_step.o initialize.o ants.o ticktock.o
	${CPP} ${CPPFLAGS} initialize.o single_time_step.o output_time_step.o ants.o ticktock.o -o ants

# creating the output files for the modularized code
ants.o: ants.cc
	${CPP} ${CPPFLAGS} ants.cc -c -o ants.o

initialize.o: initialize.cpp
	${CPP} ${CPPFLAGS} initialize.cpp -c -o initialize.o


single_time_step.o: single_time_step.cpp
	${CPP} ${CPPFLAGS}  single_time_step.cpp -c -o single_time_step.o

output_time_step.o: output_time_step.cpp
	${CPP} ${CPPFLAGS}  output_time_step.cpp -c -o output_time_step.o


#ticktock.o: ${TICKTOCK_PATH}/ticktock.cc
ticktock.o: ticktock.cc 
        #${CPP} ${CPPFLAGS} ${TICKTOCK_PATH}/ticktock.cc -c -o ticktock.o	
	${CPP} ${CPPFLAGS} ticktock.cc -c -o ticktock.o

# cleaning the directory by removing executable and the output files
clean:
	rm -f initialize.o single_time_step.o output_time_step.o ticktock.o ants.o ants_orig.o ants_gmon.out ants_orig_gmon.out ants
