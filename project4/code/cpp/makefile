# Comment lines
# General makefile for c++ - choose PROG =   name of given program
# Here we define compiler option, libraries and the  target
CPPflags = c++ -O3
MPIflags = mpic++ -O3 
# Here we define the library functions we nee
LIB = -larmadillo -llapack -lblas
# Here we define the name of the executable
PROG = testcode
TARGET = main
MPI = paraIsing
# -Wall
all: ${TARGET} 
mpi: ${MPI}

# ${PROG} :	   	test-main.o  test-functions.o vec3.o planet.o solarSystem.o ODEsolver.o
# 				${CPPflags} test-main.o test-functions.o vec3.o planet.o solarSystem.o ODEsolver.o ${LIB} -o ${PROG}

${TARGET} :	   	main.o
				${CPPflags} main.o lib.o ${LIB} -o ${TARGET}

lib.o :	lib.h
		        	${CPPflags} -c lib.cpp

main.o :	main.cpp
		        	${CPPflags} -c main.cpp

${MPI} : paraIsing.o
	${MPIflags} paraIsing.o lib.o -o ${MPI}

paraIsing.o : paraIsing.cpp
	${MPIflags} -c paraIsing.cpp

