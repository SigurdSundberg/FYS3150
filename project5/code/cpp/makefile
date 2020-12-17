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

${TARGET} :	   	main.o solver.o
				${CPPflags} main.o solver.o ${LIB} -o ${TARGET}

solver.o :	solver.hpp solver.cpp
		        	${CPPflags} -c solver.cpp

main.o :	main.cpp
		        	${CPPflags} -c main.cpp

# ${MPI} : paraIsing.o
# 	${MPIflags} paraIsing.o lib.o -o ${MPI}

# paraIsing.o : paraIsing.cpp
# 	${MPIflags} -c paraIsing.cpp

