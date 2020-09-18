# Comment lines
# General makefile for c++ - choose PROG =   name of given program
# Here we define compiler option, libraries and the  target
CPPflags = c++ -O3
# Here we define the library functions we nee
LIB = -larmadillo -llapack -lblas
# Here we define the name of the executable
PROG = testcode
TARGET = main

all: ${PROG} ${TARGET}

${PROG} :	   	test-main.o  test-functions.o jacobi_rotation.o
			${CPPflags} test-main.o test-functions.o jacobi_rotation.o ${LIB} -o ${PROG}

${TARGET} :	   	main.o jacobi_rotation.o
			${CPPflags} main.o jacobi_rotation.o ${LIB} -o ${TARGET}

tests-main.o :			tests-main.cpp 
		        	${CPPflags} -c test-main.cpp

test-functitons.o :			test-functions.cpp
		        	${CPPflags} -c test-functions.cpp

jacobi_rotation.o :		jacobi_rotation.cpp 
		        	${CPPflags} -c jacobi_rotation.cpp

main.o: main.cpp
		${CPPflags} -c main.cpp


