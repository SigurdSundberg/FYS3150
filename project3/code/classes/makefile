# Comment lines
# General makefile for c++ - choose PROG =   name of given program
# Here we define compiler option, libraries and the  target
CPPflags = c++ -O3
# Here we define the library functions we nee
LIB = -larmadillo -llapack -lblas
# Here we define the name of the executable
PROG = testcode
TARGET = main
# -Wall
all: ${PROG} ${TARGET} 

${PROG} :	   	test-main.o  test-functions.o vec3.o planet.o solarSystem.o ODEsolver.o
				${CPPflags} test-main.o test-functions.o vec3.o planet.o solarSystem.o ODEsolver.o ${LIB} -o ${PROG}

${TARGET} :	   	main.o planet.o solarSystem.o ODEsolver.o vec3.o
				${CPPflags} main.o vec3.o planet.o solarSystem.o ODEsolver.o ${LIB} -o ${TARGET}


tests-main.o :		tests-main.cpp 
		        	${CPPflags} -c test-main.cpp

test-functitons.o :	test-functions.cpp planet.o solarSystem.o ODEsolver.o
		        	${CPPflags} -c test-functions.cpp

solarSystem.o :	solarSystem.cpp solarSystem.hpp planet.o
		        	${CPPflags} -c solarSystem.cpp
					
planet.o : 	planet.cpp planet.hpp
				${CPPflags} -c planet.cpp					

ODEsolver.o : 		ODEsolver.cpp ODEsolver.hpp	solarSystem.o
				${CPPflags} -c ODEsolver.cpp


main.o : 		main.cpp ODEsolver.hpp planet.hpp solarSystem.hpp
				${CPPflags} -c main.cpp


vec3.o : 		vec3.cpp vec3.h	
			${CPPflags} -c vec3.cpp

# clean :
				


