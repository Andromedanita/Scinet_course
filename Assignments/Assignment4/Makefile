CPP      = g++             # setting the compiler
CPPFLAGS = -std=c++11  -O2 # setting the flags
GCCLIB   = -g -L${SCINET_GSL_LIB} -lgsl -lgslcblas

all: mains # the key to run if we only type make

# linking all the files to one single output file (ants)
mains: main.o energy.o
	${CPP} ${CPPFLAGS} main.o energy.o -o mains ${GCCLIB} 

# creating the output files
main.o: main_root.cpp
	${CPP} ${CPPFLAGS} main_root.cpp -c -o main.o ${GCCLIB}

energy.o: energy_root.cpp
	${CPP} ${CPPFLAGS} energy_root.cpp -c -o energy.o ${GCCLIB}

# cleaning the directory by removing executable and the output files
clean:
	rm -f main.o energy.o