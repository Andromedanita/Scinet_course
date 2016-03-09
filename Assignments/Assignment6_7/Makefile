CPP      = g++             # setting the compiler
CPPFLAGS = -std=c++11  -O2 # setting the flags
FFTLIB   = -lfftw3
BLASLIB  = -lopenblas 

all: main # the key to run if we only type make

# linking all the files to one single output file (ants)
main: main.o funcs.o
	${CPP} ${CPPFLAGS} main.o funcs.o -o main ${FFTLIB} -I${SCINET_OPENBLAS_INC} -L${SCINET_OPENBLAS_LIB} ${BLASLIB}

# creating the output files
main.o: main.cpp
	${CPP} ${CPPFLAGS} main.cpp -c -o main.o ${FFTLIB} -I${SCINET_OPENBLAS_INC} -L${SCINET_OPENBLAS_LIB} ${BLASLIB}

funcs.o: funcs.cpp
	${CPP} ${CPPFLAGS} funcs.cpp -c -o funcs.o ${FFTLIB} -I${SCINET_OPENBLAS_INC} -L${SCINET_OPENBLAS_LIB} ${BLASLIB}

# cleaning the directory by removing executable and the output file                                                          
clean:
	rm -f main.o funcs.o